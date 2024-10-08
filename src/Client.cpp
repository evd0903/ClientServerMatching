#include <iostream>
#include <boost/asio.hpp>

#include "Common.hpp"
#include "json.hpp"

using boost::asio::ip::tcp;

// Отправка сообщения на сервер по шаблону.
void SendMessage(
    tcp::socket& aSocket,
    const std::string& aId,
    const std::string& aRequestType,
    const std::string& aMessage = "",
    const std::string& aPrice = "",
    const std::string& aVolume = "")
{
    nlohmann::json req;
    req["UserId"] = aId;
    req["ReqType"] = aRequestType;
    req["Message"] = aMessage;

    if (aRequestType == Requests::Buy || aRequestType == Requests::Sale) 
    {
        req["Price"] = aPrice;
        req["Volume"] = aVolume;
    }

    std::string request = req.dump();
    boost::asio::write(aSocket, boost::asio::buffer(request, request.size()));
}

// Возвращает строку с ответом сервера на последний запрос.
std::string ReadMessage(tcp::socket& aSocket)
{
    boost::asio::streambuf b;
    boost::asio::read_until(aSocket, b, "\0");
    std::istream is(&b);
    std::string line(std::istreambuf_iterator<char>(is), {});
    return line;
}

// "Создаём" пользователя, получаем его ID.
std::string ProcessRegistration(tcp::socket& aSocket)
{
    std::string name;
    std::cout << "Hello! Enter your name: ";
    std::cin >> name;

    // Для регистрации Id не нужен, заполним его нулём
    SendMessage(aSocket, "0", Requests::Registration, name);
    return ReadMessage(aSocket);
}

int main()
{
    try
    {
        boost::asio::io_service io_service;

        tcp::resolver resolver(io_service);
        tcp::resolver::query query(tcp::v4(), "127.0.0.1", std::to_string(port));
        tcp::resolver::iterator iterator = resolver.resolve(query);

        tcp::socket s(io_service);
        s.connect(*iterator);

        // Мы предполагаем, что для идентификации пользователя будет использоваться ID.
        // Тут мы "регистрируем" пользователя - отправляем на сервер имя, а сервер возвращает нам ID.
        // Этот ID далее используется при отправке запросов.
        std::string my_id = ProcessRegistration(s);

        while (true)
        {
            // Тут реализовано "бесконечное" меню.
            std::cout << "Menu:\n"
                         "1) New buy\n"
                         "2) New Sell\n"
                         "3) Get bill\n"
                         "4) Exit\n"
                         << std::endl;

            short menu_option_num;
            std::cin >> menu_option_num;
            switch (menu_option_num)
            {
                case 1:
                {
                    std::string price, volume;
                    std::cout << "Enter purchase price USD : " << std::endl;
                    std::cin >> price;
                    std::cout << "Enter purchase volume USD : " << std::endl;
                    std::cin >> volume;
                    SendMessage(s, my_id, Requests::Buy, " ", price, volume);
                    break;
                }
                case 2:
                {
                    std::string price, volume;
                    std::cout << "Enter sales price USD : " << std::endl;
                    std::cin >> price;
                    std::cout << "Enter sales volume USD : " << std::endl;
                    std::cin >> volume;
                    SendMessage(s, my_id, Requests::Sale, " ", price, volume);
                    break;
                }
                case 3:
                {
                    SendMessage (s, my_id, Requests::Bill);
                    std::cout << ReadMessage (s);
                    break;
                }
                default:
                {
                    std::cout << "Unknown menu option\n" << std::endl;
                }
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}