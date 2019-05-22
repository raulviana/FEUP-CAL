/*
 * menu.h
 */
#ifndef MENU_H
#define MENU_H

#include <string>

int startMenu();
int mainMenu();
int dataAreaMenu();
int showPathsMenu();
void listAvailableMaps();
bool validateMapChoice();
void listAvailableLogisticPoints(std::string pointType);
bool isTagLogisticPoint(std::string tag);
bool isTagDeliveryPoint(std::string tag);

#endif //MENU_H