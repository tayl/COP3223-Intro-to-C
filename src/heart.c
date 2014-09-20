/* Taylor Veith
 * COP3223
 * Heart Rate Monitor
 * 09/15/2014
 *
 * Monitor how often user meets their target heart rate
 */

//included libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//constants
#define MALE_RATE 226
#define FEMALE_RATE 220

//main function
int main() {
    //variable declaration
    int male;
    int age;
    int target_heart_rate;
    //and initialization for those that should be
    int current_heart_rate = 0;
    int hit_count = 0;
    int total_count = 0;
    char gender;

    //get gender
    printf("What is your gender?: ");
    scanf("%c", &gender);

    switch(gender) {
        case 'f':
        case 'F':
            male = 0;
            break;
        case 'm':
        case 'M':
            male = 1;
            break;
        default:
            printf("Please specify m for male or f for female");
            return 1;
    }

    //get age
    printf("What is your age?: ");
    scanf("%d", &age);
    //and validate
    if(age < 0 || age >= 100) {
        printf("Please enter an positive age less than 100");
        return 1;
    }

    //calculate target heart rate given sex and age
    target_heart_rate = male ? MALE_RATE - age : FEMALE_RATE - age;

    //collect heart rates
    printf("Enter your recorded heart rates:\n");
    while(current_heart_rate != -1) {
        scanf("%d", &current_heart_rate);
        //check that heart rate is less than zero
        if(current_heart_rate < 0) {
            //if it is, it might be our escape
            //confirm it isn't and throw error
            if(current_heart_rate != -1) {
                printf("Please enter a heart rate greater than 0\n");
            }
            continue;
        }
        //increment hit count if we meet or exceed our target
        if(current_heart_rate >= target_heart_rate) {
            hit_count++;
        }
        //increment total count regardless of target being met
        total_count++;
    }
    //output
    printf("You hit your target heart rate %d times out of %d!\n", hit_count, total_count);
    return 0;
}
