#include <iostream>
#include <boost/asio.hpp>

int main()
{
    boost::asio::io_context io;
    boost::asio::ip::tcp::socket sock(io);
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> ewg = boost::asio::make_work_guard(io);
    std::string remote_addr = "127.0.0.1";
    boost::asio::ip::port_type port = 7890;
    boost::asio::ip::address addr = boost::asio::ip::address::from_string(remote_addr);
    boost::asio::ip::tcp::endpoint remote_endpoint(addr, port);

    sock.connect(remote_endpoint);
    std::string msg = "Hello socket";

    sock.async_write_some(
            boost::asio::buffer(msg.c_str(), msg.size()),
            [&](const boost::system::error_code &ec, std::size_t bytes)
            {
                if(ec)
                {
                    std::cout << "We encountered error: \"" << ec.message() << "\"" << std::endl;
                    return;
                }
                std::cout << "We have written " << bytes << " bytes" << std::endl;
            }
                );
    io.run();
    return 0;
}
