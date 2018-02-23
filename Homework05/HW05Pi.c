//Link to graph:
// https://github.com/RichiePalma/Operating-Systems/blob/master/Homework05/PiRunTimeGraph.pdf

//Note: Graph file may be empty if HW was checked before 11:59 of 2/22/2018 but it will be
       //submited before such hour
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <stdint.h>
#include <math.h>
#include <time.h>

#define DEFAULT_POINTS      100000
#define NUM_THREADS  30
int     work_per_thread;
long    circle_count;
long    points;
unsigned int seed;

double randomizer(){
    return (double)rand_r(&seed) / (double)((unsigned)RAND_MAX + 1);
}

void *pointsGenerator(void *t_id){
    double x, y;
    int *count_in = (int *)malloc(sizeof(int));
    *count_in = 0;
    
    int i;
    for(i=0; i<DEFAULT_POINTS/NUM_THREADS; i++){
        x = randomizer();
        y = randomizer();
        if( sqrt(pow((x-.5),2)+ pow((y-.5),2)) <= .5){  
          *count_in += 1;
       }
    }
    pthread_exit((void *) count_in);
}

int main(void){
    seed = time(NULL);
    points = DEFAULT_POINTS; 

    double  pi;
    void    *count_inside_thread;
    int     thread_creation;

    pthread_t threads[NUM_THREADS];

    unsigned int i;
    for(i=0; i<NUM_THREADS; i++){ //Generates threads and runs pointGenerator( ) each
        thread_creation = pthread_create(&threads[i], NULL, pointsGenerator, (void *)(intptr_t) i);
        seed++;
    }

    for(i=0; i<NUM_THREADS; i++){ //Sums the value of points inside circle gotten by each thread
        pthread_join(threads[i], &count_inside_thread);
        circle_count += * (long *) count_inside_thread;
    }
    
    printf("Total points: %zd\n"
           "Points inside circle: %zd\n", points, circle_count);

    pi = (4.00 * (float)circle_count) / (float)points;

    printf("\nPi-> %.5f\n", pi);

    exit(0);
}
