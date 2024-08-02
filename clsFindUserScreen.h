#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUser.h"
class clsFindUserScreen : protected clsScreen
{
private:
	static void _PrintUser(clsUser User)
	{
		cout << "\nUser Card:";
		cout << "\n___________________";
		cout << "\nFirstName   : " << User.FirstName;
		cout << "\nLastName    : " << User.LastName;
		cout << "\nFull Name   : " << User.FullName();
		cout << "\nEmail       : " << User.Email;
		cout << "\nPhone       : " << User.Phone;
		cout << "\nUser Name   : " << User.UserName;
		cout << "\nPassword    : " << User.Password;
		cout << "\nPermissions : " << User.Permssion;
		cout << "\n___________________\n";

	}

public:

	static void ShowFindUserScreen()
	{
		_DrawScreenHeader("\tFind User Screen");
		cout << "\nPlease enter UserName: ";
		string UserName;
		cin >> UserName;
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser not found, try again ";
			cin >> UserName;
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
	}

};

