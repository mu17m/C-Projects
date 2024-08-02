#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

#pragma once
class clsUpdate : protected clsScreen
{
private:
	static void _ReadClientInfo(clsBankClient& Client)
	{
		cout << "Enter FirstName: ";
		Client.FirstName = clsInputValidate::ReadString();
		cout << "\nEnter LastName: ";
		Client.LastName = clsInputValidate::ReadString();
		cout << "\nEnter Email: ";
		Client.Email = clsInputValidate::ReadString();
		cout << "\nEnter Phone: ";
		Client.Phone = clsInputValidate::ReadString();
		cout << "\nEnter PinCode: ";
		Client.PinCode = clsInputValidate::ReadString();
		cout << "\nEnter AccountBalance: ";
		Client.AccountBalance = clsInputValidate::ReadFloatNumber();
	}
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
	static void ShowUpdateClient()
	{
		if (!CheckAccessRights(clsUser::pUpdateClient))
		{
			return;
		}
		_DrawScreenHeader("\tUpdate Client Screen");

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

		cout << "\n\nUpdate Client Info:\n";
		_ReadClientInfo(Client1);

		clsBankClient::enSaveResult SaveResult;
		SaveResult = Client1.Save();
		switch (SaveResult)
		{
		case clsBankClient::svFailEmptyObject:
			cout << "\nError Account Not saved because its Empty";
			break;
		case clsBankClient::svSucceded:
			cout << "\nAccount Saved successfully :-)";
			_PrintAddedClient(Client1);
			break;
		}
	}
};

