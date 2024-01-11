#include <fstream>
#include <iostream>

int main ()
{
  std::ifstream myfile("sample.txt");

  if (myfile.is_open())
  {
    char mychar;
    while (myfile.good())
    {
      mychar = myfile.get();
      std::cout << mychar;
    }
  }

  return 0;
}
