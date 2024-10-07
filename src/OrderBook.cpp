#include "OrderBook.h"
#include "Common.hpp"

#include <algorithm>

void OrderBook::AddOrder(const Order& order) 
{
    if (order.type == OrderType::BUY) {
        buyOrders.push_back(order);
        std::sort(buyOrders.begin(), buyOrders.end(), [](const Order& a, const Order& b) {
            return a.price > b.price;
        });
    } else {
        sellOrders.push_back(order);
        std::sort(sellOrders.begin(), sellOrders.end(), [](const Order& a, const Order& b) {
            return a.price < b.price;
        });
    }
}

void OrderBook::RemoveOrder(const Order& order) 
{
    if (order.type == OrderType::BUY) {
        auto it = std::find_if(buyOrders.begin(), buyOrders.end(), [&order](const Order& o) {
            return o.userId == order.userId && o.price == order.price && o.volume == order.volume;
        });
        if (it != buyOrders.end()) {
            buyOrders.erase(it);
        }
    } else {
        auto it = std::find_if(sellOrders.begin(), sellOrders.end(), [&order](const Order& o) {
            return o.userId == order.userId && o.price == order.price && o.volume == order.volume;
        });
        if (it != sellOrders.end()) {
            sellOrders.erase(it);
        }
    }
}

const std::vector<Order>& OrderBook::getBuyOrders() const {
    return buyOrders;
}

const std::vector<Order>& OrderBook::getSellOrders() const {
    return sellOrders;
}