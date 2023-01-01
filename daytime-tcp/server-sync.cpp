#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;
namespace ba = boost::asio;
using boost_error_code =
    boost::system::error_code;

string make_daytime_string()
{
    const time_t now = time(0);
    return ctime(&now);
}

int main()
{
    try
    {
        ba::io_service theReactor;
        tcp::acceptor  theAcceptor(
            theReactor, tcp::endpoint(tcp::v4(), IPPORT_DAYTIME));
        for (;;)
        {
            tcp::socket socket(theReactor);
            theAcceptor.accept(socket);
            const string message = make_daytime_string();
            boost_error_code ignored_error;
            ba::write(socket, ba::buffer(message), ignored_error);
        }
    }
    catch (const std::exception& exp)
    {
        cerr << exp.what() << endl;
    }
    return 0;
}

