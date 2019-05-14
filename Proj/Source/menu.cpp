#include <iostream>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <string>
#include <vector>

#include "menu.h"

std::vector<std::string> maps;

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
        std::cout << "1 - Alterar Dados da Área de Influência\n";
        std::cout << "2 - Visualização dos Percursos\n";
        std::cout << "3 - Sair\n\n";
        std::cout << "--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            dataAreaMenu();
            break;
        case 2:
            showPathsMenu();
            break;
        case 3:
            std::cout << "\nA sair do programa...\n\n";
            break;
        default:
            break;
        }

    } while (option != 3);

    return 0;
}

int dataAreaMenu()
{
    int option;

    do
    {
        std::cout << "\n------- Dados da Área de Influência -------\n";
        std::cout << "-------------------------------------------\n\n";
        std::cout << "1 - Escolher mapa da área de influência\n";
        std::cout << "2 - Definir local inicial (depósito)\n";
        std::cout << "3 - Definir local final (garagem)\n";
        std::cout << "4 - Definir o ponto de entrega\n";
        std::cout << "5 - Voltar atrás\n\n";
        std::cout << "-------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            listAvailableMaps();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            break;
        }

    } while (option != 5);

    return 0;
}

int showPathsMenu()
{
    int option;

    do
    {
        std::cout << "\n-------- Visualização dos Percursos --------\n";
        std::cout << "--------------------------------------------\n\n";
        std::cout << "1 - Percursos de todas as carrinhas\n";
        std::cout << "2 - Percurso de uma determinada carrinha\n";
        std::cout << "3 - Voltar atrás\n\n";
        std::cout << "--------------------------------------------\n\n";

        std::cout << "Opção: ";
        std::cin >> option;

        switch (option)
        {
        case 1:
            break;
        case 2:
            break;
        default:
            break;
        }

    } while (option != 3);

    return 0;
}

void listAvailableMaps()
{
    int option;

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

    do
    {
        std::cout << "\n------------- Mapas Disponíveis -------------\n";
        std::cout << "---------------------------------------------\n\n";

        for (unsigned int i = 0; i < maps.size(); i++)
        {
            std::cout << i + 1 << " - " << maps.at(i) << std::endl;
        }

        std::cout << (int)maps.size() + 1 << " - Voltar atrás\n\n";
        std::cout << "---------------------------------------------\n\n";
        std::cout << "Opção: ";
        std::cin >> option;

    } while (option != (int)maps.size() + 1);
}