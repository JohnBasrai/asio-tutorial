#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>

using boost::asio::ip::tcp;
using namespace std;
namespace ba = boost::asio;
using boost_error_code = boost::system::error_code;

int main(int argc, char* argv[])
{
    const auto host = (argc == 2 ? argv[1] : "localhost");
    try
    {
        ba::io_service          theReactor;
        tcp::resolver           resolver(theReactor);
        tcp::resolver::query    query(host, "daytime");
        tcp::resolver::iterator endpoint_iter = resolver.resolve(query);

        tcp::socket socket(theReactor);
        ba::connect(socket, endpoint_iter); // Synchronous connect
        while(true)
        {
            boost::array<char, 128> buf;
            boost_error_code error;
            const size_t len = socket.read_some(ba::buffer(buf), error); // blocking read
            if (error)
            {
                if (error == ba::error::eof) break;       // Connection closed cleanly by peer.
                throw boost::system::system_error(error); // Some other error.
            }
            cout.write(buf.data(), len);
        }
    }
    catch (const std::exception& exp)
    {
        cerr << exp.what() << endl;
    }
    return 0;
}

