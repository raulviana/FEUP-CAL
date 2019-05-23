#include "van.h"

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
std::vector<Van *> Van::calcVans()
{
  /*std::vector<Delivery *> deliveries = map->getDeliveries();
  std::vector<Van *> vans;
  std::vector<Delivery *> items;
  std::vector<int> cost;
  std::vector<int> best;

  for (int i = 1; i <= deliveries.size(); i++)
  {
    for (int k = deliveries.at(i)->getVolume(); k <= vans.at(i)->getMaxVol(); k++)
    {
      if (deliveries.at(i) + cost[k - size[i]] > cost[k])
      {
        cost[k] = deliveries.at(i) + cost[k - size[i]];
        best[k] = i;
      }
    }
    */
}