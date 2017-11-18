#include <iostream>
#include <cstdlib>
#include <pthread.h>


using namespace std;

double Vx,Vy,Vz,X,Y,Z=0;
double   Ax = -2.0;
double   Ay = 4.0;
double   Az = 10.5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//Thread Class
class ThreadClass
{
    int hold_priority;
public:
    Thread (void *(*function)(void *a),pthread_t *mythread)
    {
        //no clue what there priorities are..not neeeded..?
        //sched_setscheduler(0, SCHED_RR, &param);  //setting priority
        pthread_create(mythread , NULL, function, NULL);
        //param.sched_priority = hold_priority; //restore priority
    }

};

//Insert Timer class here

//producer
void *DataAquAndProcessing(void *threadid) {
    long tid;
    tid = (long)threadid;

    //need add timer counting


    pthread_mutex_lock( &mutex );
    for (int i = 1; i <= 10000; i++) { //simulate extra time by for loop to 10000
        Vx = Vx + Ax * T;
        Vy = Vy + Ay * T;
        Vz = Vz + (Az - g) * T;

        X = X + Vx * T;
        Y = Y + Vy * T;
        Z = Z + Vz * T;
    }
    pthread_mutex_unlock( &mutex );
}

//consumer
void *DataDisplay(void *threadid) {
    long tid;
    tid = (long)threadid;

    //need add timer counting

    //need to add some loop here...
    pthread_mutex_lock( &mutex );

    //**************** Displaying Data **********************
    cout<<"Display of data:" << endl;
    //add display for the time ie 6sec, 12 sec..
    cout<<"Vx =  " << Vx << "  Vy = " << Vy << "  Vz = " << Vz << endl;
    cout<<"X =  " << X << "  Y = " << Y << "  Z = " << Z << endl;

    pthread_mutex_unlock( &mutex );

}

int main () {
    pthread_t producer;
    pthread_t consumer;

    Thread MyProducer(DataAquAndProcessing,&producer);
    pthread_join(producer, NULL);

    Thread MyConsumer(DataDisplay,&consumer);
    pthread_join(consumer, NULL);


    //pthread_exit(NULL); to exit a thread

}