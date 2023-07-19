#include <iostream>
#include "StudentData.h"

int main()
{
  MyManager engine;
  MyParser  parser;
  DiskManager set;
  std::vector<std::string> existing_students = set.read_file();;
  for(int i{0}; i < existing_students.size(); i++)
  {
    engine.process(parser(existing_students[i]));
  }

    std::vector<char>  separators{' ', '\t'};
    std::string  userInput;
    
    bool  shouldStop{false};
    while(!shouldStop)
    {
     std::getline(std::cin, userInput); // pay attention, pure cin doesn't allow spaces or tabs in userInput
     shouldStop = engine.process( parser(userInput) );
    }
   return 0;
}
