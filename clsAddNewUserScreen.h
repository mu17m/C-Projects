#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsUser.h"
class clsAddNewUserScreen : protected clsScreen
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
public:

	static void ShowAddNewUserScreen()
	{
		_DrawScreenHeader("\tAdd New User Screen");
		cout << "\nPlease Enter Username ";
		string UserName = clsInputValidate::ReadString();
		while (clsUser::IsUserExist(UserName))
		{
			cout << "\nUsername " << UserName << " Is Already exist, try again ";
			UserName = clsInputValidate::ReadString();
		}
		clsUser User = clsUser::GetAddNewUser();
		_ReadUser(User);
		User.UserName = UserName;
		clsUser::enSaveResult SvResult;
		SvResult = User.Save();

		switch (SvResult)
		{
		case clsUser::svFailEmptyObject:
			cout << "\nUser is Empty";
			break;

		case clsUser::svSucceded:
			cout << "\nUser Added Successfully";
			break;

		case clsUser::svFailAccountNumberExist:
			cout << "\nUserName is exist";
			break;
		}

	}
};

