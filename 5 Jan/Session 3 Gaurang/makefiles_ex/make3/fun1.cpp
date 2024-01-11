#include "fun1.h"

#include <iostream>

using namespace std;

Fun1::Fun1()
{
  cout << "Fun1 constructor" << endl;
}

Fun1::~Fun1()
{
  cout << "Fun1 destructor" << endl;
}

void Fun1::funTime()
{
  cout << "Fun1:: It's fun time" << endl;
}
