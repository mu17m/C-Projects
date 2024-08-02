#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUser.h"
#include "clsMainScreen.h"
#include "Global.h"
class clsLoginScreen : protected clsScreen
{
private:

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\tLogin Screen");
		bool LoginFail = false;
		short CountLonginFaild = 0;
		string UserName, Password;
		do
		{
			if (LoginFail)
			{
				CountLonginFaild++;
				cout << "\nInvalid UserName/Password";
				cout << "\nYou have " << 3 - CountLonginFaild << " trial(s) fail for register\n";
			}
			if (CountLonginFaild == 3)
			{
				cout << "\nYou are locked from registering\n";
				return false;
			}
			cout << "\nEnter UserName: ";
			cin >> UserName;
			cout << "\nEnter Password: ";
			cin >> Password;
			CurrentUser = clsUser::Find(UserName, Password);
			LoginFail = CurrentUser.IsUserEmpty();
		} while (LoginFail);
		CurrentUser.RegisterLogin();
		clsMainScreen::ShowMainMenue();
		return true;
	}

};

