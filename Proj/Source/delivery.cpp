#include "delivery.h"

Delivery::Delivery(std::string recipientName, double contentValue, double volume, int node, int invoiceNumber)
{
    this->recipientName = recipientName;
    this->contentValue = contentValue;
    this->volume = volume;
    this->node = node;
    this->invoiceNumber = invoiceNumber;
}

std::string Delivery::getrecipientName()
{
    return recipientName;
}

double Delivery::getcontentValue()
{
    return contentValue;
}

double Delivery::getvolume()
{
    return volume;
}

int Delivery::getNode()
{
    return node;
}

int Delivery::getinvoiceNumber()
{
    return invoiceNumber;
}

/*
//MUdar para class NOde???? !!!!!Not tested!!!!!!!!!
bool IsReachable(vector<Node> res, Node deliveryPoint) {
    for (auto i = 0; i < res.size(); i++) {
        if (deliveryPoint == res.at(i))
            return true;
        else
            return false;
    }
}*/