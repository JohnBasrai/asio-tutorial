
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/bind/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost_error_code = boost::system::error_code;
using boost::asio::ip::udp;
namespace ba = boost::asio;
using StringPtr = boost::shared_ptr<string>;

StringPtr make_daytime_string()
{
    const auto now = time(nullptr);
    return StringPtr(new string((const char*)ctime(&now)));
}

class UdpServer
{
public:
    UdpServer(ba::io_service & theReactor)
        : theSocket(theReactor, udp::endpoint(udp::v4(), IPPORT_DAYTIME))
    { start_receive(); }
private:
    void start_receive()
    {
        theSocket.async_receive_from(
            ba::buffer(theRecvBuffer), theRemoteEndpoint,
            [this](const boost_error_code & err, const size_t)
            { handle_receive(err); });
    }
    void handle_receive(const boost_error_code & error)
    {
        if (!error || error == ba::error::message_size)
        {
            const auto message = make_daytime_string();
            theSocket.async_send_to(
                ba::buffer(*message), theRemoteEndpoint,
                [message](const boost_error_code&,const size_t){});
            start_receive();
        }
    }
    udp::socket           theSocket;
    udp::endpoint         theRemoteEndpoint;
    boost::array<char, 1> theRecvBuffer;
};

int main()
{
    try
    {
        ba::io_service theReactor;
        UdpServer      theServer(theReactor);

        theReactor.run();
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
