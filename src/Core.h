#pragma once

#include "OrderBook.h"

#include <string>
#include <map>

class Core {
public:
    // "Регистрирует" нового пользователя и возвращает его ID.
    std::string RegisterNewUser(const std::string& aUserName);

    // Запрос имени клиента по ID
    std::string GetUserName(const std::string& aUserId);

    // Запрос баланса клиента по ID
    std::string GetUserBalance(const std::string& aUserId);

    void addOrder(const Order& order);

    int getCurrentTimestamp();

private:
    void matchOrders(const Order& newOrder, const std::vector<Order>& existingOrders);

    bool areOrdersIntersecting(const Order& newOrder, const Order& existingOrder) const;

    double getTradePrice(const Order& newOrder, const Order& existingOrder) const;

    void executeTrade(const Order& newOrder, const Order& existingOrder, int tradeVolume, double tradePrice);

    void handleRemainingOrder(const Order& newOrder, int remainingVolume);

private:
    // <UserId, User>
    std::map<size_t, User> mUsers;
    OrderBook mOrderBook;
};

Core& GetCore();