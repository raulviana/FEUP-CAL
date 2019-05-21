/*
 * delivery.h
 */
#ifndef DELIVERY_H_
#define DELIVERY_H_

#include <string>

class Delivery
{
private:
    std::string recipientName;
    double contentValue;
    double volume;
    int node; //Nao tenho a certeza se será asim, poseria ser Vertex?
    int invoiceNumber;

public:
    Delivery(std::string recipientName, double contentValue, double volume, int node, int invoiceNumber);
    ~Delivery();
    std::string getrecipientName();
    double getcontentValue();
    double getvolume();
    int getNode(); //Nao tenho a certeza se será asim, poseria ser Vertex?
    int getinvoiceNumber();
};

#endif /* DELIVERY_H_ */