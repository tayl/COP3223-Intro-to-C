/* Taylor Veith
 * COP3223
 * best.c
 * 10/13/2014
 *
 * Reads in user data from input.txt and formats it for humans
 */

//included libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <float.h>

//constants
#define SET_SIZE 12

//define Participant structure
struct Participant {
    int number;
    int most_sets;
    int least_sets;
    float average_sets;
    float best_time;
    float worst_time;
    float average_time;
};

//main function
int main() {
    //declare array of Participants, as well as an extra for storing winner details
    struct Participant participants[10];
    struct Participant winner;
    FILE* ifp = fopen("input.txt", "r");

    //initialize average times to their relative minimums or maximums
    winner.average_time = FLT_MAX;
    winner.average_sets = FLT_MIN;

    //iterate over each participant
    int i;
    for(i = 0; i < 10; ++i) {
        //initialize variables inside the structure
        //is there a better way to do this?
        participants[i].number = (i+1);
        participants[i].most_sets = INT_MIN;
        participants[i].least_sets = INT_MAX;
        participants[i].average_sets = 0;
        participants[i].best_time = FLT_MAX;
        participants[i].worst_time = FLT_MIN;
        participants[i].average_time = 0;

        //iterate over each time data point in the participants set
        int j;
        float temp_time;
        for(j = 0; j < SET_SIZE; ++j) {
            //read in the time to a temporary variable
            fscanf(ifp, "%f", &temp_time);
            //compare it to the stored best and worst times, and set it when necessary
            if(temp_time < participants[i].best_time) {
                participants[i].best_time = temp_time;
            }
            if(temp_time > participants[i].worst_time) {
                participants[i].worst_time = temp_time;
            }
            //accumulate the times
            participants[i].average_time += temp_time;
        }
        //calculate the average time
        participants[i].average_time /= SET_SIZE;
        //determine whether participant is winner
        if(participants[i].average_time < winner.average_time) {
            winner.average_time = participants[i].average_time;
            winner.number = participants[i].number;
        }
        //iterate over each set data point in the participants set
        int temp_sets;
        for(j = 0; j < 12; ++j) {
            fscanf(ifp, "%d", &temp_sets);
            if(temp_sets > participants[i].most_sets) {
                participants[i].most_sets = temp_sets;
            }
            if(temp_sets < participants[i].least_sets) {
                participants[i].least_sets = temp_sets;
            }
            participants[i].average_sets += temp_sets;
        }
        participants[i].average_sets /= SET_SIZE;
        if(participants[i].average_sets < winner.average_sets) {
            winner.average_sets = participants[i].average_sets;
            winner.number = participants[i].number;
        }
    }
    //print in specified format
    for(i = 0; i < 10; ++i) {
        printf("Participant #%d\n", (i+1));
        printf("Cardio Workouts:\n", (i+1));
        printf("\tBest Time: %.2f\n", participants[i].best_time);
        printf("\tWorst Time: %.2f\n", participants[i].worst_time);
        printf("\tAverage Time: %.2f\n", participants[i].average_time);
        printf("Weight Workouts:\n");
        printf("\tMost Sets: %d\n", participants[i].most_sets);
        printf("\tLeast Sets: %d\n", participants[i].least_sets);
        printf("\tAverage Sets: %.2f\n", participants[i].average_sets);
        printf("\n");
    }
    printf("The winner is Participant #%d! Congratulations!\n", winner.number);
    return 0;
}
