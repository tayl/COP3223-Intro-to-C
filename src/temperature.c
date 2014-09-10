/* Taylor Veith
 * date
 *
 * description
 */

 /*

 1) Write a program that does temperature conversion from either Fahrenheit
 to Celsius, or the other way around. Your program should first prompt the
 user for which type of conversion they want to do. Then your program should
 prompt the user for the temperature they want to convert. Finally, your
 program should output the proper converted temperature. Incidentally, the
  formula for conversion from Celsius to Fahrenheit is:

F = 1.8*C + 32
 */

//included libraries
#include <stdio.h>
#include <math.h>

//main function
int main() {
    int type;
    float fahrenheit;
    float celsius;

    printf("Celsius to Fahrenheit (0) or Fahrenheit to Celsius (1)?: ");
    scanf("%i", &type);
    if(type == 0) {
        printf("What is your Celsius value?: ");
        scanf("%f", &celsius);
        fahrenheit = (1.8 * celsius) + 32;
        printf("Your temperature in Fahrenheit is %.3f", fahrenheit);
    } else if(type == 1) {
        printf("What is your Fahrenheit value?: ");
        scanf("%f", &fahrenheit);
        celsius = (fahrenheit - 32) / 1.8;
        printf("Your temperature in Celsius is %.3f", celsius);
    } else {
        printf("Invalid option. Choose 0 or 1 for the given options.");
        return 0;
    }
    return 0;
}
