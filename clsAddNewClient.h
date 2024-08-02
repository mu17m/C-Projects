#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"

#pragma once
class clsAddNewClient : protected clsScreen
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

	static void ShowAddNewClient()
	{
		if (!CheckAccessRights(clsUser::pAddNewClient))
		{
			return;
		}
		_DrawScreenHeader("\tAdd New Screen");
		cout << "\nPlease enter client account number: ";
		string AccountNumber = clsInputValidate::ReadString();
		while (clsBankClient::IsClientExist(AccountNumber))
		{
			cout << "Account Number is already exist, please enter another one: ";
			AccountNumber = clsInputValidate::ReadString();
		}
		clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
		_ReadClientInfo(NewClient);
		clsBankClient::enSaveResult SaveResult;
		SaveResult = NewClient.Save();
		switch (SaveResult)
		{
		case clsBankClient::svFailEmptyObject:
			cout << "\nAccount didnt added because the object is empty";
			break;

		case clsBankClient::svSucceded:
			cout << "\nClient added successfully :-)";
			_PrintAddedClient(NewClient);
			break;

		case clsBankClient::svFailAccountNumberExist:
			cout << "\nError account number is already exist";
			break;
		}
	}

};

