#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include<windows.h>
//#include <unistd.h>


#define sleep(x) Sleep(1000 * (x))

struct dado{
int info;
pthread_mutex_t locker;

} dado1, dado2;



//sem_t mutex;

void *thread_sensor_1(void *param){

     pthread_mutex_lock(&dado1.locker);
     printf("\n thread 1");
     pthread_mutex_lock(&dado2.locker);
     printf("\n thread 1");

     pthread_mutex_unlock(&dado1.locker);
     pthread_mutex_unlock(&dado2.locker);

}

void *thread_sensor_2(void *param){


    pthread_mutex_lock(&dado2.locker);
     printf("\n thread 2");
    pthread_mutex_lock(&dado1.locker);
     printf("\n thread 2");


    pthread_mutex_unlock(&dado2.locker);
    pthread_mutex_unlock(&dado1.locker);


}



int main(){

   printf("\n 0");

    pthread_mutex_init(&dado1.locker, NULL);//Seta os Locks
    pthread_mutex_init(&dado2.locker, NULL);

   pthread_t tid_1, tid_2;//declarar variáveis e tipos para threads
   pthread_attr_t attr;
   printf("\n 1");

   //sem_init(&mutex, 0, 1);

   pthread_attr_init(&attr);


    int i=0;



   printf("\n 3");
    do {

        pthread_create(&tid_1,&attr,thread_sensor_1,NULL);//criar threads
        pthread_create(&tid_2,&attr,thread_sensor_2,NULL);
        printf("\n 4");
        i++;

        sleep(1);

	}while(i < 10);


	pthread_cancel(tid_1);//destroi threads
	pthread_cancel(tid_2);
	pthread_mutex_destroy(&dado1.locker);//destroi lockers
	pthread_mutex_destroy(&dado2.locker);
	printf("\n 5");
   //sem_destroy(&mutex);
return 0;
}
