/* Taylor Veith
 * COP3223
 * mile.c
 * 9/22/2014
 *
 * Return the average run time and average mph for given user input (miles run, time taken)
 */

//included libraries
#include <stdio.h>
#include <stdlib.h>

//constants
#define MINUTES_IN_HOUR 60.0

//main function
int main() {
    //variable declaration, initialize those that need it
    int miles_run;
    float time = 0;

    //read in user input (miles)
    printf("How many miles did you run?: ");
    scanf("%d", &miles_run);
    //verify user input is valid against given specs
    if(miles_run < 0 || miles_run >= 50) {
        printf("Please enter a positive miles value less than 50\n");
        return 1;
    }

    //declare variables to be used in for loop
    int i;
    float temp_time;
    for(i = 0; i < miles_run; i++) {
        //read in user time
        printf("How long did it take to run mile #%d?: ", (i+1));
        scanf("%f", &temp_time);
        //confirm time given complies with specs
        if(temp_time <= 0 || temp_time >= 100.0) {
            printf("Please enter a positive time less than 100 minutes.\n");
            i--;
            continue;
        }
        //add given time to total time
        time += temp_time;
    }
    //print results
    printf("Your average time to run a mile is %.3d.\n", (time / miles_run));
    printf("That is approximately %.1d miles per hour!\n", (MINUTES_IN_HOUR / (time / miles_run)));
    return 0;
}
