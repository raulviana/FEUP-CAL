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
            if (state == VIEW || state == VAN || map->getVans()->size() != 0)
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
        std::cout << "1 - Local Inicial (armazém)\n";
        std::cout << "2 - Local Final (garagem)\n";
        std::cout << "3 - Pontos de Entrega\n";
        std::cout << "4 - Carrinhas\n\n";
        std::cout << "-------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            listAvailableLogisticPoints("armazém");
            break;
        case 2:
            listAvailableLogisticPoints("garagem");
            break;
        case 3:
            tagMenu();
            break;
        case 4:
            if (state != VAN && state != VIEW)
                printPointInstruction();
            else
                vanMenu();
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
    int vanChoice;
    bool noDeliveries = true;
    vanDeliveries(map);

    do
    {
        std::cout << "\n-------- Visualização dos Percursos --------\n";
        std::cout << "--------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";
        std::cout << "1 - Percurso de uma Carrinha com Carga Ilimitada (1ª Iteração)\n";
        std::cout << "2 - Percurso de uma Determinada Carrinha (de um conjunto de carrinhas) com Carga Limitada (2ª Iteração)\n\n";
        std::cout << "--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            vanPath(map, 0, true);
            break;
        case 2:
            map->setGraphViewerDefaultAppearance();
            if (state == VAN)
                printVanInstruction();
            else
            {
                std::cout << "\n------------- Carrinhas Usadas -------------\n";
                std::cout << "--------------------------------------------\n\n";

                for (unsigned int i = 0; i < map->getVans()->size(); i++)
                {
                    if (map->getVans()->at(i)->getDeliveries().size() != 0)
                    {
                        std::cout << i + 1 << " - " << map->getVans()->at(i)->getMaxVol() << " (capacidade)" << std::endl;
                        noDeliveries = false;
                    }
                }

                if (noDeliveries)
                {
                    cout << "No deliveries to deliver. Add some before trying to viewww a path.\n";
                    break;
                }

                std::cout << "\n--------------------------------------------\n\n";
                std::cout << "Opção: ";
                std::cin >> vanChoice;
                vanPath(map, vanChoice - 1, false);
            }
            break;
        default:
            break;
        }

    } while (option != 0);

    map->setGraphViewerDefaultAppearance();

    return 0;
}

int tagMenu()
{
    int option;

    do
    {
        std::cout << "\n------------ Pontos de Entrega ------------\n";
        std::cout << "-------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";
        std::cout << "1 - Listar Encomendas\n";
        std::cout << "2 - Adicionar Encomenda\n";
        std::cout << "\n--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            std::cout << "\n-----------------------------------------\n\n";

            for (unsigned int i = 0; i < map->getDeliveries()->size(); i++)
            {
                std::cout << i + 1 << " - " << map->getDeliveries()->at(i)->getNode()->getIdNode() << " ("
                          << map->getDeliveries()->at(i)->getRecipientName() << ")" << std::endl;
            }
            std::cout << "\n-----------------------------------------\n";
            break;
        case 2:
            listDeliveries();
            break;
        default:
            break;
        }

    } while (option != 0);

    return 0;
}

int vanMenu()
{
    int option;

    do
    {
        std::cout << "\n---------------- Carrinhas ----------------\n";
        std::cout << "-------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";
        std::cout << "1 - Listar Carrinhas\n";
        std::cout << "2 - Adicionar Carrinha\n";
        std::cout << "\n-------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 0:
            break;
        case 1:
            std::cout << "\n-------------------------------------------\n\n";

            for (unsigned int i = 0; i < map->getVans()->size(); i++)
            {
                std::cout << i + 1 << " - " << map->getVans()->at(i)->getMaxVol() << " (capacidade)" << std::endl;
            }
            std::cout << "\n-------------------------------------------\n";
            break;
        case 2:
            addVanMenu();
            break;
        default:
            break;
        }

    } while (option != 0);

    return 0;
}

void addVanMenu()
{
    int maxVol;
    std::cout << "\n-----------------\n";
    std::cout << "Capacidade Máxima: ";
    std::cin >> maxVol;
    std::cout << "-----------------\n";

    Van *van = new Van(maxVol);
    map->addVan(van);
    state = VIEW;
}

void listDeliveries()
{
    int option;
    std::vector<string> tags = {"shop=department_store", "shop=variety_store", "shop=supermarket",
                                "shop=doityourself", "shop=convenience", "shop=clothes",
                                "shop=hardware", "shop=furniture", "shop=eletronics",
                                "shop=mobile_phone", "shop=shoes", "shop=alcohol"};

    do
    {
        std::cout << "\n------------ Tags Disponíveis ------------\n";
        std::cout << "------------------------------------------\n\n";
        std::cout << "0 - Voltar Atrás\n";
        std::cout << "----------------\n";

        for (unsigned int i = 0; i < tags.size(); i++)
        {
            std::cout << i + 1 << " - " << tags.at(i) << std::endl;
        }

        std::cout << "\n---------------------------------------------\n\n";
        std::cout << "Opção: ";
        std::cin >> option;

        if (option != 0)
            listAvailableTags(tags.at(option - 1));

    } while (option != 0);
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

void listAvailableTags(std::string tag)
{
    int option;
    int counter = 0; // to choose 5 tags
    std::vector<int> showedNodes;
    Node *node;

    /* New seed for rand() */
    srand(time(NULL));

    std::cout << "\n----------- " << tag << " ----------\n\n";
    std::cout << "0 - Voltar Atrás\n";
    std::cout << "----------------\n";

    /* it only shows 5 random nodes ... */
    while (counter < 5)
    {
        int randomNumber = rand() % map->getGraph()->getNumVertex();

        std::string newTag = map->getGraph()->getVertexSet().at(randomNumber)->getInfo()->getTag();
        node = map->getGraph()->getVertexSet().at(randomNumber)->getInfo();

        if (tag == newTag)
        {
            std::cout << counter + 1 << " - " << node->getIdNode() << std::endl;
            showedNodes.push_back(node->getIdNode());
            counter++;
        }
    }

    std::cout << "...\n";
    std::cout << "\n---------------------------------------------\n\n";
    std::cout << "Opção: ";
    std::cin >> option;

    if (option != 0)
    {
        node = map->findNode(showedNodes.at(option - 1));

        std::string recipientName;
        std::cout << "\n--------------------\n";
        std::cout << "Nome do Destinatário: ";
        std::cin >> recipientName;
        std::cout << "--------------------\n";

        double contentValue;
        std::cout << "\n-----\n";
        std::cout << "Valor: ";
        std::cin >> contentValue;
        std::cout << "-----\n";

        double volume;
        std::cout << "\n------\n";
        std::cout << "Volume: ";
        std::cin >> volume;
        std::cout << "------\n";

        int invoiceNumber;
        std::cout << "\n----------------\n";
        std::cout << "Número do Pedido: ";
        std::cin >> invoiceNumber;
        std::cout << "----------------\n";

        Delivery *del = new Delivery(recipientName, contentValue, volume, node, invoiceNumber);
        map->addDelivery(del);

        std::cout << "\n -> Escolhido Ponto ' " << node->getIdNode() << " ' -> " << tag << " ...\n";
    }
}

void listAvailableLogisticPoints(std::string pointType)
{
    int option;
    int counter = 0; // to choose 5 tags
    std::vector<int> showedNodes;
    Node *node;

    /* new seed for rand() */
    srand(time(NULL));

    std::cout << "\n------------- Pontos Disponíveis ------------\n";
    std::cout << "---------------------------------------------\n\n";
    std::cout << "0 - Voltar Atrás\n";
    std::cout << "----------------\n";
    std::cout << "1 - Indicar Ponto\n";

    if (state == INIT_POINT || state == VIEW || state == VAN)
    {
        std::cout << "2 - Armazém (" << map->getWarehouse()->getIdNode() << ")" << endl;
        showedNodes.push_back(map->getWarehouse()->getIdNode());
        counter++;
    }

    if (state == END_POINT || state == VIEW || state == VAN)
    {
        if (state == INIT_POINT)
            std::cout << "2 - Garagem (" << map->getGarage()->getIdNode() << ")" << endl;
        else
            std::cout << "3 - Garagem (" << map->getGarage()->getIdNode() << ")" << endl;

        showedNodes.push_back(map->getGarage()->getIdNode());
        counter++;
    }

    /* it only shows 5 random nodes ... */
    while (counter < 5)
    {
        int randomNumber = rand() % map->getGraph()->getNumVertex();

        std::string tag = map->getGraph()->getVertexSet().at(randomNumber)->getInfo()->getTag();
        node = map->getGraph()->getVertexSet().at(randomNumber)->getInfo();

        if (isTagLogisticPoint(tag))
        {
            std::cout << counter + 2 << " - " << node->getIdNode() << std::endl;
            showedNodes.push_back(node->getIdNode());
            counter++;
        }
    }

    std::cout << "...\n";
    std::cout << "\n---------------------------------------------\n\n";
    std::cout << "Opção: ";
    std::cin >> option;

    if (option != 0)
    {
        /* 'escolher ponto' */
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

            if (!isTagLogisticPoint(node->getTag()))
            {
                std::cout << "\n---------------------------------\n";
                std::cout << "O ponto indicado não é logístico!\n";
                std::cout << "---------------------------------\n";
                return;
            }
        }
        else
        {
            node = map->findNode(showedNodes.at(option - 2));
        }

        if (pointType == "armazém")
        {
            map->setWarehouse(node);

            if (state == END_POINT)
                state = VAN;
            else if (state == VIEW)
                state = VIEW;
            else
                state = INIT_POINT;
        }
        else if (pointType == "garagem")
        {
            map->setGarage(node);

            if (state == INIT_POINT)
                state = VAN;
            else if (state == VIEW)
                state = VIEW;
            else
                state = END_POINT;
        }

        std::cout << "\n -> Escolhido Ponto ' " << node->getIdNode() << " ' -> " << pointType << " ...\n";
    }
}

void printMapInstruction()
{
    std::cout << "\n\n---------------------------------\n";
    std::cout << "Escolha um mapa antes de começar!";
    std::cout << "\n---------------------------------\n\n";
}

void printPointInstruction()
{
    std::cout << "\n\n----------------------------------------\n";
    std::cout << "Defina todos os pontos antes de avançar!";
    std::cout << "\n----------------------------------------\n\n";
}

void printVanInstruction()
{
    std::cout << "\n\n-------------------------------------------------\n";
    std::cout << "Adicione pelo menus uma carrinha antes de avançar!";
    std::cout << "\n-------------------------------------------------\n\n";
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