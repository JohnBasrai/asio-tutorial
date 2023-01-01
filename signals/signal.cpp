
#include <signal.h>             // for kill
#include <unistd.h>             // for getpid
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

using namespace std;
using boost_error_code = boost::system::error_code;
namespace ba = boost::asio;

void handler(const boost_error_code & error, const int signal_number)
{
    if (!error)
    {
        cout << "Caught signal " << signal_number
             << " pthread_t " << pthread_self() << endl;
        return;
    }
    cout << "Error:" << error.message() << endl;
}

int main(int ac, const char *av[])
{
    cout << "Main running" << " pthread_t " << pthread_self() << endl;

    ba::io_service     theReactor;
    ba::signal_set     signalSet(theReactor, SIGINT, SIGTERM);
    ba::deadline_timer timer1(theReactor, boost::posix_time::seconds(5u));
    
    signalSet.async_wait(handler);

    timer1.async_wait([](const boost_error_code&err)
    {
        kill(getpid(), SIGTERM);
    });
    theReactor.run();
    cout << "Main exiting" << endl;
    return 0;
}

