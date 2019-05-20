

#include "delivery.h"


Delivery::Delivery(string recipientName, float contentValue, int volume, int node, int invoiceNumber){
     recipientName = recipientName; 
     contentValue = contentValue;
     volume = volume;
     node = Node;
     invoiceNumber = invoiceNumber;
}

std::string Delivery::getrecipientName(){
     return recipientName;
}

float Delivery::getcontentValue(){
     return contentValue;
}

float Delivery::getvolume(){
     return volume;
}

int Delivery::getNode(){
     return Node;
} 

int Delivery::getinvoiceNumber(){
     return invoiceNumber;
}
   
