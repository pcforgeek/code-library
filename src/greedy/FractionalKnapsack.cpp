#include <vector>
#include <algorithm>
#include <iostream>

using std::vector;

class Item {
public:
    int weight{};
    int cost{};

    Item(int weight, int cost) {
        this->weight = weight;
        this->cost = cost;
    }
};

vector<Item> items;

// descending order of cost of unit weight
bool compare(Item a, Item b) {
    double r1 = (double) a.cost / a.weight;
    double r2 = (double) b.cost / b.weight;
    return r1 > r2;
}


double fractionalKnapsack(int sackSize) {
    int filledSize = 0;
    double filledItemsCost = 0.0;
    std::sort(items.begin(), items.end(), compare);
    int pos = 0;
    while (filledSize != sackSize && pos < items.size()) {
        if (items[pos].weight + filledSize <= sackSize) {
            filledSize += items[pos].weight;
            filledItemsCost += items[pos].cost;
        } else if (items[pos].weight + filledSize > sackSize) {
            filledItemsCost += ((double) (sackSize - filledSize) / items[pos].weight) * items[pos].cost;
            filledSize = sackSize;
        }
        ++pos;
    }
    return filledItemsCost;
}

void fractionalKnapsackDriver() {
    items = {Item(10, 60), Item(30, 120), Item(20, 100)};
    std::cout << fractionalKnapsack(50); // 240
}