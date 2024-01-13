#include <iostream>
#include <unistd.h>
#include <pthread.h>

using namespace std;

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t oddCond;
pthread_cond_t evenCond;

int count = 0;

void* evenThread(void* param)
{
  while(1)
  {
      pthread_mutex_lock(&mutex1);

      if (count%2 == 0)
      {
        cout << "CountE : " << count << endl;
        count++;
        //usleep(10000);

        pthread_cond_signal(&oddCond);
        pthread_cond_wait(&evenCond, &mutex1);
      }
      pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(NULL);
}

void* oddThread(void* param)
{
  while(1)
  {
      pthread_mutex_lock(&mutex1);

      if (count%2 == 1)
      {
        cout << "CountO : " << count << endl;
        count++;
        //usleep(10000);

        pthread_cond_signal(&evenCond);
        pthread_cond_wait(&oddCond, &mutex1);
      }

      pthread_mutex_unlock(&mutex1);
  }
  pthread_exit(NULL);
}

int main()
{
  pthread_t thread[2];

  pthread_mutex_init(&mutex1, NULL);
  pthread_cond_init(&oddCond, NULL);

  pthread_create( &thread[0], NULL, *evenThread, NULL);
  pthread_create( &thread[1], NULL, *oddThread, NULL);

  pthread_join (thread[0], NULL);
  pthread_join (thread[1], NULL);

  return 0;
}