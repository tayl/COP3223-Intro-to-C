/* Taylor Veith
 * COP3223
 * 9/9/2014
 *
 * Calorie
 */

//included libraries
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//constant values
#define WALKING 5
#define WORKOUT 10
#define DRINK 20
#define FOOD 40
#define DAYS_IN_WEEK 7

//function prototypes
int isValid(int value, int min, int max, char* error);

//main function
int main() {
    //variable declaration
    int current_weight;
    int goal_weight;
    int weight_to_goal;
    int losing_weight;
    int time_spent_walking;
    int time_spent_working_out;
    int time_spent_eating;
    int time_spent_drinking;
    int daily_calorie_change;
    int days_to_goal;

    //gather user input
    printf("What is your current weight?: ");
    scanf("%d", &current_weight);
    //validate input against given specifications
    if(!isValid(current_weight, 0, 1000, "current weight")) {
        return 1;
    }

    //gather user input
    printf("What is your weight goal?: ");
    scanf("%d", &goal_weight);
    //validate input against given specifications
    if(!isValid(goal_weight, 0, 1000, "goal weight")) {
        return 1;
    }

    //determine users weight from goal
    weight_to_goal = goal_weight - current_weight;
    //negative if losing weight
    //positive if gaining weight

    //confirm user has chosen to achieve something
    if(weight_to_goal == 0) {
        printf("Goal achieved! That was fast.");
        return 0;
    }

    //determine whether user plans to gain or lose weight
    losing_weight = weight_to_goal < 0;

    //gather user input
    printf("How many minutes do you walk per day?: ");
    scanf("%d", &time_spent_walking);
    //validate input against given specifications
    if(!isValid(time_spent_walking, 0, 720, "walking time")) {
        return 1;
    }

    //gather user input
    printf("How many minutes do you exercise per day?: ");
    scanf("%d", &time_spent_working_out);
    //validate input against given specifications
    if(!isValid(time_spent_working_out, 0, 720, "exercise time")) {
        return 1;
    }

    //gather user input
    printf("How many minutes do you drink per day?: ");
    scanf("%d", &time_spent_drinking);
    //validate input against given specifications
    if(!isValid(time_spent_drinking, 0, 720, "drinking time")) {
        return 1;
    }

    //gather user input
    printf("How many minutes do you eat per day?: ");
    scanf("%d", &time_spent_eating);
    //validate input against given specifications
    if(!isValid(time_spent_eating, 0, 720, "eating time")) {
        return 1;
    }

    //calculate daily caloric change
    //exercise burns, eating gains - arithmetize accordingly
    daily_calorie_change = 0
       - (time_spent_walking * WALKING)
       - (time_spent_working_out * WORKOUT)
       + (time_spent_eating * FOOD)
       + (time_spent_drinking * DRINK);

    //catch /0
    if(daily_calorie_change == 0) {
        printf("You're never going to gain or lose a single pound at that rate.");
        return 2;
    }

    //tell user what they burn/gain daily
    printf("\nYou %s %d calories per day.\n",
        daily_calorie_change < 0 ? "burn" : "gain",
        abs(daily_calorie_change)
    );

    //calculate days to goal
    days_to_goal = (weight_to_goal * 3500) / daily_calorie_change;

    //tell user how many more pounds they must lose/gain to achieve their goal
    printf("You have %d more %s to %s.\n",
        abs(weight_to_goal),
        weight_to_goal == 1 ? "pound" : "pounds",
        losing_weight ? "lose" : "gain"
    );

    //tell user how long it will take to reach their goal
    if(days_to_goal < 0) {
        printf("You will never reach your goal at that rate.");
    } else if(days_to_goal > DAYS_IN_WEEK) {
        printf("You will reach your goal weight in %d %s and %d %s.\n",
            days_to_goal / DAYS_IN_WEEK,
            days_to_goal / DAYS_IN_WEEK == 1 ? "week" : "weeks",
            days_to_goal % DAYS_IN_WEEK,
            days_to_goal % DAYS_IN_WEEK == 1 ? "day" : "days"
        );
    } else if(days_to_goal < DAYS_IN_WEEK) {
        printf("You will reach your goal weight in %d %s.\n",
            days_to_goal,
            days_to_goal == 1 ? "day" : "days"
        );
    } else {
        printf("You will reach your goal weight in 7 days.\n");
    }
    return 0;
}

//validate user input against given specs and 'throw' errors where necessary
int isValid(int value, int min, int max, char* error) {
    if(value <= min) {
        printf("Your %s needs to be more than %d\n", error, min);
        return 0;
    }
    if(value >= max) {
        printf("Your %s needs to be less than %d\n", error, max);
        return 0;
    }
    return 1;
}
