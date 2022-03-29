/**
 * @author Nikita Mochalov (github.com/tralf-strues)
 * @file networking.h
 * @date 2022-03-29
 *
 * @copyright Copyright (c) 2022
 */

#include <boost/asio.hpp>
#include <string>

namespace rchat {
namespace network {

constexpr size_t RECEIVE_BUFFER_SIZE = 2048;

class Endpoint
{
public:
    /**
     * @brief Construct a new Endpoint object.
     *
     * @param port Port in network byte order.
     */
    Endpoint(int32_t port) : m_Socket(m_IOService), m_ReceiveBuffer(RECEIVE_BUFFER_SIZE) {}

    virtual ~Endpoint() = default;

    /**
     * @brief Sends size bytes to the remote server.
     *
     * @param buffer
     * @param size
     */
    void send(const uint8_t* buffer, size_t size)
    {
        boost::asio::write(m_Socket, boost::asio::buffer(buffer, size), m_ErrorCode);
    }

    /**
     * @brief Reads data from the remote server.
     *
     * @return size_t Bytes received.
     */
    size_t receive()
    {
        m_ReceiveBuffer.consume(m_PrevBytesReceived);
        m_PrevBytesReceived = boost::asio::read_until(m_Socket, m_ReceiveBuffer, "\n");
        return m_PrevBytesReceived;
    }

    /**
     * @brief Get received buffer after call to receive().
     *
     * @tparam T Pointer template parameter, e.g. const char*.
     * @return T Received buffer.
     */
    template<typename T>
    T receiveBuffer()
    {
        return boost::asio::buffer_cast<T>(m_ReceiveBuffer.data());
    }

protected:
    boost::asio::io_service      m_IOService;
    boost::asio::ip::tcp::socket m_Socket;
    boost::system::error_code    m_ErrorCode;
    boost::asio::streambuf       m_ReceiveBuffer;
    size_t                       m_PrevBytesReceived{0};
};

class Client : public Endpoint
{
public:
    /**
     * @brief Construct a new Client object.
     *
     * Connects to the specified remote server.
     *
     * @param ip   IP address in the form of 4 decimal numbers separated by dots.
     * @param port Port in network byte order.
     */
    Client(const char* ip, int32_t port) : Endpoint(port)
    {
        m_Socket.connect(
            boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(ip), port));
    }
};

class Server : public Endpoint
{
public:
    /**
     * @brief Construct a new Server object.
     *
     * @param port Port in network byte order.
     */
    Server(int32_t port)
        : Endpoint(port),
          m_Acceptor(m_IOService, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        m_Acceptor.accept(m_Socket);
    }

private:
    boost::asio::ip::tcp::acceptor m_Acceptor;
};

}
}