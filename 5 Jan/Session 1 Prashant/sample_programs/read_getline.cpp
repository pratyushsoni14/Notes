#include <fstream>
#include <iostream>
#include <string>

int main ()
{
  std::ifstream myfile("sample.txt");

  if (myfile.is_open())
  {
    std::string myline;
    while (myfile.good())
    {
      std::getline (myfile, myline);
      std::cout << myline << std::endl;
    }
  }
  return 0;
}

