//
// Created by Athulya Ben and Ying Chen Chu
//
#include <stdio.h>
#include <iostream.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#include <sync.h>

using namespace std;

double Vx,Vy,Vz,X,Y,Z=0;
double   Ax = -2.0;
double   Ay = 4.0;
double   Az = 10.5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond=PTHREAD_COND_INITIALIZER;

class Timer
{
private:
    int channelID; //channel ID
    int conn_channel; //connection to channel
    timer_t timerID;
    clock_t timer_1 = 2000; //timer for 2 secs
    clock_t timer_2 = 6000; //timer for 6 secs
public:
    Timer(int s,int ns); //default constructor
    ~Timer(); //destructor
    void setTimer(long s, long ns); //setting the timer for default times (2 and 6)
    void wait(); //to sleep, waiting to start the next timer
};
Timer::Timer(int s,int ns)
{
    channelID = ChannelCreate(0);
    conn_channel = ConnectAttach(0,0, conn_channel,0,0);
    SIGEV_PULSE_INIT(&event, conn_channel, SIGEV_PULSE_PRIO_INHERIT, 1, 0);
    cout << "TIMER initiated" << endl;
    //create timer
    if (timer_create(CLOCK_REALTIME, &event, &timerID) == -1)
        cout << "ERROR"<< endl;
    settimer(s,ns); //set the timer
}
Timer::~Timer()
{
    cout << "Destructor called" << endl;
}
void Timer::setTimer(long s, long ns)
{
    itime.it_value.tv_sec = s;
    itime.it_value.tv_nsec = ns;
    itime.it_interval.tv_sec = s;
    itime.it_interval.tv_nsec = ns;
    timer_settime(timerID, 0, &itime, NULL);    //0 for relative time
}
void Timer::wait(){  // Wait for timer tick
    int received;
    received = MsgReceive(chid, &msgbuf, sizeof(msgbuf), NULL);
}
class ThreadClass
{
    int holdPriority;
public:
    ThreadClass(int hp);
    ~ThreadClass();
    Thread (void *(*function)(void *a),pthread_t *mythread);
};
ThreadClass::ThreadClass(int hp)
{
    holdPriority = hp;
}
ThreadClass::~ThreadClass()
{
    cout << "Destructor called" << endl;
}
long ThreadClass::Thread(void *(*)(void *)function, pthread_t *mythread)
{
    pthread_create(mythread , NULL, function, NULL);
}
//PRODUCER
void *DataAquAndProcessing(void *threadid)
{
    long tid;
    tid = (long)threadid;

    //timer counting
    Timer timer(2,1000); //for 2 secs

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
//CONSUMER
void *DataDisplay(void *threadid) {
    long tid;
    tid = (long)threadid;

    //timer counting
    Timer timer1(6, 1000); //for 6 secs
    //need to add some loop here...
    pthread_mutex_lock( &mutex );

    //**************** Displaying Data **********************
    cout<<"Display of data:" << endl;
    //add display for the time ie 6sec, 12 sec..
    cout<<"Vx =  " << Vx << "  Vy = " << Vy << "  Vz = " << Vz << endl;
    cout<<"X =  " << X << "  Y = " << Y << "  Z = " << Z << endl;

    pthread_mutex_unlock( &mutex );

}
int main(void)
{
    pthread_t P1,P2,P3; //3 threads
    //creating a periodic timer
    Timer t(1,0);
    while(true) //run till manually exit
    {
        pthread_mutex_lock(&mutex);
        //release the lock at t=0
        if(cnt == 0)
        {
            priority[3] = 0.5;
            pthread_create(&P3 , NULL, P3, NULL);
        }
        //release the lock at t = 2
        else if(cnt == 2)
        {
            priority[2] = 0.6;
            pthread_create(&P2, NULL, P2, NULL);
        }
        //release the lock at t = 5
        else if(cnt == 5)
        {
            priority[3] = 0.7;
            pthread_create(&P1 , NULL, P1, NULL);
        }
        // stop the program at t = 30
        else if(cnt == 30)
        {
            break;
        }
    }
    pthread_mutex_unlock(&mutex);
    //wait
    t.wait();
    pthread_t producer;
    pthread_t consumer;

    Thread MyProducer(DataAquAndProcessing,&producer);
    pthread_join(producer, NULL);

    Thread MyConsumer(DataDisplay,&consumer);
    pthread_join(consumer, NULL);

    cnt++;
    cout<<endl<<"pulse = "<< cnt <<endl;

    ThreadManager(); //Run active thread
}