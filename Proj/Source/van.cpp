#include "van.h"

#include <vector>
#include <climits>
#include <algorithm>

Van::Van(int maxVolume)
{
  this->maxVol = maxVolume;
};

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

void Van::setMaxVol(int volume)
{
  this->maxVol = volume;
}

void Van::addDelivery(Delivery *delivery)
{
  deliveries.push_back(delivery);
}

void Van::calcVans(std::vector<Delivery *> &deliveries)
{
  distributeDeliveries(deliveries); // knapsack problem
}

void Van::distributeDeliveries(std::vector<Delivery *> &deliveries)
{
  int w;
  std::vector<int> volumes;

  for (auto del = deliveries.begin(); del != deliveries.end(); del++)
  {
    volumes.push_back((*del)->getVolume());
  }

  size_t n = volumes.size();

  int V[n + 1][maxVol + 1];

  // table V[][] in bottom up manner
  for (unsigned int i = 0; i <= n; i++)
  {
    for (w = 0; w <= maxVol; w++)
    {
      if (i == 0 || w == 0)
        V[i][w] = 0;
      else if (volumes[i - 1] + V[i - 1][w - volumes.at(i - 1)] <= w)
        V[i][w] = std::max(volumes.at(i - 1) + V[i - 1][w - volumes.at(i - 1)], V[i - 1][w]);
      else
        V[i][w] = V[i - 1][w];
    }
  }

  // stores the result of the knapsack
  int res = V[n][maxVol];
  std::vector<Delivery *> vanDeliveries;

  for (unsigned int i = n; i > 0 && res > 0; i--)
  {
    // if the result comes from val[i-1] + V[i-1][w-volumes[i-1]] it's included
    if (res != V[i - 1][maxVol])
    {
      // this item is included
      vanDeliveries.push_back(deliveries[i-1]);

      // its value is deducted
      res -= volumes[i - 1];
    }
  }

  // percorre o vetor deliveries para retirar as encomendas que foram colocadas na carrinha
  for (auto i = vanDeliveries.begin(); i != vanDeliveries.end(); i++)
  {
    auto it = deliveries.end();

    if ((it = find(deliveries.begin(), deliveries.end(), *i)) != deliveries.end())
    {
      deliveries.erase(it);
    }

  }

  this->deliveries = vanDeliveries;
}