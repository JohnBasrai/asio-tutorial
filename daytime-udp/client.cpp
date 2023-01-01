
#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::udp;
namespace ba = boost::asio;

int main(int argc, char* argv[])
{
    const auto host = (argc == 2 ? argv[1] : "localhost");
    try
    {
        ba::io_service          theReactor;
        udp::resolver           theResolver(theReactor);
        udp::resolver::query    theQuery(udp::v4(), host, "daytime");
        udp::endpoint           theEndpoint = *theResolver.resolve(theQuery);
        udp::socket             theSocket(theReactor);

        theSocket.open(udp::v4());

        boost::array<char, 1> theSendBuf  = {{ 0 }};
        theSocket.send_to(ba::buffer(theSendBuf), theEndpoint);

        boost::array<char, 128> theRecvBuf;
        udp::endpoint           theRemoteEndpoint;
        const size_t len = theSocket.receive_from(ba::buffer(theRecvBuf), theRemoteEndpoint);

        cout.write(theRecvBuf.data(), len);
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
    }
    return 0;
}
