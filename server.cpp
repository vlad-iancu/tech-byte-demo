#include <iostream>
#include <string>
#include <array>
#include <boost/asio.hpp>

int main()
{
    std::string local_addr = "127.0.0.1";
    boost::asio::ip::port_type port = 7890;
    boost::asio::ip::address address = boost::asio::ip::address::from_string(local_addr);
    boost::asio::ip::tcp::endpoint local_endpoint(address, port);

    boost::asio::io_context io;
    boost::asio::executor_work_guard<boost::asio::io_context::executor_type> ewg = boost::asio::make_work_guard(io);

    boost::asio::ip::tcp::acceptor acceptor(io, local_endpoint);
    boost::asio::ip::tcp::socket sock(io);

    std::array<char, 128> buf;
    auto d = buf.data();
    acceptor.accept(sock);
    sock.async_read_some(
            boost::asio::buffer(buf, 128),
            [&](const boost::system::error_code &ec, std::size_t bytes)
            {
                if(ec)
                {
                    std::cout << "We encountered error: \"" << ec.message() << "\"" << std::endl;
                    return;
                }
                std::string msg(buf.data(), buf.data() + bytes);
                std::cout << "We got the message \"" << msg << "\"" << std::endl;
            }
    );
    io.run();
}
