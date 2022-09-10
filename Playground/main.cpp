#include <iostream>
#include <Message.hpp>

enum class GameTypes{
   Position,
};

int main() {


   net::Message<GameTypes> msg;
   msg.header.id = GameTypes::Position;

   msg << 10;

   int value = 0;
   std::cout<< value << std::endl;

   msg >> value;

   std::cout<< value << std::endl;

   return 0;
}
