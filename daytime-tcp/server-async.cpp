
#include <ctime>
#include <iostream>
#include <string>
#include <Refcountable.hh>
#include <boost/asio.hpp>
#include <boost/bind/bind.hpp>
#include <boost/intrusive_ptr.hpp>

using boost::asio::ip::tcp;
using namespace std;
namespace ba = boost::asio;
using boost_error_code =
    boost::system::error_code;

namespace daytime
{
    template<typename T> void intrusive_ptr_add_ref(T * p) { p->_addRef_(); }
    template<typename T> void intrusive_ptr_release(T * p) { p->_decRef_(); }

    string make_daytime_string()
    {
        const auto now = time(nullptr);
        return ctime(&now);
    }
    class TcpConnection;
    using TcpConnectionPtr = boost::intrusive_ptr<TcpConnection>;

    class TcpConnection : public util::Refcountable
    {
    private:
        TcpConnection(ba::io_service & reactor) : theSocket(reactor) {}

        tcp::socket theSocket;
        string      theMessage;
    public:
        static TcpConnectionPtr create(ba::io_service & reactor)
        {
            return new TcpConnection(reactor); 
        }
        tcp::socket & socket() { return theSocket; }

        void start()
        {
            theMessage = make_daytime_string();
            ba::async_write(theSocket, ba::buffer(theMessage),
                            [this](const boost_error_code &err,size_t){});
        }
    };

    class TcpServer
    {
    public:
        TcpServer(ba::io_service & reactor)
            : theReactor(reactor)
            , theAcceptor(reactor, tcp::endpoint(tcp::v4(), IPPORT_DAYTIME))
        { start_accept(); }

    private:
        void start_accept()
        {
            const auto conn = TcpConnection::create(theReactor);

            theAcceptor.async_accept(
                conn->socket(),
                [this, conn_new{conn} ](const boost_error_code & err)
                {
                    this->handle_accept(conn_new, err);
                });
        }
        void handle_accept(
            const TcpConnectionPtr & new_conn, const boost_error_code & err)
        {
            if (!err)
                new_conn->start();
            start_accept();
        }
        ba::io_service &theReactor;
        tcp::acceptor   theAcceptor;
    };
} // end namespace daytime

int main()
{
    try
    {
        ba::io_service     theReactor;
        daytime::TcpServer theServer(theReactor);

        theReactor.run();
    }
    catch (const std::exception & exp)
    {
        cerr << exp.what() << endl;
    }
}

