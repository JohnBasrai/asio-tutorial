
#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost;
using namespace std;
using boost_error_code = boost::system::error_code;

class Timer4 {
    asio::deadline_timer theTimer;
    int                  theCount;

    void startTimer() {
        theTimer.expires_from_now(posix_time::seconds(1));
        theTimer.async_wait([this](const boost_error_code&err){print();});
    }
    void print() {
        if (theCount < 5) {
            cout << theCount << "\n";
            ++theCount;
            startTimer();
        }
    }
public:
    Timer4(asio::io_service & reactor) : theTimer(reactor) , theCount(0) { startTimer(); }
    ~Timer4() {cout << "Final count is " << theCount << "\n";}
};
int main() {
    asio::io_service theReactor;
    const Timer4     t4(theReactor);
    theReactor.run();
}

