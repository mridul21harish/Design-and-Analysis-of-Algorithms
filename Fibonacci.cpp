#include <stdio.h>
#include <string.h>
#include <unistd.h> 
#include <sys/types.h> 
//#include <sys/wait.h>
#include <limits.h>
#include <math.h>
#include <pthread.h> 
 
#define r_end 0
#define w_end 1
 
typedef struct{
    int index;
    int lower;
    int upper;
    int *arr;
    int *val;
} minmax_args_t;
 
 
void get_fibonacci(int n, int* fib_series){
 
    if (n==0) return;
    fib_series[0] = 1;
    if (n==1) return;
    fib_series[1] = 1;
    int i =2;    
    while(i<n)
    {
        fib_series[i++] = fib_series[i-1]+fib_series[i-2];
    }
    }
 
void* minmax(void *vargs) {
    minmax_args_t *args = (minmax_args_t *)  vargs;
    int index = args->index;
    int lower = args->lower;
    int upper = args->upper;
    int *arr = args->arr;
    int *val = args->val;
 
    printf("Lower bound (inclusive) for Thread%d = %d\n", index, lower);
    printf("Upper bound (exclusive) for Thread%d = %d\n", index, upper);
 
    int min = INT_MAX, max = 0;
    for (int i = lower; i < upper; ++i) {
        min = min > arr[i] ? arr[i] : min;
        max = max > arr[i] ? max : arr[i];
    }
 
    printf("Computed by Thread%d: Max = %d, Min = %d\n", index, max, min);
    val[0] = min;
    val[1] = max;
    return NULL;
}
 
int calc_fact(int n) {
    int ans = 1;
    while (n > 0) {
        ans *= n;
        --n;
    }
    return ans;
}
 
int main(){
    int status;
    int fd1[2],fd2[2],fd3[2],fd4[2],fd5[2];
    //First pipe
    status  = pipe(fd1);
    if(status == -1){
        fprintf(stderr, "Error in creating pipe 1");
        return 1;
    }
    //First child
    pid_t c1 = fork();
    printf("%d\n", c1);
 
    if(c1>0)
    {
        //We're back to our parent 
        close(fd1[r_end]);
        //Taking n1
        int n1;
        printf("Please enter n1 : \n");
        scanf("%d", &n1);
        //Passing n1 to child
        write(fd1[w_end], &n1, 4);
        close(fd1[w_end]);
        printf("%d\n", wait(NULL));
        printf("Hola\n");
    }
 
    else if(c1 == 0){
        //Contents of child 1
        close(fd1[w_end]);
        int n1=2;
        read(fd1[r_end], &n1, 4);
        close(fd1[r_end]);
        printf("Value recieved by child 1 (n1) : %d\n", n1);
        //----------------------------------------------------------
        //After this child 1 stops executing for random reason, idk
        //-----------------------------------------------------------
        printf("yo\n");
        int fib_series[n1];
        printf("here\n");
        get_fibonacci(n1, fib_series);
 
        // Construct string of series
        char series[1000] = {0};
        char temp[100] = {0};
        int head = 0;
        printf("\n");
        for (int i = 0; i < n1; i++) {
            printf("%d ",fib_series[i]);
            sprintf(temp, "%d", fib_series[i]);
            strcat(series, temp);
        }
 
        printf("\nChild 1 says: Fibonacci series: %s\n", series);
        printf("Terminating");
        return 0; // Child 1 terminates 
    }
 
    else if(c1 < 0){
        fprintf(stderr, "Fork Failed for child 1" );
        return 1;
    }
    
 
 
    //Create 3 pipes for child 2 now
    status  = pipe(fd2);
    if(status == -1){
        fprintf(stderr, "Error in creating pipe 2");
        return 1;
    }
    status = pipe(fd3);
    if(status == -1){
        fprintf(stderr, "Error in creating pipe 3");
        return 1;
    }
    status = pipe(fd4);
    if(status == -1){
        fprintf(stderr, "Error in creating pipe 4");
        return 1;
    }
 
    //Second child
    pid_t c2 = fork();
    
    if(c2 == 0){
        //First close all pipes writing ends'
        close(fd2[w_end]);
        close(fd3[w_end]);
        close(fd4[w_end]);
 
        //giving n2,n3 and the array of n3 elements to child 2
        int n2, n3;
        read(fd2[r_end], &n2, 4);
        read(fd3[r_end], &n3, 4);
 
        int arr[n3];
        for(int i = 0; i < n3; i++){
            read(fd4[r_end], &arr[i], 4);
        }
 
        //Reading done, time to close these ends
        close(fd2[r_end]);
        close(fd3[r_end]);
        close(fd4[r_end]);
 
        //Array to string, makes printing easier
        char series[1000] = {0};
        char temp[100] = {0};
        int head = 0;
        for (int i = 0; i < n3; i++) {
            sprintf(temp, "%d ", arr[i]);
            strcat(series, temp);
        }
 
        //Printing values
        printf("Child 2, n2 = %d\n", n2);
        printf("Child 2, n3 = %d\n", n3);
        printf("Child2, array = %s \n", series);
        int no_threads = n3/n2;
        pthread_t thread[no_threads];
        minmax_args_t threads[no_threads];
        int val[no_threads][2];
 
        int lower = 0;
        for(int i = 0; i < no_threads; i++){
            threads[i].index = i+1;
            threads[i].lower = lower;
            threads[i].upper = lower+no_threads;
            threads[i].arr = arr;
            threads[i].val = val[i];
            lower+=no_threads;
 
            if(pthread_create(&thread[i], NULL, minmax, &threads[i]) != 0){
                fprintf(stderr, "Failed to create thread %d in child 2\n", i);
                return 1;
            }
        }
 
        for(int i = 0; i < no_threads; i++){
            pthread_join(thread[i], NULL);
        }
 
        int min = INT_MAX, max = 0;
        for(int i = 0; i < no_threads; i++){
            min = min > val[i][0] ? val[i][0] : min;
            max = max > val[i][0] ? max : val[i][0];
        }
        printf("Child2 shows Max = %d , Min = %d", max, min);
 
        //closing processes
        close(fd2[r_end]);
        close(fd3[r_end]);
        close(fd4[r_end]);
        
        //Close child
        return 0;
    }
    else if(c2 < 0){
        fprintf(stderr, "Failed to fork child 2");
        return 1;
    }
    //Back to parent
    close(fd2[r_end]);
    close(fd3[r_end]);
    close(fd4[r_end]);
 
    int n2, n3;
    printf("Parent asks n2 : \n");
    scanf("%d", &n2);
    printf("Parent asks n3 : \n");
    scanf("%d", &n3);
    int arr[n3];
    printf("Parent asks arr for child2 : \n");
    for(int i = 0; i < n3; i++){
        scanf("%d", &arr[i]);
    }
 
    write(fd2[w_end], &n2, 4);
    write(fd3[w_end], &n3, 4);
    for(int i = 0; i < n3; i++){
        write(fd4[w_end], &arr[i], 4);
    }
 
    //Close pipes
    close(fd2[w_end]);
    close(fd3[w_end]);
    close(fd4[w_end]);
 
    status = pipe(fd5);
    if(status == -1){
        fprintf(stderr, "Error in creating pipe 5");
        return 1;
    }
    //------------------------------------------------------------
    //Some weird error here where prog stops executing unless n2 > n3, which should not be there
    //--------------------------------------------------------------
    //printf("\n");
    pid_t c3 = fork();
    if(c3 == 0){
        close(fd5[w_end]);
 
        int n4;
        read(fd5[r_end], &n4, 4);
        close(fd5[r_end]);
 
        printf("Child 3 : n4 = %d\n", n4);
        int fac = calc_fact(n4);
        printf("Child 3 : %d! = %d\n", n4, fac);
        
        //End child
        return 0;
    }
    else if(c3 < 0){
        fprintf(stderr, "Failed to fork child3\n");
        return 1;
    }
 
    //Back to parent
    close(fd5[r_end]);
 
    int n4;
    printf("Parent asks for n4 : \n");
    scanf("%d", &n4);
    write(fd5[w_end], &n4, 4);
    close(fd5[w_end]);
 
    //Waiting for the 3 child process to complete
    wait(NULL);
    //wait(NULL);
    //wait(NULL);
    printf("Successfully executed \n");
    return 0;
}
