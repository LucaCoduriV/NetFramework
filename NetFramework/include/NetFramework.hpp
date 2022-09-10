/*
-----------------------------------------------------------------------------------
Nom du fichier  : NetFramework.hpp
Auteur(s)       : lucac
Date creation   : 10.09.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef NETFRAMEWORK_NETFRAMEWORK_HPP
#define NETFRAMEWORK_NETFRAMEWORK_HPP

#include <string>
#include <vector>
#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

class NetFramework {
public:
   static int test() {
      asio::error_code errorCode;
      asio::io_context context;
      asio::ip::tcp::endpoint endpoint(asio::ip::make_address("127.0.0.1",
                                                              errorCode), 80);
      asio::ip::tcp::socket socket(context);

      socket.connect(endpoint, errorCode);

      if(!errorCode){
         std::cout << "connected" << std::endl;
      }else {
         std::cout << "Failed to connect to address:\n" << errorCode.message();
      }

      if(socket.is_open()){
         std::string sRequest = "GET /index.html HTTP/1.1\r\n"
                                "Host: example.com\r\n"
                                "Connection: close\r\n\r\n";

         socket.write_some(asio::buffer(sRequest.data(), sRequest.size()),
                           errorCode);

         size_t bytes = socket.available();

         if(bytes > 0){
            std::vector<char> vBuffer(bytes);
            socket.read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
                             errorCode);
            std::cout << vBuffer.data() << std::endl;
         }
      }

      return 0;
   }
};


#endif //NETFRAMEWORK_NETFRAMEWORK_HPP
