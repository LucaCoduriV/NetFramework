/*
-----------------------------------------------------------------------------------
Nom du fichier  : Message.hpp
Auteur(s)       : lucac
Date creation   : 10.09.2022
Description     : <à compléter>
Remarque(s)     : <à compléter>
Compilateur     : Mingw-w64 g++ 8.1.0
-----------------------------------------------------------------------------------

*/

#ifndef PLAYGROUND_MESSAGE_HPP
#define PLAYGROUND_MESSAGE_HPP

#include <vector>
#include <memory>

namespace net {
   template<typename T>
   struct MessageHeader {
      T id{};
      uint32_t size = 0;
   };

   template<typename T>
   struct Message {
      MessageHeader<T> header{};
      std::vector<uint8_t> body;

      size_t size() const {
         return body.size();
      };

      friend std::ostream &operator<<(std::ostream &os, const Message<T> &msg) {
         os << "ID:" << int(msg.header.id) << " Size:" << msg.header.size;
         return os;
      }

      template<class DataType>
      friend Message &operator<<(Message<T> &msg, const DataType &data) {
         // Check that the type of the data being pushed is trivially copyable
         static_assert(std::is_standard_layout<DataType>::value,
                       "Data is too complex to be pushed into vector");

         size_t index = msg.body.size();

         msg.body.resize(msg.body.size() + sizeof(DataType));

         memcpy(msg.body.data() + index, &data, sizeof(DataType));

         msg.header.size += msg.size();

         return msg;
      }

      template<class DataType>
      friend Message &operator>>(Message<T> &msg, DataType &data) {
         // Check that the type of the data being pushed is trivially copyable
         static_assert(std::is_standard_layout<DataType>::value,
                       "Data is too complex to be pushed into vector");

         size_t index = msg.body.size() - sizeof(DataType);

         memcpy(&data, msg.body.data() + index, sizeof(DataType));

         msg.body.resize(index);

         msg.header.size = msg.size();

         return msg;
      }

   };

   template<typename T>
   class Connection;

   template<typename T>
   struct OwnedMessage {
      std::shared_ptr<Connection<T>> connection = nullptr;
      Message<T> msg;


      friend std::ostream &
      operator<<(std::ostream &os, const OwnedMessage<T> &msg) {
         os << msg.msg;
         return os;
      }
   };

}

#endif //PLAYGROUND_MESSAGE_HPP
