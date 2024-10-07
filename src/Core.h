#pragma once

#include "OrderBook.h"

#include <string>
#include <map>

class Core
{
public:
    // "Регистрирует" нового пользователя и возвращает его ID.
    std::string RegisterNewUser(const std::string& aUserName);

    // Запрос имени клиента по ID
    std::string GetUserName(const std::string& aUserId);

    void ProcessBuy(const std::string& clientId, const std::string& count, const std::string& price);
    void ProcessSale(const std::string& clientId, const std::string& count, const std::string& price);

    std::string GetBill();

private:
    // <UserId, UserName>
    std::map<size_t, std::string> mUsers;
    OrderBook mOrderBook;
};

Core& GetCore();