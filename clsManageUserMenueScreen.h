#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsInputValidation.h"
#include "clsListUsersScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUser.h"
#include "clsUpdateUser.h"
#include "clsFindUserScreen.h"

#pragma once

using namespace std;

class clsShowManageUserScreen : public clsScreen
{
private:
	enum enManageMenueOption {eListUsers = 1, eAddNew = 2, eDeleteUser = 3, eUpdateUser = 4, eFindUser = 5, eMainMenue =6};
	static void _GoBackToMenue()
	 {
		 cout << "\nPress any key to go back...";
		 system("pause>0");
		 ShowManageUserMenueScreen();
	 }

	static void _ShowListUsersScreen()
	{
		clsListUsersScreen::ShowUsersList();
	}

	static void _ShowAddNewUserScreen()
	{
		clsAddNewUserScreen::ShowAddNewUserScreen();
	}

	static void _ShowDeleteUsersScreen()
	{
		clsDeleteUser::ShowUserDeleteScreen();
	}

	static void _ShowUpdateUserScreen()
	{
		clsUpdateUser::ShowUpdateUserScreen();
	}

	static void _ShowFindUsersScreen()
	{
		clsFindUserScreen::ShowFindUserScreen();
	}
	static void _PerformManageMenueOption(enManageMenueOption opation)
	{
		switch (opation)
		{
		case clsShowManageUserScreen::eListUsers:
			system("cls");
			_ShowListUsersScreen();
			_GoBackToMenue();
			break;
		case clsShowManageUserScreen::eAddNew:
			system("cls");
			_ShowAddNewUserScreen();
			_GoBackToMenue();
			break;
		case clsShowManageUserScreen::eDeleteUser:
			system("cls");
			_ShowDeleteUsersScreen();
			_GoBackToMenue();
			break;
		case clsShowManageUserScreen::eUpdateUser:
			system("cls");
			_ShowUpdateUserScreen();
			_GoBackToMenue();
			break;
		case clsShowManageUserScreen::eFindUser:
			system("cls");
			_ShowFindUsersScreen();
			_GoBackToMenue();
			break;
		case clsShowManageUserScreen::eMainMenue:
			break;
		}
	}
	static short ReadNum()
	{
		cout << "\nChoose what do you do? [1-6] ";
		return clsInputValidate::ReadIntNumberBetween(1, 6);
	}

public:
	static void ShowManageUserMenueScreen()
	{
		system("cls");
		if (!CheckAccessRights(clsUser::pManageUsers))
		{
			return;
		}
		_DrawScreenHeader("\t\tManage User Screen");

		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t\t\tManage User Menue\n";
		cout << setw(37) << left << "" << "===========================================\n";
		cout << setw(37) << left << "" << "\t[1] List User.\n";
		cout << setw(37) << left << "" << "\t[2] Add New User.\n";
		cout << setw(37) << left << "" << "\t[3] Delete User.\n";
		cout << setw(37) << left << "" << "\t[4] Update User Info.\n";
		cout << setw(37) << left << "" << "\t[5] Find User.\n";
		cout << setw(37) << left << "" << "\t[6] Main Menue.\n";
		cout << setw(37) << left << "" << "===========================================\n";

		_PerformManageMenueOption((enManageMenueOption)ReadNum());
	}

};

