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
    Delivery(std::string recipientName, int contentValue, int volume, Node *node, int invoiceNumber);
    std::string getRecipientName();
    int getContentValue();
    int getVolume();
    Node *getNode();
    int getInvoiceNumber();
    bool operator==(Delivery &delivery);
};

#endif /* DELIVERY_H_ */