#include "menu.h"
#include <iostream>

int startMenu()
{
    mainMenu();
    dataAreaMenu();
    showPathsMenu();

    return 0;
}

int mainMenu()
{
    std::cout << "\n-------------- Menu Principal --------------\n";
    std::cout << "--------------------------------------------\n\n";
    std::cout << "1 - Alterar Dados da Área de Influência\n";
    std::cout << "2 - Visualização dos Percursos\n\n";
    std::cout << "--------------------------------------------\n\n";

    return 0;
}

int dataAreaMenu()
{
    std::cout << "------- Dados da Área de Influência -------\n";
    std::cout << "-------------------------------------------\n\n";
    std::cout << "1 - Escolher mapa da área de influência\n";
    std::cout << "2 - Definir local inicial (depósito)\n";
    std::cout << "3 - Definir local final (garagem)\n";
    std::cout << "4 - Definir o ponto de entrega\n\n";
    std::cout << "-------------------------------------------\n\n";

    return 0;
}

int showPathsMenu()
{
    std::cout << "-------- Visualização dos Percursos --------\n";
    std::cout << "--------------------------------------------\n\n";
    std::cout << "1 - Percursos de todas as carrinhas\n";
    std::cout << "2 - Percurso de uma determinada carrinha\n\n";
    std::cout << "--------------------------------------------\n\n";

    return 0;
}
