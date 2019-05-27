/*
 * menu.h
 */
#ifndef MENU_H
#define MENU_H

#include <string>

#include "delivery.h"

enum state_t {START, MAP, INIT_POINT, END_POINT, VAN, VIEW};

/**
 * @brief First Menu
 * 
 * @return int Returns 0 on success
 */
int startMenu();

/**
 * @brief Main Menu
 * 
 * @return int Returns 0 on success
 */
int mainMenu();

/**
 * @brief Area Data Menu
 * 
 * @return int Returns 0 on success
 */
int dataAreaMenu();

/**
 * @brief Paths Menu
 * 
 * @return int Returns 0 on success
 */
int showPathsMenu();

/**
 * @brief Tag Menu
 * 
 * @return int Returns 0 on success
 */
int tagMenu();

/**
 * @brief Van Menu
 * 
 * @return int Returns 0 on success
 */
int vanMenu();

/**
 * @brief Add Van Menu
 * 
 */
void addVanMenu();

/**
 * @brief Lists the available maps on the directory ../Maps/
 * 
 */
void listAvailableMaps();

/**
 * @brief Lists the available tags read from each map's respective tag file
 * 
 */
void listAvailableTags(std::string tag);

/**
 * @brief Lists the logistic points from the tags
 * 
 */
void listAvailableLogisticPoints(std::string pointType);

/**
 * @brief Lists the deliveries from the tags
 * 
 */
void listDeliveries();

/**
 * @brief Prompts the user with the instruction to choose a map
 * 
 */
void printMapInstruction();

/**
 * @brief Prompts the user with the instruction to choose the points
 * 
 */
void printPointInstruction();

/**
 * @brief Prompts the user with the instruction to add vans
 * 
 */
void printVanInstruction();

/**
 * @brief Verifies whether the given tag is a logistic point
 * 
 * @param tag Tag to analyze
 * @return True if it is a logistic point, false otherwise
 */
bool isTagLogisticPoint(std::string tag);

/**
 * @brief Verifies whether the given tag is a delivery point
 * 
 * @param tag Tag to analyze
 * @return True if it is a delivery point, false otherwise
 */
bool isTagDeliveryPoint(std::string tag);

#endif //MENU_H