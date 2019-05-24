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
    double contentValue;
    double volume;
    Node *node;
    int invoiceNumber;

public:
    Delivery(std::string recipientName, double contentValue, double volume, Node *node, int invoiceNumber);
    std::string getRecipientName();
    double getContentValue();
    double getVolume();
    Node *getNode();
    int getInvoiceNumber();
};

#endif /* DELIVERY_H_ */