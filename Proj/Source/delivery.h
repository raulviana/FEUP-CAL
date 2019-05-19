/*
 * delivery.h
 */
#ifndef DELIVERY_H_
#define DELIVERY_H_

#include <string> 
#include "graph.h"
#include "map.h"

class Delivery{
    private:
        std::string recipientName;
        float contentValue;
        float volume;
        Node destiny;  //Nao tenho a certeza se será asim, poseria ser Vertex? 
        int invoiceNumber;

    public:
        Delivery(string recipientName, float contentValue, float volume, Node destiny, int invoiceNumber);
        ~Delivery();
        std::string getrecipientName();
        float getcontentValue();
        float getvolume();
        Node getdestiny();  //Nao tenho a certeza se será asim, poseria ser Vertex? 
        int getinvoiceNumber();
};



#endif /* DELIVERY_H_ */


