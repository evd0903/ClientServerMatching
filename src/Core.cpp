#include "Core.h"

// "Регистрирует" нового пользователя и возвращает его ID.
std::string Core::RegisterNewUser(const std::string& aUserName)
{
    size_t newUserId = mUsers.size();
    mUsers[newUserId] = aUserName;

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
        return userIt->second;
    }
}

void Core::ProcessBuy(const std::string& clientId, const std::string& count, const std::string& price);
void Core::ProcessSale(const std::string& clientId, const std::string& count, const std::string& price);

std::string Core::GetBill();

Core& GetCore()
{
    static Core core;
    return core;
}