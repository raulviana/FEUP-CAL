#include "delivery.h"

Delivery::Delivery(std::string recipientName, int contentValue, int volume, Node *node, int invoiceNumber)
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

int Delivery::getContentValue()
{
    return contentValue;
}

int Delivery::getVolume()
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

bool Delivery::operator==(Delivery &other){
    if(this->getInvoiceNumber() == other.getInvoiceNumber()) return true;
    else return false;
}
