
#include "van.h"

Van::Van(){};

van::Van(vector<Deliveries*> deliveries){
    this.deliveries = deliveries;
    this.maxVol = INT_MAX;
}

vector<Deliveries*> getDeliveries(){
    return deliveries;
}

int getMaxVol(){
    return maxVol;
}

void addDelivery(Delivery* delivery){
    deliveries.push_back(delivery);
}

void setMaxVol(){
    this.maxVol = 200;
}

};



//mochila ---- Incomplete
vector<Van*> calcVans(){

vector<Deliveries*> deliveries = map->getDeliveries();
vector<Van*> vans;
vector<Deliveries*> items;
vector<int> cost;
vector<int> best;

for (int i = 1; i <= deliveries.size(); i++ ){
  for (int k = deliveries.at(i)->getVolume(); k <= van->getMaxVol(); k++){
    if (deliveries.at(i) + cost[k-size[i]] > cost[k]) {
    cost[k] = deliveries.at(i) + cost[k-size[i]];
    best[k] = i;
    } 
  }
}