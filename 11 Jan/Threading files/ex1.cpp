#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;

int count = 0;
bool flag = false;

void* evenThread(void* param)
{
  while(1)
  {
    if (count%2 == 0)
    {
      //usleep(1* 1000);
      cout << "CountEven : " << count << endl;
      //usleep(10000);
    }
    else
    {
      count++;
    }
  }
  pthread_exit(NULL);
}

void* oddThread(void* param)
{
  while(1)
  {
    if (count%2 == 1)
    {
      cout << "CountOdd  : " << count << endl;
      //usleep(5000);
    }
    else
    {
      count++;
      usleep(10000);
    }
  }
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread[2];

  pthread_create( &thread[0], NULL, *evenThread, NULL);
  pthread_create( &thread[1], NULL, *oddThread, NULL);

  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);

  return 0;
}