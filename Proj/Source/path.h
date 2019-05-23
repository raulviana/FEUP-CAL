/*
 * path.h
 */
#ifndef PATH_H
#define PATH_H

#include "map.h"
#include "2opt.h"

void pathOfVan(Map *map);
void isReachable(std::vector<Node *> res, std::vector<Delivery *> deliveries);

#endif //PATH_H