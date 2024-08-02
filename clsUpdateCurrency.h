#pragma once
#include <iostream>
#include "clsCurrency.h"
using namespace std;

class clsUpdateCurrency
{
private:
	static void _PrintCurrency(clsCurrency Currency)
	{
		cout << "\nCurrency Card: ";
		cout << "\n\n________________________\n";
		cout << "\nCountry: " << Currency.Countery();
		cout << "\n Code: " << Currency.CurrencyCode();
		cout << "\nName: " << Currency.CurrencyName();
		cout << "\nRate(1$) =: " << Currency.Rate();
		cout << "\n\n________________________\n";

	}

public:
	static void ShowUpdateCurrencyScreen()
	{
		cout << "\nPlease enter currency code: ";
		string code;
		cin >> code;
		clsCurrency Currency = clsCurrency::FindByCode(code);
		_PrintCurrency(Currency);
		cout << "\nAre you sure you want to update the rate of this currency? y/n? ";
		char answer;
		cin >> answer;
		if (answer == 'Y', answer == 'y')
		{
			cout << "\nEnter New Rate: ";
			float NewRate;
			cin >> NewRate;
			Currency.UpdateRate(NewRate);
			cout << "\nCurrency Rate Updated Successfully\n";
			_PrintCurrency(Currency);
		}
	}

};

