
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

using namespace std;
using boost::asio::ip::udp;
namespace ba = boost::asio;

int main(int argc, char* argv[])
{
    ba::io_service theReactor;

    if( argc < 3 )
    {
        cout << "Usage:" << argv[0] << " <local-ip> <port>" << endl;
        exit(1);
    }
    const auto host = string(argv[1]);
    const auto port = boost::lexical_cast<short>(argv[2]);

    cout << "host/port " << host << '/' << port << endl;

    try
    {
        const auto address  = ba::ip::address::from_string(host);
        const auto endpoint = udp::endpoint(address, port);

        udp::socket theSocket(theReactor, endpoint);

        while (true)
        {
            boost::array<char, 8192> theRecvBuf;
            udp::endpoint            theRemoteEndpoint;

            const size_t len = theSocket.receive_from(
                ba::buffer(theRecvBuf), theRemoteEndpoint);

            cout << "Got " << len << " bytes from " << theRemoteEndpoint
                 << " -> " << host << ':' << port << endl;
        }
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
