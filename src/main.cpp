/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file main.cpp
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#include <boost/asio.hpp>
#include "cxxopts.hpp"
#include <iostream>

#include "network_system.h"
#include "chat.h"

constexpr int32_t DEFAULT_PORT = 1234;

template<typename TEndpoint>
void runEndpoint(TEndpoint& endpoint, rchat::User user)
{
    std::thread receiveThread{[&]() {
        while (true)
        {
            endpoint.receive();

            const char* received = endpoint.template receiveBuffer<const char*>();
            rchat::Message message;
            rchat::deserializeMessage(&message, received);

            fmt::print("Received message: sender='{}', text='{}'\n", message.sender.name, message.text);
        }
    }};

    std::string messageToSend;

    while (true)
    {
        std::getline(std::cin, messageToSend);

        rchat::Message message(user, fmt::format("{}", messageToSend));

        std::string serializedMessage = rchat::serializeMessage(message);
        endpoint.send(reinterpret_cast<const uint8_t*>(serializedMessage.data()), serializedMessage.length());
        endpoint.send(reinterpret_cast<const uint8_t*>("\n"), 1);
    }
}

int32_t main(int32_t argc, const char* argv[])
{
    cxxopts::Options options("retro-chat", "Simple terminal chat");
    options.add_options()("h,help", "Help")
                         ("p,port", "Port on which to be based", cxxopts::value<int32_t>()->default_value("1234"))
                         ("u,username", "Username", cxxopts::value<std::string>())
                         ("s,server", "Run as a chat server");

    auto result = options.parse(argc, argv);

    if (result.count("help") > 0)
    {
        fmt::print("{}\n", options.help());
        return 0;
    }

    int32_t port = result["port"].as<int32_t>();;

    std::string username;

    if (result.count("username") > 0)
    {
        username = result["username"].as<std::string>();
    }
    else
    {
        fmt::print("You have to specify username! Please see help for more information!\n");
        return 0;
    }

    bool isServer = result.count("server") > 0;

    if (isServer)
    {
        rchat::network::Server server{port};
        runEndpoint(server, rchat::User(username));
    }
    else
    {
        rchat::network::Client client{"127.0.0.1", port};
        runEndpoint(client, rchat::User(username));
    }

    return 0;
}