#include "van.h"
#include "map.h"

#include <vector>
#include <climits>

Van::Van(){};

Van::Van(std::vector<Delivery *> deliveries)
{
  this->deliveries = deliveries;
  this->maxVol = INT_MAX;
}

std::vector<Delivery *> Van::getDeliveries()
{
  return deliveries;
}

int Van::getMaxVol()
{
  return maxVol;
}

void Van::setMaxVol()
{
  this->maxVol = 200;
}

void Van::addDelivery(Delivery *delivery)
{
  deliveries.push_back(delivery);
}

//mochila ---- Incomplete
std::vector<Van *> Van::calcVans() {
    Van van = Van();
    van.setMaxVol();

      
  
}

vector<Delivery*> distributingDeliverires(int maxVol, Map *map) { 
    int i, w; 
    vector<Delivery*> deliveries = map->getDeliveries();
    vector<int> val;
    for (auto i = 0; i < deliveries.size(); i++){
      val.push_back(deliveries.at(i)->getContentValue());
    }
    vector<int> wt;
    for (auto i = 0; i < deliveries.size();i++){
      wt.push_back(deliveries.at(i)->getVolume());
    }

    int n = sizeof(val) / sizeof(val[0]);
    int K[n + 1][maxVol + 1]; 
     
    // Build table K[][] in bottom up manner 
    for (i = 0; i <= n; i++) { 
        for (w = 0; w <= maxVol; w++) { 
            if (i == 0 || w == 0) 
                K[i][w] = 0; 
            else if (wt[i - 1] <= w) 
                K[i][w] = max(val[i - 1] +  
                    K[i - 1][w - wt[i - 1]], K[i - 1][w]); 
            else
                K[i][w] = K[i - 1][w]; 
        } 
    } 
  
    // stores the result of Knapsack 
    int res = K[n][w];     
    cout << res << endl;
      
    int vol = maxVol;
    vector<Delivery*> vanDeliveries;
    for (i = n; i > 0 && res > 0; i--) { 
          
        //Ifthe result comes from val[i-1] + K[i-1][w-wt[i-1]] it' included. 
        if (res == K[i - 1][vol])  
            continue;         
        else { 
  
            // This item is included.
             
            vanDeliveries.push_back(deliveries[i - 1]); 
              
            // So its value is deducted 
            res = res - val[i - 1]; 
            w = w - wt[i - 1]; 
        } 
    }
    for (int i = 0; i < vanDeliveries.size(); i++){
        cout << "vols: " << vanDeliveries.at(i) << endl;
    } 

    //percorre o vetor deliveries para retirar as emcoment«das que foram colocadas na carrinha
    for (int i = 0; i < vanDeliveries.size(); i++){
      Delivery *toRemove = vanDeliveries.at(i);
    auto e = find(deliveries.begin(), deliveries.end(),
                   [&toRemove](Delivery * j) { return j && (*j == toRemove); });

    if (e != deliveries.end()) {
      deliveries.erase(e);
    }
  }
}

