/*
 * van.h
 */
#ifndef VAN_H_
#define VAN_H_

#include <vector>
#include <iostream>

#include "delivery.h"

class Van
{
private:
    std::vector<Delivery *> deliveries;
    int maxVol;

public:
    Van(int maxVolume);
    Van(std::vector<Delivery *> deliveries);
    std::vector<Delivery *> getDeliveries();
    void addDelivery(Delivery *delivery);
    int getMaxVol();
    void setMaxVol(int volume);

    void calcVans(std::vector<Delivery *> &deliveries);
    void distributeDeliveries(std::vector<Delivery *> &deliveries);
};

#endif /* VAN_H_ */