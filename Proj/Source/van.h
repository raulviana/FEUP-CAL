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
    /**
     * @brief Construct a new Van object
     * 
     * @param maxVolume 
     */
    Van(int maxVolume);

    /**
     * @brief Construct a new Van object
     * 
     * @param deliveries 
     */
    Van(std::vector<Delivery *> deliveries);

    /**
     * @brief Get the Max Vol object
     * 
     * @return int 
     */
    int getMaxVol();

    /**
     * @brief Set the Max Vol object
     * 
     * @param volume 
     */
    void setMaxVol(int volume);

    /**
     * @brief Get the Deliveries object
     * 
     * @return std::vector<Delivery *> 
     */
    std::vector<Delivery *> getDeliveries();

    /**
     * @brief 
     * 
     * @param delivery 
     */
    void addDelivery(Delivery *delivery);

    /**
     * @brief 
     * 
     * @param deliveries 
     */
    void calcVans(std::vector<Delivery *> &deliveries);

    /**
     * @brief 
     * 
     * @param deliveries 
     */
    void distributeDeliveries(std::vector<Delivery *> &deliveries);
};

#endif /* VAN_H_ */