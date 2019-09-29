#include <iostream>
#include <cstdio>

using namespace std;

void assumptions_warning(){
    printf(" -- Based on Theorem 2.7 from Concepts and Practices of Mathematical Finance -- \n");
    printf("This calculator assumes the following:\n");
    printf("1) Stocks are non-dividend-paying\n");
    printf("2) Interest rates are non-negative\n");
}

// Check if input is valid
bool input(double &call_price, double &strike_price, double &spot_price){

    printf("\n\nEnter three numbers, separated by spaces:\n");
    printf("{call_price} {strike_price} {spot_price}\n");
    printf("\nEnter three zeroes to exit\n");
    scanf(" %lf %lf %lf", &call_price, &strike_price, &spot_price);

    return (call_price || strike_price || spot_price);
}


void calculate_action(double call_price, double strike_price, double spot_price){
    /* According to Theorem 2.7
        spot_price > call_price > spot_price - strike_price
    */

    // Check upper bound
    if (spot_price <= call_price){
        printf("Arbitrage!\n");

        printf("\n-- Today --\n");
        printf("Sell the call option for $%.3f today.\n", call_price);
        printf("Buy the stock at a cost of $%.3f today.\n", spot_price);
        printf("Invest the remaining $%.3f at the risk free rate today.\n", call_price - spot_price);

        printf("\n-- On Maturity -- \n");
        printf("If the option is exercised - give the stock up, you have your risk free rate savings of $%.3f.\n", call_price - spot_price);
        printf("If the option is not exercised - you can now sell the stock in addition to your risk free rate savings!\n");


    // Check lower bound
    } else if (call_price <= spot_price - strike_price){

        printf("Arbitrage!\n");

        printf("\n-- Today --\n");
        printf("Short the stock for $%.3f today.\n", spot_price);
        printf("Buy the call option for $%.3f today.\n", call_price);
        printf("Invest the remaining $%.3f at the risk free rate today.\n", spot_price - call_price);

        printf("\n-- On Maturity -- \n");
        printf("Close the stock short position for the minimum of the strike price and the at-maturity spot price\n");
        printf("If the at-maturity spot price is higher than the strike price then exercise the option using the money invested at the risk free rate\n");
        printf("You have no chance of losing money and a non-zero chance of making money on the difference between the strike and at-maturity spot price\n");
        printf("You will make at least $%.3f\n", spot_price - strike_price - call_price);

    // No arbitrage :(
    } else {
        printf("No arbitrage :( \n");
    }

}


int main()
{
    assumptions_warning();

    double call_price, strike_price, spot_price;
    while (input(call_price, strike_price, spot_price)){
        calculate_action(call_price, strike_price, spot_price);
    }
}
