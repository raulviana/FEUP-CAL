/*
 * delivery.h
 */
#ifndef DELIVERY_H_
#define DELIVERY_H_

#include <string>

#include "node.h"

class Delivery
{
private:
    std::string recipientName;
    int contentValue;
    int volume;
    Node *node;
    int invoiceNumber;

public:
    /**
     * @brief Construct a new Delivery object
     * 
     * @param recipientName 
     * @param contentValue 
     * @param volume 
     * @param node 
     * @param invoiceNumber 
     */
    Delivery(std::string recipientName, int contentValue, int volume, Node *node, int invoiceNumber);
    
    /**
     * @brief Get the Recipient Name object
     * 
     * @return std::string 
     */
    std::string getRecipientName();

    /**
     * @brief Get the Content Value object
     * 
     * @return int 
     */
    int getContentValue();

    /**
     * @brief Get the Volume object
     * 
     * @return int 
     */
    int getVolume();

    /**
     * @brief Get the Node object
     * 
     * @return Node* 
     */
    Node *getNode();

    /**
     * @brief Get the Invoice Number object
     * 
     * @return int 
     */
    int getInvoiceNumber();

    /**
     * @brief 
     * 
     * @param delivery 
     * @return true 
     * @return false 
     */
    bool operator==(Delivery &delivery);
};

#endif /* DELIVERY_H_ */