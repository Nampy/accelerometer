//
// Created by A3K on 11/17/2017.
//
#include <cstdlib>
#include <iostream>
#include <pthread.h>
#include <time.h>

using namespace std;

double Vx,Vy,Vz,X,Y,Z=0;
double Ax = -2.0;
double Ay = 4.0;
double Az = 10.5;

clock_t timer_1 = 12000; //12 seconds
clock_t timer_2 = 6000; //6 seconds

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

//Timer Class
void Timer(clock_t t1, clock_t t2)
{
                while(clock()<t1)
                {
                        cout << clock() << endl;
                }
                cout << "Time's up for timer 1" << endl;
                while(clock()<t2)
                {
                        cout << clock() << endl;
                }
                cout << "Time's up for timer 2" << endl;
}


//producer
void *DataAquAndProcessing(void *threadid) {
    long tid;
    tid = (long)threadid;

    //timer counting


    pthread_mutex_lock( &mutex );
    for (int i = 1; i <= 10000; i++) { //simulate extra time by for
loop to 10000
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

    //timer counting

    //need to add some loop here...
    pthread_mutex_lock( &mutex );

    //**************** Displaying Data **********************
    cout<<"Display of data:" << endl;
    //add display for the time ie 6sec, 12 sec..
    cout<<"Vx =  " << Vx << "  Vy = " << Vy << "  Vz = " << Vz << endl;
    cout<<"X =  " << X << "  Y = " << Y << "  Z = " << Z << endl;

    pthread_mutex_unlock( &mutex );

}

int main(int argc, char *argv[]) {
        std::cout << "Welcome to the Momentics IDE" << std::endl;

        /*pthread_t producer;
    pthread_t consumer;

    Thread MyProducer(DataAquAndProcessing,&producer);
    pthread_join(producer, NULL);

    Thread MyConsumer(DataDisplay,&consumer);
    pthread_join(consumer, NULL);


    //pthread_exit(NULL); to exit a thread*/
    Timer(timer_1, timer_2); // TO TEST ONLY, REMOVE AFTER

        return EXIT_SUCCESS;
}
