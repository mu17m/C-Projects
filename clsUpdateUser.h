#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUser.h"
class clsUpdateUser : protected clsScreen
{
private:
	static int _ReadPermissions()
	{
		int permission = 0;
		char answer = 'n';

		cout << "\nAll Permissions? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			return -1;
		}

		cout << "\nShow Client list? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pListClient;
		}

		cout << "\nAdd New Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pAddNewClient;
		}

		cout << "\nDelete Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pDeleteClient;
		}

		cout << "\nUpdate Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pUpdateClient;
		}

		cout << "\nFind Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pFindClient;
		}

		cout << "\nTransaction Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pTransaction;
		}

		cout << "\nManage Client? y/n? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			permission += clsUser::enPermissions::pManageUsers;
		}
		return permission;
	}
	static void _ReadUser(clsUser& User)
	{
		cout << "\nEnter FirstName: ";
		User.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter LastName: ";
		User.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		User.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone: ";
		User.Phone = clsInputValidate::ReadString();
		cout << "\nEnter Password: ";
		User.Password = clsInputValidate::ReadString();
		cout << "\nEnter Permissions: ";
		User.Permssion = _ReadPermissions();
	}
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

	static void ShowUpdateUserScreen()
	{
		_DrawScreenHeader("\tUpdate Screen");
		cout << "\nPlease Enter UserName: ";
		string UserName;
		cin >> UserName;
		while (!clsUser::IsUserExist(UserName))
		{
			cout << "\nUser Not found, try again";
			cin >> UserName;
		}
		clsUser User = clsUser::Find(UserName);
		_PrintUser(User);
		cout << "\nEnter update data: \n";
		_ReadUser(User);
		clsUser::enSaveResult svResult;
		svResult = User.Save();
		switch (svResult)
		{
		case clsUser::svFailEmptyObject:
			cout << "\nObject is empty";
			break;
		case clsUser::svSucceded:
			cout << "\nUpdated seccussfully";

			break;
		case clsUser::svFailAccountNumberExist:
			cout << "\nAccount number not exist";
			break;
		}
	}
};

