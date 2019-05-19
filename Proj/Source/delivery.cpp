

#include "delivery.h"


Delivery::Delivery(string recipientName, float contentValue, float volume, Node destiny, int invoiceNumber){
     recipientName = recipientName; 
     contentValue = contentValue;
     volume = volume;
     destiny = destiny;
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

Node Delivery::getdestiny(){
     return destiny;
} 

int Delivery::getinvoiceNumber(){
     return invoiceNumber;
}
   
