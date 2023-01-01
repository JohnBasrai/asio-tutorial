#include <iostream>
#include <boost/asio.hpp>
#include <thread>
using namespace boost;
using namespace std;
using boost_error_code = boost::system::error_code;

namespace ba = boost::asio;
class Timer5 {
    ba::io_context::strand    theStrand;
    ba::deadline_timer        theTimer1;
    ba::deadline_timer        theTimer2;
    int                       theCount;
    void print1();
    void print2();
public:
    Timer5(ba::io_service& theReactor)
        : theStrand(theReactor)
        , theTimer1(theReactor, posix_time::seconds(1))
        , theTimer2(theReactor, posix_time::seconds(1))
        , theCount(0)
    {
        theTimer1.async_wait(theStrand.wrap([this](const boost_error_code&){print1();}));
        theTimer2.async_wait(theStrand.wrap([this](const boost_error_code&){print2();}));
    }
    ~Timer5() {cout << "Final count is " << theCount << endl;}
};

int main()
{
  ba::io_service theReactor;
  Timer5 t5(theReactor);
  thread t1([&theReactor](){theReactor.run();});
  thread t2([&theReactor](){theReactor.run();});
  t1.join(); t2.join();
}

void Timer5::print1()
{
    if (theCount < 10)
    {
        cout << "Timer 1: " << theCount << "\n"; ++theCount;
        theTimer1.expires_at(theTimer1.expires_at() + posix_time::seconds(1u));
        theTimer1.async_wait(theStrand.wrap([this](const boost_error_code&){print1();}));
    }
}

void Timer5::print2()
{
    if (theCount < 10)
    {
        cout << "Timer 2: " << theCount << "\n"; ++theCount;
        theTimer2.expires_from_now(posix_time::seconds(1u));
        theTimer2.async_wait(theStrand.wrap([this](const boost_error_code&){print2();}));
    }
}
