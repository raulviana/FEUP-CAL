/*
 * path.h
 */
#ifndef PATH_H
#define PATH_H

#include "map.h"
#include "2opt.h"
#include "van.h"

/**
 * @brief 
 * 
 * @param map 
 * @param vanIndex 
 * @param firstIteration 
 */
void vanPath(Map *map, int vanIndex, bool firstIteration);

// =======================================================

/**
 * @brief 
 * 
 * @param map 
 */
void vanDeliveries(Map *map);

#endif //PATH_H