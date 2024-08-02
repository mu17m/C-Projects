#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUser.h"
class clsDeleteUser : protected clsScreen
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

	static void ShowUserDeleteScreen()
	{
		string UserName;
		cout << "\nPlease enter username to delete ";
		cin >> UserName;
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUserName Not found, try again ";
			cin >> UserName;
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		cout << "\nAre you sure you want to delete this client? y/n? ";
		char answer ;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			User.Delete();
			cout << "\nClient deleted sccuccfully";
		}
	}

};

