/*
 * path.h
 */
#ifndef PATH_H
#define PATH_H

#include "map.h"
#include "2opt.h"
#include "van.h"

/**
 * @brief Applies two-opt algorithm for a specific van if it's the second iteration and for all vans if it's the first
 * 
 * @param map Pointer to the graph
 * @param vanIndex Index of the van whose path is to be caclculated
 * @param firstIteration True if it's the first iteration, false otherwise
 */
void vanPath(Map *map, int vanIndex, bool firstIteration);

// =======================================================

/**
 * @brief Applies knapsack problem to all vans until there's no deliveries to deliver
 * 
 * @param map Pointer to the graph
 */
void vanDeliveries(Map *map);

#endif //PATH_H