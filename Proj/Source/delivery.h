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
     * @brief Construct a new Delivery
     * 
     * @param recipientName Name of the delivery's recipient
     * @param contentValue Delivery's content value
     * @param volume Delivery's volume
     * @param node Node to deliver the delivery
     * @param invoiceNumber Delivery's invoice number 
     */
    Delivery(std::string recipientName, int contentValue, int volume, Node *node, int invoiceNumber);
    
    /**
     * @brief Get the Recipient Name of a Delivery
     * 
     * @return std::string Returns the delivery's recipient name
     */
    std::string getRecipientName();

    /**
     * @brief Get the Content Value of a Delivery
     * 
     * @return int Returns the delivery's content value
     */
    int getContentValue();

    /**
     * @brief Get the Volume of a Delivery
     * 
     * @return int Returns the delivery's volume
     */
    int getVolume();

    /**
     * @brief Get the Node of a Delivery
     * 
     * @return Node* Returns a pointer to the delivery's Node
     */
    Node *getNode();

    /**
     * @brief Get the Invoice Number of a Delivery
     * 
     * @return int Returns the delivery's invoice number
     */
    int getInvoiceNumber();

    /**
     * @brief Checks whether two deliveries are the same
     * 
     * @param delivery Delivery to compare with
     * @return True if deliveries' invoice number are the same, false otherwise
     */
    bool operator==(Delivery &delivery);
};

#endif /* DELIVERY_H_ */