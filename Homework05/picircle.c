/*
//Calcular pi obteniendo pixeles dentro del circulo

int npoints =  10000;
int circle_count = 0;

void* calculatePi(void *arg){

	for(i=1; i<npoints;i++){
	//generate random numbers in coord x and y
	//if  (x,y) inside circle circle_count + 1
	}
}
pi =  (4.0)(circle_count) / npoints
*/


#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include <time.h>
#include <math.h>

#define SIZE_ARRAY 10000
#define NUM_THREADS 2

pthread_t tid[NUM_THREADS];
int ret1,ret2 = 0;

int a[SIZE_ARRAY];
int x[SIZE_ARRAY];
int y[SIZE_ARRAY];
int size = sizeof(a)/sizeof(a[0]);

void* generatePoints(void *threadid)
{
	long tid = (long)threadid;
//	print("It's me thread #%ld!\n", tid);
	int count;
	 for (count = 0 ; count < size/NUM_THREADS; count ++){
            //(x - center_x)^2 + (y - center_y)^2 < radius^2
            if (pow((x[count] - 50),2) + pow((y[count] - 50),2) < pow(50,2)){
                printf("From thread %d : %d,%d is inside \n",count, x[count],y[count]);
                //ret1++;
            }
        }
	pthread_exit(&count);



/*    pthread_t id = pthread_self();

    if(pthread_equal(id,tid[0])) {
        for (int count = 0 ; count < size/2; count ++){
            //(x - center_x)^2 + (y - center_y)^2 < radius^2
            if (pow((x[count] - 50),2) + pow((y[count] - 50),2) < pow(50,2)){
                printf("From thread 1 %d,%d is inside \n",x[count],y[count]);
                ret1++;
            }
        }
        pthread_exit(&ret1);
    }
    else {

        for (int count_2 = size/2 ; count_2 < size; count_2 ++){
            //(x - center_x)^2 + (y - center_y)^2 < radius^2
            if (pow((x[count_2] - 50),2) + pow((y[count_2] - 50),2) < pow(50,2)){
                printf("From thread 2 %d,%d is inside \n",x[count_2],y[count_2]);
                ret2++;
            }
        }
        pthread_exit(&ret2);
    }*/

}

int main(void)
{
    long  i = 0;
    int err;
    int *ptr[NUM_THREADS];

    time_t t;

    /* Intializes random number generator */
    srand((unsigned) time(&t));

    for ( long i = 0 ; i < SIZE_ARRAY ; i++){
        x[i] = rand() %100;
        y[i] = rand() %100;
        printf("Data : %d,%d \n", x[i],y[i]);

    }


    while(i < NUM_THREADS)
    {
        err = pthread_create(&(tid[i]), NULL, &generatePoints, (void *)i);
        if (err != 0)
            printf("\ncan't create thread :[%s]", strerror(err));
        else
            printf("\n Thread created successfully\n");

        i++;
    }

    pthread_join(tid[0], (void**)&(ptr[0]));
    pthread_join(tid[1], (void**)&(ptr[1]));

    printf("\n return value from first thread is [%d]\n", *ptr[0]);
    printf("\n return value from second thread is [%d]\n", *ptr[1]);

    //PI = 4.0*circle_count/npoints

    printf("Formula = PI = 4.0*circle_count/npoints\n");
    int circule_count;
    for(int i=0;i<NUM_THREADS;i++){
	circule_count += *ptr[i];
    }
    //int circule_count = *ptr[0]+*ptr[1];
    int npoints = size;


    printf("circule_count = %d \n",circule_count);
    printf("npoints  = %d \n",size);

    double PI = 4.0*(circule_count)/size;
    printf("Pi = %lf",PI);

    return 0;
}
