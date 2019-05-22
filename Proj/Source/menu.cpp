#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <iostream>
#include <string>
#include <vector>

#include "menu.h"
#include "map.h"
#include "path.h"

std::string mapOption = "";
Map *map = new Map();

int startMenu()
{
    mainMenu();
    return 0;
}

int mainMenu()
{
    int option;

    do
    {
        std::cout << "\n-------------- Menu Principal --------------\n";
        std::cout << "--------------------------------------------\n\n";
        std::cout << "0 - Sair\n";
        std::cout << "--------\n";
        std::cout << "1 - Escolher Mapa da Área de Influência\n";
        std::cout << "2 - Alterar Dados da Área de Influência\n";
        std::cout << "3 - Visualização dos Percursos\n\n";
        std::cout << "--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            if (map->getGraphViewer() != NULL)
                map->closeGraphViewer();
            std::cout << "\nA sair do programa...\n\n";
            break;
        case 1:
            if (!validateMapChoice())
            {
                listAvailableMaps();
                if (mapOption != "")
                    map->loadMap(mapOption);
            }
            break;
        case 2:
            if (validateMapChoice())
            {
                dataAreaMenu();
            }
            break;
        case 3:
            if (validateMapChoice())
            {
                showPathsMenu();
            }
            break;
        default:
            break;
        }

    } while (option != 0);

    return 0;
}

int dataAreaMenu()
{
    int option;

    do
    {
        std::cout << "\n------- Dados da Área de Influência -------\n";
        std::cout << "-------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";
        std::cout << "1 - Definir Local Inicial (depósito)\n";
        std::cout << "2 - Definir Local Final (garagem)\n";
        std::cout << "3 - Definir Pontos de Entrega\n\n";
        std::cout << "-------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            listAvailableLogisticPoints("warehouse");
            break;
        case 2:
            listAvailableLogisticPoints("garage");
            break;
        case 3:
            break;
        default:
            break;
        }

    } while (option != 0);

    return 0;
}

int showPathsMenu()
{
    int option;

    do
    {
        std::cout << "\n-------- Visualização dos Percursos --------\n";
        std::cout << "--------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";
        std::cout << "1 - Percursos de Todas as Carrinhas\n";
        std::cout << "2 - Percurso de uma Determinada Carrinha\n\n";
        std::cout << "--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            pathOfVan(map);
            break;
        case 2:
            break;
        default:
            break;
        }

    } while (option != 0);

    return 0;
}

void listAvailableMaps()
{
    int option;
    std::vector<std::string> maps;

    DIR *dirp = opendir("../Maps");
    struct dirent *dp;

    while ((dp = readdir(dirp)) != NULL)
    {
        if (strcmp(dp->d_name, ".") && strcmp(dp->d_name, ".."))
        {
            maps.push_back(dp->d_name);
        }
    }

    closedir(dirp);

    std::cout << "\n------------- Mapas Disponíveis -------------\n";
    std::cout << "---------------------------------------------\n\n";
    std::cout << "0 - Voltar Atrás\n";
    std::cout << "----------------\n";

    for (unsigned int i = 0; i < maps.size(); i++)
    {
        std::cout << i + 1 << " - " << maps.at(i) << std::endl;
    }

    std::cout << "\n---------------------------------------------\n\n";
    std::cout << "Opção: ";
    std::cin >> option;

    if (option != 0)
    {
        mapOption = maps.at(option - 1);
        std::cout << "\n -> Escolhido Mapa ' " << maps.at(option - 1) << " ' ...\n";
    }
}

bool validateMapChoice()
{
    if (mapOption == "")
    {
        std::cout << "\n---------------------------------\n\n";
        std::cout << "\nEscolha um Mapa antes de começar!\n\n";
        std::cout << "\n---------------------------------\n\n";
        return false;
    }
    else
    {
        return true;
    }
}

void listAvailableLogisticPoints(std::string pointType)
{
    int option;
    std::vector<int> showedNodes;
    Node *node;

    std::cout << "\n------------- Pontos Disponíveis ------------\n";
    std::cout << "---------------------------------------------\n\n";
    std::cout << "0 - Voltar Atrás\n";
    std::cout << "----------------\n";

    int counter = 0; // to choose 5 tags

    for (unsigned int i = 0; i < map->getGraph()->getNumVertex(); i++) /* it only shows the first 5 for now ... */
    {
        std::string tag = map->getGraph()->getVertexSet().at(i)->getInfo()->getTag();
        node = map->getGraph()->getVertexSet().at(i)->getInfo();

        if (isTagLogisticPoint(tag))
        {
            std::cout << counter + 1 << " - " << node->getIdNode() << std::endl;
            showedNodes.push_back(i);
            counter++;
        }

        if (counter == 5)
            break;
    }

    std::cout << "\n---------------------------------------------\n\n";
    std::cout << "Opção: ";
    std::cin >> option;

    if (option != 0)
    {
        node = map->getGraph()->getVertexSet().at(showedNodes.at(option - 1))->getInfo();

        if (pointType == "garage")
            map->setGarage(node);
        else if (pointType == "warehouse")
            map->setWarehouse(node);

        std::cout << "\n -> Escolhido Ponto ' " << node->getIdNode() << " ' -> " << pointType << " ...\n";
    }
}

bool isTagLogisticPoint(std::string tag)
{
    if (tag == "building=warehouse" ||
        tag == "industrial=warehouse" ||
        tag == "landuse=industrial" ||
        tag == "amenity=loading_dock")
        return true;

    return false;
}

bool isTagDeliveryPoint(std::string tag)
{
    if (!isTagLogisticPoint(tag) && tag != "")
        return true;

    return false;
}