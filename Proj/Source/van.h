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
     * @brief Construct a new Van
     * 
     * @param maxVolume Van's maximum volume
     */
    Van(int maxVolume);

    /**
     * @brief Construct a new Van
     * 
     * @param deliveries Deliveries to attach to the van
     */
    Van(std::vector<Delivery *> deliveries);

    /**
     * @brief Get the Max Volume
     * 
     * @return int Van's maximum volume
     */
    int getMaxVol();

    /**
     * @brief Set the Max Volume
     * 
     * @param volume Van's maximum volume
     */
    void setMaxVol(int volume);

    /**
     * @brief Get the Deliveries of a Van
     * 
     * @return std::vector<Delivery *> Return the vector of pointers to each of the Van's deliveries
     */
    std::vector<Delivery *> getDeliveries();

    /**
     * @brief Add delivery to a Van's deliveries
     * 
     * @param delivery Delivery to add
     */
    void addDelivery(Delivery *delivery);

    /**
     * @brief Applies knapsack problem to the Van
     * 
     * @param deliveries Group of deliveries used
     */
    void calcVans(std::vector<Delivery *> &deliveries);

    /**
     * @brief Knapsack problem
     * 
     * @param deliveries Group of deliveries used
     */
    void distributeDeliveries(std::vector<Delivery *> &deliveries);
};

#endif /* VAN_H_ */