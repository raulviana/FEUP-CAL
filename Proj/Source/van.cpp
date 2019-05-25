#include "van.h"

#include <vector>
#include <climits>
#include <algorithm>

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

void Van::setMaxVol(int volume)
{
  this->maxVol = volume;
}

void Van::addDelivery(Delivery *delivery)
{
  deliveries.push_back(delivery);
}

std::vector<Delivery *> Van::calcVans(Map *map)
{
  setMaxVol(40);
  return distributeDeliveries(*map->getDeliveries()); // knapsack problem
}

vector<Delivery *> Van::distributeDeliveries(vector<Delivery *> &deliveries)
{
  int w;
  vector<int> volumes;

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
        V[i][w] = max(volumes.at(i - 1) + V[i - 1][w - volumes.at(i - 1)], V[i - 1][w]);
      else
        V[i][w] = V[i - 1][w];
    }
  }

  // stores the result of the knapsack
  int res = V[n][maxVol];
  vector<Delivery *> vanDeliveries;

  for (unsigned int i = 0; i <= n; i++)
  {
    for (unsigned int j = 0; j <= w - 1; j++)
      std::cout << V[i][j] << "     ";

    std::cout << endl;
  }
  std::cout << res << endl;

  for (unsigned int i = n; i > 0 && res > 0; i--)
  {
    // if the result comes from val[i-1] + V[i-1][w-volumes[i-1]] it's included
    if (res == V[i - 1][maxVol])
      continue;
    else
    {
      // this item is included
      vanDeliveries.push_back(deliveries[i - 1]);

      // its value is deducted
      res = res - volumes[i - 1];
    }
  }

  for (unsigned int i = 0; i < vanDeliveries.size(); i++)
  {
    std::cout << "invoice = " << vanDeliveries.at(i)->getInvoiceNumber() << " vol: " << vanDeliveries.at(i)->getVolume() << endl;
  }

  // percorre o vetor deliveries para retirar as encomendas que foram colocadas na carrinha
  for (auto i = vanDeliveries.begin(); i != vanDeliveries.end(); i++)
  {
    auto it = deliveries.end();

    if ((it = find(deliveries.begin(), deliveries.end(), *i)) != deliveries.end())
    {
      deliveries.erase(it);
    }

    /*for (auto iter = deliveries.begin(); iter != deliveries.end(); iter++)
    {
      if ((*iter)->getInvoiceNumber() == (*i)->getInvoiceNumber())
      {
        deliveries.erase(iter);
        break;
      }
    }*/
  }

  return vanDeliveries;
}