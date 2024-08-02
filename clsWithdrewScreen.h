#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
#pragma once

using namespace std;

class clsWithdrewScreen : protected clsScreen
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

	static void ShowWithdrewScreen()
	{
		_DrawScreenHeader("\tWithdrew Screen");
		string AccountNumber;
		cout << "\nPlease enter account number? ";
		AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient is not exist, try again";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintAddedClient(Client);
		cout << "\nEnter withdrew amount? ";
		short amount;
		cin >> amount;
		while (amount > Client.AccountBalance)
		{
			cout << "\nWithdrew amount is higher than your balance, try again\n";
			cin >> amount;
		}
		cout << "\nAre you sure you want this transaction? ";
		char answer ;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			Client.Withdrew(amount);
			cout << "\nWithdrew done successfully, Your balance is "<<Client.AccountBalance;
		}
	}
};

