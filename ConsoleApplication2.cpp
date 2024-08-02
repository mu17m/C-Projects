
#include <iostream>
#include <iomanip>
#include "clsUtil.h"
#include "clsDate.h"
#include "clsString.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidation.h"
#include "clsMainScreen.h"
#include "clsLoginScreen.h"
using namespace std;

void TotalBalances()
{
	vector<clsBankClient> vClients = clsBankClient::GetClientList();

	cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;

	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	float Totalbalances = clsBankClient::GetTotalBalances();
	if (vClients.size() == 0)
		cout << "\t\t\t\tNo Clients Available In the System!";
	else

		for (clsBankClient Client : vClients)
		{
			//PrintClientRecordLine(Client);
			cout << endl;
		}

	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "\t\t\t\t\t   Total Balances = " << Totalbalances << endl;
	cout << "\t\t\t\t\t   ( " << clsUtil::NumberToText(Totalbalances) << ")";
}

int main()
{
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
}

