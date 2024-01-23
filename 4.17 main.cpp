/*
4.17 : Single thread.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

// Assume circle center is (0,0)
float radius=1.0;
long in_circle=0;

// Thread config
int thread_num=1;

// Function to calculate whether a point is in or out of the circle.
int in_or_out(double x, double y){
    double distance = sqrtf(x*x + y*y);
    if (distance <= radius) {
        return 1; // in
    }
    return 0; // out
}

// Thread function
void* gen_random_points(void* times){
    double x,y;

    for( long i=0; i < *((long*)times) ; i++ ){
        x = (double)rand() / ((double)RAND_MAX/2) - radius;
        y = (double)rand() / ((double)RAND_MAX/2) - radius;
        in_circle += in_or_out(x,y);
    }
    pthread_exit(NULL);
}


int main() {
    srand(time(NULL));
    long num_of_poins =1000000;

    pthread_t threads[thread_num];
    void *thread_arg = &num_of_poins;

    for( int i =0 ; i < thread_num ; i++ ){
        pthread_create(&threads[i], NULL, gen_random_points, thread_arg);
    }
    for (int i = 0; i < thread_num ; i++) {
        pthread_join(threads[i], NULL);
    }

    double estimated_pi = 4 * (double)in_circle / (double)(num_of_poins*thread_num);
    printf("Estimated pi: %f\n", estimated_pi);
    return 0;
}
