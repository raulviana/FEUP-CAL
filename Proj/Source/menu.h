/*
 * menu.h
 */
#ifndef MENU_H
#define MENU_H

#include <string>

#include "delivery.h"

enum state_t {START, MAP, INIT_POINT, END_POINT, VIEW};

int startMenu();
int mainMenu();
int dataAreaMenu();
int showPathsMenu();
int tagMenu();
void listDeliveries();
void listAvailableTags(std::string tag);
void listAvailableMaps();
void printMapInstruction();
void printPointInstruction();
void listAvailableLogisticPoints(std::string pointType);
bool isTagLogisticPoint(std::string tag);
bool isTagDeliveryPoint(std::string tag);

#endif //MENU_H