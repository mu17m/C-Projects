#pragma once
#include <iostream>
#include "clsCurrency.h"
//#include "clsScreen"

class clsFindCurrency
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
	static void _ShowResult(clsCurrency Currency)
	{
		if (!Currency.IsEmpty())
		{
			cout << "\nCurrency Found";
			_PrintCurrency(Currency);
		}
		else
		{
			cout << "\nCurrency NOT Found";
		}
	}
public:
	static void ShowFindCurrencyScreen()
	{
		cout << "\nFind by: [1] Code or [2] Country ? ";
		short answer;
		cin >> answer;
		while (answer > 2 || answer < 1)
		{
			cout << "\nInvalid Number, try again: ";
			cin >> answer;
		}
		if (answer == 1)
		{
			cout << "\nPlease enter Currency Code: ";
			string Code;
			cin >> Code;
			clsCurrency Currency = clsCurrency::FindByCode(Code);
			_ShowResult(Currency);
		}
		else if (answer == 2)
		{
			cout << "\nPlease enter Currency Name: ";
			string Name;
			cin >> Name;
			clsCurrency Currency = clsCurrency::FindByCountry(Name);
			_ShowResult(Currency);
		}
	}

};

