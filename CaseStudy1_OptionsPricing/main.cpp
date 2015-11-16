// Created by Yucheng Shi ys2734

#include "functions.h"

using namespace std;

int main()
{
	char anotherRun = 'Y';
	while (anotherRun != 'N')
	{
		double userUpperBound;
		int userPriceStep, userTimeStep;
		cout << "Please specify the upper bound of stock price:" << endl;
		cin >> userUpperBound;
		cout << "Please specify the step of price:" << endl;
		cin >> userPriceStep;
		cout << "Please specify the step of time:" << endl;
		cin >> userTimeStep;

		calculateOptionPrice(userUpperBound, userPriceStep, userTimeStep);

		cout << "Calculate another one? (Y/N):";
		cin >> anotherRun;
	}
	
	return 0;
}

