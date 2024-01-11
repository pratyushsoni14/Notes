#include <fstream>
#include <iostream>
#include <string>

int main ()
{
  std::ofstream myfile("sample.txt", std::ios_base::trunc);

  myfile << "Only this line will appear in the file.\n";
  return 0;
}

