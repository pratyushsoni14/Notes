#include <fstream>
#include <iostream>
#include <string>

int main ()
{
  std::ofstream myfile("sample.txt", std::ios_base::app);

  myfile << "\nThis content was appended in the File.";
  return 0;
}
