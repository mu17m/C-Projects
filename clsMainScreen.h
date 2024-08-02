#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidation.h"
#include "clsClientListScreen.h"
#include "clsAddNewClient.h"
#include "clsDeleteClient.h"
#include "clsUpdate.h"
#include "clsFindClient.h"
#include "clsTransactionsScreen.h"
#include "clsManageUserMenueScreen.h"
#include "clsLoginRegister.h"
#include "Global.h"
#include"clsCurrency.h"
#include"clsCurrencyMainMenue.h"

using namespace std;

class clsMainScreen :protected clsScreen
{


private:
    enum enMainMenueOptions {
        eListClients = 1, eAddNewClient = 2, eDeleteClient = 3,
        eUpdateClient = 4, eFindClient = 5, eShowTransactionsMenue = 6,
        eManageUsers = 7, eLoginScreen = 8, eCurrency = 9 , eExit = 10
    };
    static short _ReadMainMenueOption()
    {
        cout << setw(37) << left << "" << "Choose what do you want to do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadShortNumberBetween(1, 10, "Enter Number between 1 to 10? ");
        return Choice;
    }
    static  void _GoBackToMainMenue()
    {
        cout << setw(37) << left << "" << "\n\tPress any key to go back to Main Menue...";

        system("pause>0");
        ShowMainMenue();
    }



    static void _ShowAllClientsScreen()
    {
        clsClientListScreen::ShowClientListScreen();
    }

    static void _ShowAddNewClientsScreen()
    {
        clsAddNewClient::ShowAddNewClient();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClient::ShowDeleteCLient();
    }

    static void _ShowUpdateClientScreen()
    {
        clsUpdate::ShowUpdateClient();
    }

    static void _ShowFindClientScreen()
    {
        clsFindClient::ShowFindClientScreen();
    }

    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsMenue();
    }

    static void _ShowManageUsersMenue()
    {
        clsShowManageUserScreen::ShowManageUserMenueScreen();

    }

    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterScreen();
    }

    static void _ShowLogoutScreen()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _ShowCurrencyMenueScreen()
    {
        clsCurrencyMainMenue::ShowCurrencyMenue();
    }

    static void _PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
    {
        switch (MainMenueOption)
        {
        case enMainMenueOptions::eListClients:
        {
            system("cls");
            _ShowAllClientsScreen();
            _GoBackToMainMenue();
            break;
        }
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            _ShowAddNewClientsScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eShowTransactionsMenue:
            system("cls");
            _ShowTransactionsMenue();
            break;

        case enMainMenueOptions::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            break;

        case enMainMenueOptions::eLoginScreen:
            system("cls");
            _ShowLoginRegisterScreen();
            _GoBackToMainMenue();
            break;

        case enMainMenueOptions::eCurrency:
            system("cls");
            _ShowCurrencyMenueScreen();
            break;

        case enMainMenueOptions::eExit:
            system("cls");
            _ShowLogoutScreen();
            break;
        }

    }



public:


    static void ShowMainMenue()
    {

        system("cls");
        _DrawScreenHeader("\t\tMain Screen");

        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t\t\tMain Menue\n";
        cout << setw(37) << left << "" << "===========================================\n";
        cout << setw(37) << left << "" << "\t[1] Show Client List.\n";
        cout << setw(37) << left << "" << "\t[2] Add New Client.\n";
        cout << setw(37) << left << "" << "\t[3] Delete Client.\n";
        cout << setw(37) << left << "" << "\t[4] Update Client Info.\n";
        cout << setw(37) << left << "" << "\t[5] Find Client.\n";
        cout << setw(37) << left << "" << "\t[6] Transactions.\n";
        cout << setw(37) << left << "" << "\t[7] Manage Users.\n";
        cout << setw(37) << left << "" << "\t[8] Login Screen.\n";
        cout << setw(37) << left << "" << "\t[9] Currency.\n";
        cout << setw(37) << left << "" << "\t[10] Logout.\n";
        cout << setw(37) << left << "" << "===========================================\n";

        _PerfromMainMenueOption((enMainMenueOptions)_ReadMainMenueOption());
    }

};

