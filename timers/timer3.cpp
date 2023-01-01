#include <iostream>
#include <boost/asio.hpp>

using namespace boost;
using error_code = boost::system::error_code;
void startTimer(asio::deadline_timer & t, int &);

void print(const error_code & , asio::deadline_timer & t, int & count)
{
    if( count-- == 0 ) return;
    std::cout << count << std::endl;
    startTimer(t,count);
}

void startTimer(asio::deadline_timer & t, int & count)
{
    t.expires_from_now(posix_time::seconds(1u));
    t.async_wait([&t,&count](const error_code &err){print(err, t, count);
    });
}
int main()
{
    asio::io_service reactor;
    auto count = 5;
    asio::deadline_timer t(reactor);
    startTimer(t,count);
    reactor.run();
    return 0;
}

