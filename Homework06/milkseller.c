#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<stdlib.h>

//pthread_t tid[2];
int counter;
int sellers = 10;
int milks = 200;
pthread_t tid[10];
pthread_mutex_t lock;

void* doSomeThing(void *arg)
{
        srand(time(NULL));
        int r = rand() % 50;
    pthread_mutex_lock(&lock);
    unsigned long i = 0;

    counter += 1;
   // printf("\n Seller %d sold %d milks \n", counter,r);
        if(milks>0){
                if(r<=milks){
                        for(i=0; i<r;i++){
                                milks--;
                        }
                        printf("\n Seller %d sold %d milks \n", counter,r);

                }
                else{
                        printf("\n Seller %d sold %d milks \n", counter,milks);
                        milks = 0;
                }
//              printf("\n Job %d finished\n", counter);
                printf("Milks left: %d\n", milks);
        }
        else{
                printf("\n Seller %d sold %d milks \n", counter,milks);
                printf("Sorry, no milks left\n");
        }

    //printf("\n Job %d finished\n", counter);
   // printf("Milks: %d", milks);
        pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int err;

    if (pthread_mutex_init(&lock, NULL) != 0){
        printf("\n mutex init failed\n");
            return 1;
    }

    while(i < sellers/*here*/) {
        err = pthread_create(&(tid[i]), NULL, &doSomeThing, NULL);
            if (err != 0)
                printf("\ncan't create thread :[%s]", strerror(err));
                i++;
    }
for(i = 0; i < sellers;i++){
    pthread_join(tid[i], NULL);
}
    //pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
