/*
 * van.h
 */
#ifndef VAN_H_
#define VAN_H_

#include <vector>

#include "delivery.h"
#include "map.h"

class Van
{
private:
    std::vector<Delivery *> deliveries;
    int maxVol;

public:
    Van();
    Van(std::vector<Delivery *> deliveries);
    std::vector<Delivery *> getDeliveries();
    void addDelivery(Delivery *delivery);
    int getMaxVol();
    void setMaxVol(int volume);

    std::vector<Delivery *> calcVans(Map *map);
    vector<Delivery *> distributeDeliveries(vector<Delivery *> &deliveries);
};

#endif /* VAN_H_ */