#pragma once
#include <iostream>
#include "clsScreen.h"
#include "Global.h"
class clsTransfer : protected clsScreen
{
private:
	static void _PrintClientCard(clsBankClient Client)
	{
		cout << "\nClient Card";
		cout << "\n_________________";
		cout << "\n\nFull Name: " << Client.FullName();
		cout << "\nAcc. Number: " << Client.AccountNumber();
		cout << "\nBalance: " << Client.AccountBalance;
		cout << "\n_________________";
	}
	static void _TransferLogToFile(clsBankClient C1, clsBankClient C2, short amount)
	{
		fstream MyFile;
		string seprator = "#//#";
		MyFile.open("TransferLog.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << clsDate::GetDateTime() + seprator + C1.AccountNumber() + seprator + C2.AccountNumber()+ seprator + to_string(amount) + seprator + to_string(C1.AccountBalance) + seprator + to_string(C2.AccountBalance) + seprator + CurrentUser.UserName;
			MyFile.close();
		}
	}
public:

	static void ShowTransferScreen()
	{
		_DrawScreenHeader("\tTransfer Screen");
		cout << "\nPlease enter account number to transfer from: ";
		string AccountNumber1, AccountNumber2;
		cin >> AccountNumber1;
		while (!clsBankClient::IsClientExist(AccountNumber1))
		{
			cout << "\nWrong account number, try again: ";
			cin >> AccountNumber1;
		}
		clsBankClient ClientSource = clsBankClient::Find(AccountNumber1);
		_PrintClientCard(ClientSource);
		cout << "\n\nPlease enter account number to transfer from: ";
		cin >> AccountNumber2;
		while (!clsBankClient::IsClientExist(AccountNumber2))
		{
			cout << "\nWrong account number, try again: ";
			cin >> AccountNumber2;
		}
		clsBankClient ClientDestnation = clsBankClient::Find(AccountNumber2);
		_PrintClientCard(ClientDestnation);

		short amount;
		cout << "\nEnter transfer amount? ";
		cin >> amount;
		while (ClientSource.AccountBalance < amount)
		{
			cout << "\namount excceds the balance, enter less amount: ";
			cin >> amount;
		}
		cout << "\nAre you sure you want this transaction? y/n? ";
		char answer;
		cin >> answer;
		if (answer == 'y' || answer == 'Y')
		{
			ClientSource.Transfer(amount, ClientDestnation);
			cout << "\nTransfer done successfully";
			_TransferLogToFile(ClientSource, ClientDestnation, amount);
			_PrintClientCard(ClientSource);
			cout << endl;
			_PrintClientCard(ClientDestnation);

		}

	}
};

