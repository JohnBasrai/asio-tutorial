#include <iostream>
#include <boost/asio.hpp>

using namespace std;
using namespace boost;

void print(const boost::system::error_code &)
{
    cout << "Hello, world!" << endl;
}

int main()
{
    cout << "__cplusplus " << __cplusplus << endl;

    asio::io_service reactor;
    asio::deadline_timer t2(reactor, posix_time::seconds(5));

    t2.async_wait(&print);
    reactor.run();

    return 0;
}

