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

namespace {
    enum OrderType
    {
        BUY = 1,
        SELL = 2
    };

    struct Order
    {
        int volume;
        double price;
        OrderType type;
        int userId;

        Order(int volume, double price, OrderType type, int userId)
            : volume(volume)
            , price(price)
            , type(type)
            , userId(userId) 
        {
        }
    };

    struct User {
        int id;
        double usdBalance;
        double rubBalance;

        User(int id) 
            : id(id)
            , usdBalance(0)
            , rubBalance(0) 
        {
        }

        void updateBalance(double usd, double rub) {
            usdBalance += usd;
            rubBalance += rub;
        }
    };
}



#endif //CLIENSERVERECN_COMMON_HPP
