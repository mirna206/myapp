
#include <iostream>
#include <stack>
#include <queue>
#include "Card.h"
#include <fstream>

using namespace std;
/*bellow variables are:
 * totalTime: is the total time the car spend's in car_wash
 * waitTime: is the total time that the car spend to start washing
 * totalWaitTime: is the total waiting time for all cars
 * avrWaitTime: is is the avrage wait time
 * totCrWshTim: total car wash use tim
 * percentage: percentage of time car wash was in use
 */
int totalTime , waitTime, totalWaitTime;
int avrWaitTime, totCrWshTim, percentage;
auto simuEndTime = 70; // setting the Simulation End Time.
void showCard (Car_Wash card) {
    card.getArrivT ()>simuEndTime ? cout << "\t"<<"|" << card.getNum ()<< "\t\t\t"<<"|"
                                << card.getArrivT () << " minutes after opening, car arrived after closing time and was not served."
                         : cout << "\t" <<"|"<< card.getNum ()<< "\t\t\t"<<"|"
                                << card.getArrivT ()<< "\t\t\t\t\t"<<"|"
                                << card.getWashSTime () << "\t\t\t\t\t" <<"|"<< card.getDepTim () << "\t\t\t\t"<<"|"
                                << card.getWaitTime () << "\t\t\t\t"<<"|"
                                << card.getTotalTime ();

}


void showStackm (queue <Car_Wash> m) {
    while( ! m.empty ()) {
        showCard (m.front ());
        cout << "\n";
        m.pop ();
    }

}

int main() {
    /* arrivalTime is arrival time
     * counter: to count and show how many car car wash have
     * StartTime: car wash start time
     * temp = start time for previous car
     */
    int arrivalTime = 0 , temp = 0;
    int counter = 0 , startTime = 0;
    fstream inFile ("inPut.txt");
    //Step 1 is instantiate an object
    Car_Wash Car (counter , arrivalTime , startTime);

    queue<Car_Wash> m;//Constructor - using Car Wash class
    while( ! inFile.eof ()) {

        inFile >> arrivalTime;
         //counter to count the car arrived to car wash.
        counter ++;
        if (inFile.fail()){
            cout << "unable to open inPut.txt file\n";
            break;
        }
        if ( counter == 1 ) {
            startTime = arrivalTime;
            temp = startTime;
        }
        else if (( arrivalTime - ( temp + 3 )) < 0 ) {
            startTime = temp + 3;
            temp = startTime;
        }
        else {
            startTime = arrivalTime;
            temp = startTime;
            waitTime = startTime - arrivalTime;
        }



        //Step 2 is push it onto stack
        //Car_Wash Car (counter, arrivalTime, startTime);
        Car.setNum (counter);
        Car.setArrivT (arrivalTime);
        Car.setWashSTime (startTime);
        Car.setDepTim (startTime + 3);
        waitTime = Car.getWashSTime () - Car.getArrivT ();
        Car.setWaitTime (waitTime);
        totalTime = Car.getWaitTime () + 3;
        Car.setTotalTime (totalTime);
        //totalWaitTime = Car.getWaitTime ();
        if(Car.getArrivT ()<=simuEndTime) {
            totalWaitTime = totalWaitTime + Car.getWaitTime ();
            Car.setTotalWaitTime (totalWaitTime);
            avrWaitTime = Car.getTotalWaitTime () / counter;
            totCrWshTim = counter * 3;
            percentage = ( totCrWshTim * 100 ) / 60;
        }
        m.push (Car);
    }
    for(int columns=1; columns<= 1; columns++){
        cout << " Car Number " << " Arrival time: " << " Car Wash Start Time: "<< " departure time is: "
             << " wait time : "<< " Total wait Time: \n"
             <<"------------------------------------------------------------------------------------------------------\n";
    }
    showStackm (m);

    cout << "\nEnd of simulation\n"<<"\nStatistics:\n" << "\tTotal wait time:\t\t\t\t\t\t\t"
        << Car.getTotalWaitTime ()<< " min\n" << "\tAverage wait time:\t\t\t\t\t\t\t"<< avrWaitTime
        << " mins\n" "\tTotal car wash use time:\t\t\t\t\t"<<totCrWshTim<< " minutes\n"
        <<"\tPercentage of time car wash was in use:\t\t"<< percentage << "%\n";
    return 0;
}

