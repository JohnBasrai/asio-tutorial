
#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost_error_code = boost::system::error_code;
using boost::asio::ip::udp;
namespace ba = boost::asio;

string make_daytime_string()
{
    const auto now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        ba::io_service theReactor;
        udp::socket    theSocket(theReactor, udp::endpoint(udp::v4(), 13));

        for (;;)
        {
            boost::array<char, 1> theRecvBuf;
            udp::endpoint         theRemoteEndpoint;
            boost_error_code      error;

            theSocket.receive_from(
                ba::buffer(theRecvBuf), theRemoteEndpoint, 0, error);

            if (error && error != ba::error::message_size)
                throw boost::system::system_error(error);

            const string message = make_daytime_string();

            boost_error_code ignored_error;

            theSocket.send_to(
                ba::buffer(message), theRemoteEndpoint, 0, ignored_error);
        }
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
