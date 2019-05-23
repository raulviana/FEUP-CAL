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

static state_t state = START;

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
            if (state != START)
                map->closeGraphViewer();
            std::cout << "\nA sair do programa...\n\n";
            break;
        case 1:
            if (state == START)
            {
                listAvailableMaps();
                if (state == MAP)
                    map->loadMap(mapOption);
            }
            break;
        case 2:
            if (state != START)
                dataAreaMenu();
            else
                printMapInstruction();
            break;
        case 3:
            if (state == VIEW)
                showPathsMenu();
            else if (state == START)
                printMapInstruction();
            else
                printPointInstruction();
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

    map->setGraphViewerDefaultAppearance();

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
        state = MAP;
        mapOption = maps.at(option - 1);
        std::cout << "\n -> Escolhido Mapa ' " << maps.at(option - 1) << " ' ...\n";
    }
}

void printMapInstruction()
{
    std::cout << "\n---------------------------------\n";
    std::cout << "Escolha um mapa antes de começar!";
    std::cout << "\n---------------------------------\n\n";
}

void printPointInstruction()
{
    std::cout << "\n----------------------------------------\n";
    std::cout << "Defina todos os pontos antes de avançar!";
    std::cout << "\n----------------------------------------\n\n";
}

void listAvailableLogisticPoints(std::string pointType)
{
    int option;
    std::vector<int> showedNodes;
    Node *node;

    /* New seed for rand() */
    srand(time(NULL));

    std::cout << "\n------------- Pontos Disponíveis ------------\n";
    std::cout << "---------------------------------------------\n\n";
    std::cout << "0 - Voltar Atrás\n";
    std::cout << "----------------\n";
    std::cout << "1 - Indicar Ponto\n";

    int counter = 0; // to choose 5 tags

    /* it only shows 5 random nodes ... */
    while (counter < 5)
    {
        int randomNumber = rand() % map->getGraph()->getNumVertex();

        std::string tag = map->getGraph()->getVertexSet().at(randomNumber)->getInfo()->getTag();
        node = map->getGraph()->getVertexSet().at(randomNumber)->getInfo();

        if (isTagLogisticPoint(tag))
        {
            std::cout << counter + 2 << " - " << node->getIdNode() << std::endl;
            showedNodes.push_back(randomNumber);
            counter++;
        }
    }

    std::cout << "...\n";
    std::cout << "\n---------------------------------------------\n\n";
    std::cout << "Opção: ";
    std::cin >> option;

    if (option != 0)
    {
        if (option == 1)
        {
            std::cout << "\n----------------\n";
            std::cout << "Ponto pretendido: ";
            std::cin >> option;
            std::cout << "----------------\n";

            node = map->findNode(option);

            if (node == NULL)
            {
                std::cout << "\n---------------------------------------------\n";
                std::cout << "O ponto indicado não existe, tente novamente!\n";
                std::cout << "---------------------------------------------\n";
                return;
            }
        }
        else
        {
            //if (isTagLogisticPoint(map->findNode(option)->getTag()))
            //{
            node = map->getGraph()->getVertexSet().at(showedNodes.at(option - 1))->getInfo();
            /*} 
            else
            {
                std::cout << "\n---------------------------------\n";
                std::cout << "O ponto indicado não é logístico!\n";
                std::cout << "---------------------------------\n";
                return;
            }*/
        }

        if (pointType == "warehouse")
        {
            map->setWarehouse(node);

            if (state == END_POINT)
                state = VIEW;
            else
                state = INIT_POINT;
        }
        else if (pointType == "garage")
        {
            map->setGarage(node);

            if (state == INIT_POINT)
                state = VIEW;
            else
                state = END_POINT;
        }

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