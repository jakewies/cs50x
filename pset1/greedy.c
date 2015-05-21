#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // Variable declarations
    float change_owed;
    int cents_owed;
    int remaining;
    int quarters;
    int dimes;
    int nickels;
    int pennies;
    int num_coins;
    
    /* Get the user's input for the amount owed, and 
    continue to prompt the user if they enter a number less
    than 0 */
    do 
    {
        printf("How much change is owed?: ");
        change_owed = GetFloat();    
    } while (change_owed < 0);
    
    // Convert change owed into cents
    cents_owed = round(change_owed * 100);
    
    /* Count the number of coins used. If a certain
    coin isn't used, 'remaining' will stay the same */
    
    // Count quarters
    quarters = cents_owed / 25;
    remaining = cents_owed % 25;
    
    // Count dimes
    dimes = remaining / 10;
    remaining = remaining % 10;
    
    // Count nickels
    nickels = remaining / 5;
    remaining = remaining % 5;
    
    // Count pennies
    pennies = remaining;
    
    // Add the coins to gather the total
    num_coins = quarters + dimes + nickels + pennies;
    
    printf("%d\n", num_coins);
    
    
    

       
}
