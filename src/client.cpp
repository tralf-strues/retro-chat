/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file client.cpp
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#include <iostream>

#include "network_system.h"

int main()
{
    rchat::network::Client client("127.0.0.1", 1234);
    
    const std::string msg = "Hello from Client!\n";
    client.send(reinterpret_cast<const uint8_t*>(msg.data()), msg.length() + 1);

    std::cout << "Client sent hello message!\n";
    
    size_t bytesReceived = client.receive();

    const char* data = client.receiveBuffer<const char*>();
    std::cout << data << std::endl;

    // boost::asio::io_service io_service;

    // // socket creation
    // tcp::socket socket(io_service);

    // // connection
    // socket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 1234));

    // // request/message from client
    // const string              msg = "Hello from Client!\n";
    // boost::system::error_code error;

    // boost::asio::write(socket, boost::asio::buffer(msg), error,);

    // if (!error)
    // {
    //     cout << "Client sent hello message!" << endl;
    // }
    // else
    // {
    //     cout << "send failed: " << error.message() << endl;
    // }

    // // getting response from server
    // boost::asio::streambuf receive_buffer(4096);
    // boost::asio::read(socket, receive_buffer, boost::asio::transfer_all(), error);

    // if (error && error != boost::asio::error::eof)
    // {
    //     cout << "receive failed: " << error.message() << endl;
    // }
    // else
    // {
    //     const char* data = boost::asio::buffer_cast<const char*>(receive_buffer.data());
    //     cout << data << endl;
    // }

    return 0;
}