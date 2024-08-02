#pragma once
#include <iostream>
#include "clsCurrency.h"
using namespace std;

class clsCurrencyCalculator
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
	void _ConvertFrom1ToDollar(short amount, clsCurrency Currency)
	{
		cout << "\nConvert From: ";
		_PrintCurrency(Currency);
		cout << amount << "JOD = " << amount / Currency.Rate() << "USD\n";
	}
	static clsCurrency GetCurrency(string Messege)
	{
		cout << Messege;
		string code;
		cin >> code;
		while (!clsCurrency::IsCurrencyExist(code))
		{
			cout << "\nInvalid code, try again: ";
			cin >> code;
		}
		clsCurrency Currency = clsCurrency::FindByCode(code);
		return Currency;
	}
	static void _PrintCalculationResult(short amount, clsCurrency Currency1, clsCurrency Currency2)
	{
		_PrintCurrency(Currency1);
		float AmounInUSD = Currency1.ConvertToUSDCurrency(amount);
		cout << endl << amount << " " << Currency1.CurrencyName() << " = " << AmounInUSD << " " << "USD\n";
		if (Currency2.CurrencyCode() == "USD")
		{
			return;
		}
		cout << "\nConverting from USD to: ";
		_PrintCurrency(Currency2);
		float AmountOtherCurrency = Currency1.ConvertToOtherCurrency(amount, Currency2);
		cout << endl << amount << " " << Currency1.CurrencyName() << " = " << AmountOtherCurrency << " " << Currency2.CurrencyName();

	}
public:

	static void ShowCurrencyCalculator()
	{
		char answer = 'y';
		while (answer == 'Y' || answer == 'y')
		{
			system("cls");
			clsCurrency Currency1 = GetCurrency("Please enter code1: ");
			clsCurrency Currency2 = GetCurrency("Please enter code2: ");
			cout << "\nEnter amoount: ";
			short amount;
			cin >> amount;
			_PrintCalculationResult(amount, Currency1, Currency2);
			cout << "\n do you want to perform another calculation? y/n? ";
			cin >> answer;
		}
	}
};

