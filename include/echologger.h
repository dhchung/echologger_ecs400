#ifndef ECHOLOGGER_H
#define ECHOLOGGER_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <functional>
#include <sstream>

class Echologger{
public:
    Echologger(boost::asio::io_service & io, 
               const std::string & port_name, 
               const int baud_rate,
               std::function<void(const std::string&)> callback);
    ~Echologger();

private:
    boost::asio::serial_port port_;
    boost::asio::io_service & io_;
    char buffer_[1000];

    std::function<void(const std::string&)> callback_;

    void handleRead(const boost::system::error_code & error,
                    size_t bytes_transferred);

};

#endif