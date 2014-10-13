/* Taylor Veith
 * COP3223
 * strength.c
 * 10/1/2014
 *
 * read in user workout data and interpret it
 */

//included libraries
#include <stdio.h>
#include <stdlib.h>

//main function
int main() {
    //variable declaration and initialization where required
    int weeks;
    int best_week;
    int best_reps_average;
    int best_sets = 0;
    char name[50];
    FILE* ifp = fopen("input.txt", "r");

    //confirm input.txt was opened successfully
    if(ifp == NULL) {
        printf("Error opening input.txt\n");
        return 1;
    }

    //read in and print to console the name supplied in input.txt
    fscanf(ifp, "%s", &name);
    printf("%s\n", name);

    //read in weeks and check against given requirements
    fscanf(ifp, "%d", &weeks);
    if(weeks < 1 || weeks >= 10) {
        printf("Weeks value in input.txt is invalid.\n");
        return 1;
    }

    //iterate over each week
    int i;
    for(i = 0; i < weeks; ++i) {
        //declare local loop variables
        int workouts;

        printf("Week %d\n", (i+1));

        //read in workout number in week i and check against given requirements
        fscanf(ifp, "%d", &workouts);
        if(workouts < 1 || workouts >= 10) {
            printf("Number of workouts in week %d is invalid.\n", (i+1));
            return 1;
        }

        //iterate over each workout in week i
        int j;
        for(j = 0; j < workouts; ++j) {
            //declare local loop variables
            int sets;
            int set_average = 0;
            int average = 0;
            int valid_reps = 0;

            printf("Workout %d: ", (j+1));

            //read in number of sets in workout j in week i and check against given requirements
            fscanf(ifp, "%d", &sets);
            if(sets < 1 || sets >= 10) {
                printf("Number of sets in week %d is invalid.\n", (i+1));
            }

            //iterate over each set in workout j in week i
            int k;
            for(k = 0; k < sets; ++k) {
                //declare local loop variables
                int reps;

                //read in number of reps in set k in workout j in week i and check against given requirements
                fscanf(ifp, "%d", &reps);
                if(reps < 1 || reps >= 50) {
                    printf("Number of repetitions in week %d is invalid.\n", (i+1));
                } else if(reps >= 10) {
                    //if reps is valid, print a star and increment valid reps
                    printf("*");
                    ++valid_reps;
                }
                if(valid_reps > best_sets) {
                    //if new best set, set flag to set average (not yet computed), set best set, and set best set week
                    set_average = 1;
                    best_sets = valid_reps;
                    best_week = i + 1;
                }
                average += reps;
            }
            //calculate average, and if flag was set, set average to best average variable
            average /= sets;
            if(set_average) {
                best_reps_average = average;
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("Your best workout was in week %d and contained %d sets of an average of %d reps.\n", best_week, best_sets, best_reps_average);
    return 0;
}
