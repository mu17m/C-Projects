#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
#pragma once
class clsDeposite : protected clsScreen
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

	static void ShowDepositeScreen()
	{
		_DrawScreenHeader("\tDeposite Screen");
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
		cout << "\nPlease enter deposite amount? ";
		float amount = clsInputValidate::ReadFloatNumber();
		char answer = 'y';
		cout << "Are you sure you want this transaction? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			Client1.Deposite(amount);
			cout << "\nDeposite done successfully, Your balance is "<<Client1.AccountBalance;
		}

	}


};

