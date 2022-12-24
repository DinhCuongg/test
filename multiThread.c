#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
int global_var;
int buff[1];//buff[0] la read//buff[1] la write
pthread_mutex_t mutex;

//mutex
void* thread_func(void* arg)
{
    while(1)
    {     
        printf("/r/n%d",global_var);
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}


//pipe
void* thread_func2(void* arg)
{
    while(1)
    {
        char temp =0;
        
        if(read(buff[0],&temp,sizeof(temp)) >= 0) 
            printf("Hi [%d]\r\n",temp);
        sleep(1);
        
    }
}
void main()
{
    pipe(buff);
    pthread_t thread1_id=0;
    pthread_t thread2_id=0;
    //pthread_create(&thread1_id,NULL,thread_func,NULL);
    pthread_create(&thread2_id,NULL,thread_func2,NULL);
    //pthread_mutex_init(&mutex,NULL);
    char c = 0;
    while (1)
    {
        //pthread_mutex_lock(&mutex);
        //global_var++;
        
        
        c++;
        write(buff[1],&c,sizeof(c));
        printf("Hello\r\n");
        sleep(2);
    }
    
    
}
