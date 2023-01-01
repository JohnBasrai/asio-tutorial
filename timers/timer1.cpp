#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

int main(int ac, const char *av[])
{
    asio::io_service reactor;
    asio::deadline_timer t1(reactor, posix_time::seconds(5u));
    t1.wait();
    cout << "Hello world!" << endl;
    return 0;
}


