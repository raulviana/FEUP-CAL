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
    int getMaxVol();
    void setMaxVol();

    void addDelivery(Delivery *delivery);
    std::vector<Van *> calcVans();
};

#endif /* VAN_H_ */