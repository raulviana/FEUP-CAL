/*
 * van.h
 */

#ifndef VAN_H_
#define VAN_H_

#include "delivery.h"

class Van{
    private:
    vector<Deliveries*> deliveries;
    int maxVol;

    public:
    Van();
    Van(vector<Deliveries*> deliveries);
    vector<Deliveries*> getDeliveries();
    void addDelivery(Delivery* delivery);
    int getMaxVol();
    void addDelivery();
    void setMaxVol();
};







#endif /* VAN_H_ */