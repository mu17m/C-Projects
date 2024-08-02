#pragma once
#include <iostream>
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrency.h"
#include "clsUpdateCurrency.h"
#include "clsCurrencyCalculator.h"

using namespace std;
class clsCurrencyMainMenue
{
private:
	static void _PrintMenue()
	{
		cout << "\n==========================================";
		cout << "\nCurrency Exchange Menue";
		cout << "\n==========================================";
		cout << "\n[1] List Currencies.";
		cout << "\n[2] Find Currency.";
		cout << "\n[3] Update Rate.";
		cout << "\n[4] Currency Calculator.";
		cout << "\n[5] Main Menue.";
		cout << "\n==========================================";
	}
	static short ReadNumber()
	{
		cout << "\nChoose What do you want to do? [1 to 5}? ";
		short num;
		cin >> num;
		while (num > 5 || num < 1)
		{
			cout << "\nInvalid Number, try again: ";
			cin >> num;
		}
		return num;
	}
	static void _GoBackToCurrencyMenue()
	{
		cout << "\nPress any key to go back to currency menue...";
		system("pause>0");
		ShowCurrencyMenue();
	}
	enum enCurrencyMenue { ListCurrency = 1, FindCurrency = 2, UpdateRate = 3, CurrencyCalculator = 4, MainMenue = 5 };

	static void _ShowListCurrenciesScreen()
	{
		clsCurrenciesListScreen::ShowCurrenciesListScreen();
	}

	static void _ShowFindCurrencyScreen()
	{
		clsFindCurrency::ShowFindCurrencyScreen();
	}

	static void _ShowUpdateRateScreen()
	{
		clsUpdateCurrency::ShowUpdateCurrencyScreen();
	}

	static void _ShowCurrencyCalculator()
	{
		clsCurrencyCalculator::ShowCurrencyCalculator();
	}

	static void _PerformCurrencyMenue(enCurrencyMenue Option)
	{
		switch (Option)
		{
		case clsCurrencyMainMenue::ListCurrency:
			system("cls");
			_ShowListCurrenciesScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyMainMenue::FindCurrency:
			system("cls");
			_ShowFindCurrencyScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyMainMenue::UpdateRate:
			system("cls");
			_ShowUpdateRateScreen();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyMainMenue::CurrencyCalculator:
			system("cls");
			_ShowCurrencyCalculator();
			_GoBackToCurrencyMenue();
			break;

		case clsCurrencyMainMenue::MainMenue:
			break;

		}
	}
public:

	static void ShowCurrencyMenue()
	{
		//Header title is here

		system("cls");
		_PrintMenue();
		_PerformCurrencyMenue((enCurrencyMenue)ReadNumber());
	}
};

