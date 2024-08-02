#include <iostream>
#include "clsInputValidation.h"
#include "clsBankClient.h"
#pragma once
using namespace std;

class clsDeleteClient : protected clsScreen
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
	static void ShowDeleteCLient()
	{
		if (!CheckAccessRights(clsUser::pDeleteClient))
		{
			return;
		}
		_DrawScreenHeader("\tDelte Client Screen");
		cout << "\nPlease enter account number: ";
		string AccountNumber = clsInputValidate::ReadString();
		while (!clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "\nClient not exist, try again: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient Client = clsBankClient::Find(AccountNumber);
		_PrintAddedClient(Client);
		cout << "\nAre you sure you want to delete this client? ";
		char answer = 'y';
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			if (Client.Delete())
			{
				cout << "\nClient Deleted successfully";
				_PrintAddedClient(Client);
			}
			else
			{
				cout << "\nError Client was not deleted";
			}
		}
	}


};

