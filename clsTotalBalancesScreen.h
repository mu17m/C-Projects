#include <iostream>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsBankClient.h"
#pragma once

using namespace std;

class clsTotalBalancesScreen : protected clsScreen
{
private:

public:

	static void ShowTotalBalancesScreen()
	{
		vector<clsBankClient> vClients = clsBankClient::GetClientList();
		int total = clsBankClient::TotalBalances(vClients);
		cout << "TotalBalances is " << total;
	}
};

