/*
 * path.h
 */
#ifndef PATH_H
#define PATH_H

#include "map.h"
#include "2opt.h"
#include "van.h"

void vanPath(Map *map, int vanIndex, bool firstIteration);
void vanDeliveries(Map *map);

#endif //PATH_H