#ifndef CLIENSERVERECN_COMMON_HPP
#define CLIENSERVERECN_COMMON_HPP

#include <string>

static short port = 5555;

namespace Requests
{
    static std::string Registration     = "Reg";
    static std::string Buy              = "Buy";
    static std::string Sale             = "Sale";
    static std::string Bill             = "Bill";
}

enum OrderType
{
    BUY = 1,
    SELL = 2
};

struct Order
{
    Order() = default;
    Order(int volume, double price, OrderType type, int userId, int timestamp)
        : volume(volume)
        , price(price)
        , type(type)
        , userId(userId)
        , timestamp(timestamp)
    {
    }

    int volume;
    double price;
    OrderType type;
    int userId;
    int timestamp;
};

struct User 
{
    User() = default;
    User(int id, std::string name) 
        : id(id)
        , usdBalance(0)
        , rubBalance(0)
        , name(name)
    {
    }

    int id;
    std::string name;
    double usdBalance;
    double rubBalance;

    void updateBalance(double usd, double rub) {
        usdBalance += usd;
        rubBalance += rub;
    }
};

#endif //CLIENSERVERECN_COMMON_HPP
