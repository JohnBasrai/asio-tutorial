
#include <boost/asio.hpp>

#include <iostream>
#include <netinet/in.h>
#include <string>

using namespace std;
using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    const auto host = (argc == 2 ? argv[1] : "localhost");
    try
    {
        // Establish a connection to an endpoint corresponding to a resolver query
        tcp::iostream strm(host, "daytime");
        if (!strm)
        {
            cout << "Unable to connect: " << strm.error().message() << endl;
            return 1;
        }
        string line;
        getline(strm, line);
        cout << line << endl;
    }
    catch (const std::exception& exp)
    {
        cout << "Exception: " << exp.what() << endl;
    }
    return 0;
}

