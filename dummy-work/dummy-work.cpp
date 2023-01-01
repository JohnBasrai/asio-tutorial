#include <iostream>
#include <boost/asio.hpp>
#include <thread>
using namespace std;
namespace ba = boost::asio;

int main()
{
  ba::io_service       theReactor;
  ba::io_service::work theDummyWork(theReactor);

  thread t1([&theReactor]()
  {
      cout << "Calling theReactor.run()." << endl;
      theReactor.run();
      cout << "theReactor.run() returned." << endl;
  });
  sleep(3);
  cout << "Calling theReactor.stop()." << endl;
  theReactor.stop();
  t1.join();
}


