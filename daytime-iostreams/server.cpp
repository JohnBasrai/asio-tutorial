
#include <boost/asio.hpp>

#include <iostream>
#include <ctime>
#include <string>

using namespace std;
using boost_error_code = boost::system::error_code;
using boost::asio::ip::tcp;
namespace ba = boost::asio;

string make_daytime_string()
{
    const auto now = time(nullptr);
    return ctime(&now);
}

int main()
{
    try
    {
        ba::io_service theReactor;
        tcp::endpoint  theEndpoint(tcp::v4(), IPPORT_DAYTIME);
        tcp::acceptor  theAcceptor(theReactor, theEndpoint);

        for (;;)
        {
            tcp::iostream theStream;
            boost_error_code ec;
            theAcceptor.accept(theStream.socket(), ec);
            if (!ec)
                theStream << make_daytime_string();
            else
                std::cerr << "accept error:" << ec << endl;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Caught:" << e.what() << std::endl;
    }
    return 0;
}
