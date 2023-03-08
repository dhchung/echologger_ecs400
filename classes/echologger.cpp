#include "echologger.h"

Echologger::Echologger(boost::asio::io_service & io, 
                       const std::string & port_name, 
                       const int baud_rate,
                       std::function<void(const std::string&)> callback):
                       port_(io, port_name), buffer_({0}), io_(io), callback_(callback){
    std::cout<<"Echologger Class Created"<<std::endl;

    boost::asio::serial_port_base::baud_rate baud_option(baud_rate);
    port_.set_option(baud_option);

    boost::asio::async_read(port_,
                            boost::asio::buffer(buffer_),
                            boost::asio::transfer_at_least(1),
                            boost::bind(&Echologger::handleRead,
                                        this,
                                        boost::asio::placeholders::error,
                                        boost::asio::placeholders::bytes_transferred));

}


Echologger::~Echologger() {
    port_.close();
}


void Echologger::handleRead(const boost::system::error_code & error,
                            size_t bytes_transferred) {

    if(!error) {
        std::string data(buffer_, bytes_transferred);
        boost::asio::async_read(port_,
                                boost::asio::buffer(buffer_),
                                boost::asio::transfer_at_least(1),
                                boost::bind(&Echologger::handleRead,
                                            this,
                                            boost::asio::placeholders::error,
                                            boost::asio::placeholders::bytes_transferred));

        callback_(data);

    } else {
        std::cout<<"Error reading serial data: "<<error.message().c_str()<<std::endl;
    }
    
}