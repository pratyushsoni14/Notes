#include <iostream>

#include "fun1.h"
#include "fun2.h"
#include "fun3.h"

using namespace std;

int main()
{
  Fun1 fun1;
  Fun2 fun2;
  Fun3 fun3;

  fun1.funTime();
  fun2.funTime();
  fun3.funTime();

  cout << "main" << endl;

  return 0;
}
