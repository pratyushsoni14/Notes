#include "fun3.h"

#include <iostream>

using namespace std;

Fun3::Fun3()
{
  cout << "Fun3 constructor" << endl;
}

Fun3::~Fun3()
{
  cout << "Fun3 destructor" << endl;
  cout << "Fun3 2destructor" << endl;
}

void Fun3::funTime()
{
  cout << "Fun3:: It's fun time" << endl;
}
