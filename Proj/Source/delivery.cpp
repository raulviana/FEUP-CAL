#include "delivery.h"

Delivery::Delivery(std::string recipientName, double contentValue, double volume, Node *node, int invoiceNumber)
{
    this->recipientName = recipientName;
    this->contentValue = contentValue;
    this->volume = volume;
    this->node = node;
    this->invoiceNumber = invoiceNumber;
}

std::string Delivery::getRecipientName()
{
    return recipientName;
}

double Delivery::getContentValue()
{
    return contentValue;
}

double Delivery::getVolume()
{
    return volume;
}

Node *Delivery::getNode()
{
    return node;
}

int Delivery::getInvoiceNumber()
{
    return invoiceNumber;
}
