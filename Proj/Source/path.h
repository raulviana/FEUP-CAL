/*
 * path.h
 */
#ifndef PATH_H
#define PATH_H

#include "map.h"

void pathOfVan(Map *map);
void isReachable(std::vector<Node *> res, std::vector<Delivery *> deliveries);

#endif //PATH_H