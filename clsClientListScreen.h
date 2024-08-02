#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsBankClient.h"
#pragma once

class clsClientListScreen : protected clsScreen
{
private:
    static void _PrintClientRecordLine(clsBankClient Client)
    {

        cout << "| " << setw(15) << left << Client.AccountNumber();
        cout << "| " << setw(20) << left << Client.FullName();
        cout << "| " << setw(12) << left << Client.Phone;
        cout << "| " << setw(20) << left << Client.Email;
        cout << "| " << setw(10) << left << Client.PinCode;
        cout << "| " << setw(12) << left << Client.AccountBalance;

    }


public:
   
    static void ShowClientListScreen()
	{
        if (!CheckAccessRights(clsUser::pListClient))
        {
            return;
        }
        _DrawScreenHeader("\t\tClient List Screen");
        vector<clsBankClient> vClients = clsBankClient::GetClientList();
        cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(20) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        if (vClients.size() == 0)
        {
            cout << "\t\t\tNo Client available in the system!";
        }
        else
        {
            for (clsBankClient& Client : vClients)
            {
                _PrintClientRecordLine(Client);
                cout << endl;
            }
            cout << "\n_______________________________________________________";
            cout << "_________________________________________\n" << endl;

        }
	}


};

