#include<iostream>
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsScreen.h"
#pragma once
class clsFindClient : protected clsScreen
{
private:
	static void _PrintAddedClient(clsBankClient Client)
	{
		cout << "\nClient Card: ";
		cout << "\n-----------------------";
		cout << "\nFirst Name    : " << Client.FirstName;
		cout << "\nLast Name     : " << Client.LastName;
		cout << "\nFull Name     :" << Client.FullName();
		cout << "\nEmail         : " << Client.Email;
		cout << "\nPhone         : " << Client.Phone;
		cout << "\nAcc. Number   : " << Client.AccountNumber();
		cout << "\nPassword      : " << Client.PinCode;
		cout << "\nBalance       : " << Client.AccountBalance;
		cout << "\n-----------------------";
	}

public:
	static void ShowFindClientScreen()
	{
		if (!CheckAccessRights(clsUser::pFindClient))
		{
			return;
		}
	_DrawScreenHeader("\tFind Client Screen");

	string AccountNumber;
	cout << "\nPlease enter client account number: ";
	AccountNumber = clsInputValidate::ReadString();
	while (!clsBankClient::IsClientExist(AccountNumber))
	{
		cout << "\nAccount number is not found, choose another one: ";
		AccountNumber = clsInputValidate::ReadString();
	}
	clsBankClient Client1 = clsBankClient::Find(AccountNumber);
	_PrintAddedClient(Client1);
	}
};

