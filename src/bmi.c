/* Taylor Veith
 * 29 August 2014
 *
 * Calculates BMI based on user provided input
 */

//included libraries
#include <stdio.h>

//main function
int main() {
    // declare variables and initialize them to flush garbage
    int user_height = 0;
    int user_weight = 0;
    float BMI = 0;

    // query user for data
    printf("Please enter your height in inches: ");
    // scan in to variable
    scanf("%i", &user_height);
    // perform required data validation
    if(user_height <= 0 || user_height >= 100) {
        printf("Please ensure your height is positive and less than 100.");
        return 0;
    }

    // query user for data
    printf("Please enter your weight in pounds: ");
    // scan in to variable
    scanf("%i", &user_weight);
    // perform required data validation
    if(user_weight <= 0 || user_weight >= 1000) {
        printf("Please ensure your weight is positive and less than 1000.");
        return 0;
    }

    // calculate BMI using user provided data
    BMI = user_weight / pow(user_height, 2) * 703;
    // print result to stdio
    printf("Your BMI is calculated at %.2f.", BMI);
    return 0;
}
