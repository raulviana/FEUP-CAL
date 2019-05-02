#include "menu.h"
#include <iostream>

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
