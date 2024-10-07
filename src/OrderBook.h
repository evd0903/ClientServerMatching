#pragma once

#include "Common.hpp"

#include <vector>

class OrderBook 
{
public:
    void AddOrder(const Order& order);
    void RemoveOrder(const Order& order);
    const std::vector<Order>& getBuyOrders() const;
    const std::vector<Order>& getSellOrders() const;

private:
    std::vector<Order> buyOrders;
    std::vector<Order> sellOrders;
};