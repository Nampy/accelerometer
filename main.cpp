//
// Created by A3K on 11/17/2017.
//
#include <iostream>
#include <ctimer>
#include <cstdlib>

using namespace std;

int main(int args,char* argv[])
{
    clock_t timer_1 = clock();
    double secondsPassed;
    double secondsToDelay = atof(argv[1]);
    cout << "Time to delay: " << secondsToDelay << endl;
    bool flag = true;
    while(flag)
    {
        secondsPassed = (clock() - timer_1) / CLOCKS_PER_SEC;
        if (secondsPassed >= secondsToDelay)
        {
            cout << secondsPassed << "seconds have passed" << endl;
            flag = false;
        }
    }

    return 0;
}
