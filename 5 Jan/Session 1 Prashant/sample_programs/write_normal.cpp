#include <fstream>
#include <iostream>
#include <string>

int main ()
{
  // By default, it will be opened in normal write mode, ios::out.
  std::ofstream myfile("sample.txt");

  myfile << "Hello Everyone \n";
  myfile << "This content was being written from a C++ Program";
  return 0;
}
