#include <chrono>

#include "Core.h"
#include "Common.hpp"

// "Регистрирует" нового пользователя и возвращает его ID.
std::string Core::RegisterNewUser(const std::string& aUserName)
{
    size_t newUserId = mUsers.size();
    User tmp(newUserId, aUserName);
    mUsers[newUserId] = tmp;

    return std::to_string(newUserId);
}

// Запрос имени клиента по ID
std::string Core::GetUserName(const std::string& aUserId)
{
    const auto userIt = mUsers.find(std::stoi(aUserId));
    if (userIt == mUsers.cend())
    {
        return "Error! Unknown User";
    }
    else
    {
        return userIt->second.name;
    }
}

std::string Core::GetUserBalance(const std::string& aUserId)
{
    const auto userIt = mUsers.find(std::stoi(aUserId));
    if (userIt == mUsers.cend())
    {
        return "Error! Unknown User";
    }
    else
    {
        const User& user = userIt->second;
        return "USD: " + std::to_string(user.usdBalance) + ", RUB: " + std::to_string(user.rubBalance) + "\n";
    }
}

void Core::addOrder(const Order& order)
{
    if (order.type == OrderType::BUY) {
        matchOrders(order, mOrderBook.getSellOrders());
    } else {
        matchOrders(order, mOrderBook.getBuyOrders());
    }
}

void Core::matchOrders(const Order& newOrder, const std::vector<Order>& existingOrders)
{
    int remainingVolume = newOrder.volume;
    for (const auto& existingOrder : existingOrders) {
        if (remainingVolume <= 0) break;
        if (areOrdersIntersecting(newOrder, existingOrder)) {
            int tradeVolume = std::min(remainingVolume, existingOrder.volume);
            double tradePrice = getTradePrice(newOrder, existingOrder);

            executeTrade(newOrder, existingOrder, tradeVolume, tradePrice);

            remainingVolume -= tradeVolume;

            if (tradeVolume == existingOrder.volume) {
                mOrderBook.RemoveOrder(existingOrder);
            }
        }
    }

    if (remainingVolume > 0) {
        handleRemainingOrder(newOrder, remainingVolume);
    }
}

bool Core::areOrdersIntersecting(const Order& newOrder, const Order& existingOrder) const
{
    return (newOrder.type == OrderType::BUY && newOrder.price >= existingOrder.price) ||
           (newOrder.type == OrderType::SELL && newOrder.price <= existingOrder.price);
}

double Core::getTradePrice(const Order& newOrder, const Order& existingOrder) const
{
    return newOrder.timestamp < existingOrder.timestamp ? newOrder.price : existingOrder.price;
}

void Core::executeTrade(const Order& newOrder, const Order& existingOrder, int tradeVolume, double tradePrice)
{
    mUsers[newOrder.userId].updateBalance(-tradeVolume, tradeVolume * tradePrice);
    mUsers[existingOrder.userId].updateBalance(tradeVolume, -tradeVolume * tradePrice);
}

void Core::handleRemainingOrder(const Order& newOrder, int remainingVolume)
{
    Order remainingOrder = newOrder;
    remainingOrder.volume = remainingVolume;
    mOrderBook.AddOrder(remainingOrder);
}

int Core::getCurrentTimestamp()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void Core::reset()
{
    mOrderBook.reset();
    mUsers.clear();
}

Core& GetCore()
{
    static Core core;
    return core;
}