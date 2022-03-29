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

void runServerClient(int32_t port, rchat::User user)
{
    rchat::network::Server server{DEFAULT_PORT};

    while (true)
    {
        server.receive();

        const std::string received{server.receiveBuffer<const char*>()};
        rchat::Message message;
        rchat::deserializeMessage(&message, received);

        fmt::print("Server received message: sender='{}', text='{}'\n", message.sender.name, message.text);
    }
}

void runRegularClient(int32_t port, rchat::User user)
{
    rchat::network::Client client("127.0.0.1", DEFAULT_PORT);

    rchat::Message message(user, "Hello from Client!\n");
    
    std::string serializedMessage = rchat::serializeMessage(message);
    client.send(reinterpret_cast<const uint8_t*>(serializedMessage.data()),
                serializedMessage.length() + 1);
    
    // size_t bytesReceived = client.receive();
    // const char* data = client.receiveBuffer<const char*>();
    // fmt::print("Server received message: sender='{}', text='{}'\n", message.sender.name, message.text);
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

    int32_t port = result["port"].as<int32_t>();

    // if (result.count("port") > 0)
    // {
    //     port = result["port"].as<unsigned>();
    // }
    // else
    // {
    //     fmt::print("You have to specify port on which to be based! Please see help for more information!\n");
    //     return 0;
    // }

    fmt::print("HERE?\n");

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
        runServerClient(port, rchat::User(username));
    }
    else
    {
        runRegularClient(port, rchat::User(username));
    }

    // rchat::network::Server server(1234);
    
    // server.receive();
    // const std::string msg{server.receiveBuffer<const char*>()};
    // std::cout << msg << std::endl;

    // server.send(reinterpret_cast<const uint8_t*>("Hello From Server!"), sizeof("Hello From Server!"));
    // std::cout << "Servent sent Hello message to Client!" << std::endl;

    // boost::asio::io_service ioService;

    // // listen for new connection
    // boost::asio::ip::tcp::acceptor acceptor(ioService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), 1234));

    // // socket creation
    // boost::asio::ip::tcp::socket socket(ioService);

    // // waiting for connection
    // acceptor.accept(socket);

    // // read operation
    // std::string message = read(socket);
    // std::cout << message << std::endl;

    // // write operation
    // send(socket, "Hello From Server!");
    // std::cout << "Servent sent Hello message to Client!" << std::endl;

    return 0;
}