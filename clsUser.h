#include <iostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <string>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsString.h"
#pragma once

using namespace std;

class clsUser : public clsPerson
{
private:
    enum enMode { eEmptyMode = 1, eUpdateMode = 2, eAddMode = 3 };
    enMode _Mode;
    string _UserName;
    string _Password;
    int _Permssions = -1;
    float _MarkFoDeleted = false;

    static clsUser _ConvertLineToObject(string line)
    {
        vector<string> vString;
        vString = clsString::Split(line, "#//#");
        return clsUser(enMode::eUpdateMode, vString[0], vString[1], vString[2], vString[3], vString[4], vString[5], stod(vString[6]));
    }
    static vector<clsUser> _LoadUserDataFromFile()
    {
        vector<clsUser> vUsers;
        fstream MyFile;
        MyFile.open("Users.txt", ios::in);
        if (MyFile.is_open())
        {
            string line;
            while (getline(MyFile, line))
            {
                clsUser User = _ConvertLineToObject(line);
                vUsers.push_back(User);
            }
            MyFile.close();
        }
        return vUsers;
    }
    static clsUser _GetEmptyUser()
    {
        return clsUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
    }
    bool _IsEmpty()
    {
        return _Mode == enMode::eEmptyMode;
    }
    static string Encrypt(string password, short EncryptKey = 2)
    {
        for (short i = 0; i <= password.length(); i++)
        {
            password[i] = char( (int)password[i] + EncryptKey );
        }
        return password;
    }
    static string Decrypt(string password, short EncryptKey = 2)
    {
        for (short i = 0; i <= password.length(); i++)
        {
            password[i] = char((int)password[i] - EncryptKey);
        }
        return password;
    }
    static string _ConvertUserObjectToLine(clsUser User)
    {
        string line = "";
        line += User.FirstName + "#//#";
        line += User.LastName + "#//#";
        line += User.Email + "#//#";
        line += User.Phone + "#//#";
        line += User.UserName + "#//#";
        line += Encrypt(User.Password, 3) + "#//#";
        //line += User.Password + "#//#";
        line += to_string(User.Permssion);

        return line;
    }
    static void _SaveUserDateToFile(vector<clsUser> vUsers)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out);
        if (MyFile.is_open())
        {
            for (clsUser& U : vUsers)
            {
                if (U._MarkFoDeleted == false)
                {
                    MyFile << _ConvertUserObjectToLine(U) << endl;
                }
            }
            MyFile.close();
        }
    }
    void _AddDataLineToFile(string line)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << line << endl;
            MyFile.close();
        }
    }
    void _Update()
    {
        vector<clsUser> vUsers;
        vUsers = _LoadUserDataFromFile();
        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName)
            {
                U = *this;
                break;
            }
        }
        _SaveUserDateToFile(vUsers);
    }
    void _AddNew()
    {
        string line = _ConvertUserObjectToLine(*this);
        _AddDataLineToFile(line);
    }
    string _PerpartionLine(string Seprator = "#//#")
    {
        string line = "";
        line += clsDate::GetDateTime() + Seprator;
        line += UserName + Seprator;
        line += Encrypt(Password)+Seprator;
        line += to_string(Permssion);

        return line;
    }
    struct stLogin;
    static stLogin _ConvertLoginLineToRecord(string line)
    {
        stLogin Login;
        vector<string> vString = clsString::Split(line, "#//#");
        Login.DateTime = vString[0];
        Login.UserName = vString[1];
        Login.Password = Decrypt(vString[2]);
        Login.Permission = stoi(vString[3]);
        return Login;
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string UserName, string PassWord, int Permssion) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _UserName = UserName;
        _Password = PassWord;
        _Permssions = Permssion;
    }

    struct stLogin {
        string DateTime;
        string UserName;
        string Password;
        int Permission;
    };
    void SetUserName(string UserName)
    {
        _UserName = UserName;
    }
    string GetUserName()
    {
        return _UserName;
    }
    __declspec(property(get = GetUserName, put = SetUserName)) string UserName;

    void SetPassword(string Password)
    {
        _Password = Password;
    }
    string GetPassword()
    {
        return _Password;
    }
    __declspec(property(get = GetPassword, put = SetPassword)) string Password;

    void SetPermssions(int permssion)
    {
        _Permssions = permssion;
    }
    int GetPermssions()
    {
        return _Permssions;
    }
    __declspec(property(get = GetPermssions, put = SetPermssions)) int Permssion;

    static clsUser Find(string UserName)
    {
        vector<clsUser> vUsers = _LoadUserDataFromFile();
        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName)
            {
                return U;
            }
        }
        return _GetEmptyUser();
    }
    static clsUser Find(string UserName, string Password)
    {
        vector<clsUser> vUsers = _LoadUserDataFromFile();
        for (clsUser& U : vUsers)
        {
            if (U.UserName == UserName && U.Password == Password)
            {
                return U;
            }
        }
        return _GetEmptyUser();
    }
    static bool IsUserExist(string UserName)
    {
        clsUser User = clsUser::Find(UserName);
        return (!User._IsEmpty());
    }
    enum enSaveResult { svFailEmptyObject = 0, svSucceded = 1, svFailAccountNumberExist = 2 };
    enSaveResult Save()
    {
        switch (_Mode)
        {
        case clsUser::eEmptyMode:
            return enSaveResult::svFailEmptyObject;
            break;

        case clsUser::eUpdateMode:
            _Update();
            return enSaveResult::svSucceded;
            break;

        case clsUser::eAddMode:
            if (clsUser::IsUserExist(_UserName))
            {
                return enSaveResult::svFailAccountNumberExist;
            }
            else
            {
                _AddNew();
                _Mode = enMode::eUpdateMode;
                return enSaveResult::svSucceded;

            }
            break;
        }
    }
    void Delete()
    {
        vector<clsUser> vUsers = _LoadUserDataFromFile();
        for (clsUser& U : vUsers)
        {
            if (_UserName == U.UserName)
            {
                U._MarkFoDeleted = true;
                break;
            }
        }
        _SaveUserDateToFile(vUsers);
        *this = _GetEmptyUser();
    }
    static clsUser GetAddNewUser()
    {
        return clsUser(enMode::eAddMode, "", "", "", "", "", "", 0);
    }
    static vector<clsUser> GetUsersList()
    {

        vector<clsUser> vUsers = _LoadUserDataFromFile();
        return vUsers;
    }
    enum enPermissions {eAll = -1, pListClient = 1, pAddNewClient = 2, pDeleteClient = 4, pUpdateClient = 8, pFindClient = 16, pTransaction = 32, pManageUsers = 64, pLoginRegister = 128};
    bool IsUserEmpty()
    {
        return _Mode == enMode::eEmptyMode;
    }
    bool CheckAccessPermssion(enPermissions Permission)
    {
        if (Permission == enPermissions::eAll)
        {
            return true;
        }

        if ((Permission & _Permssions) == Permission)
        {
            return true;
        }
        else {
            return false;
        }
    }
    void RegisterLogin()
    {
        string line = _PerpartionLine();
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << line << endl;
            MyFile.close();
        }
    }
    static vector<stLogin> GetLoginRefisterList()
    {
        vector<stLogin> vLogins;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in);
        if (MyFile.is_open())
        {
            string line;
            stLogin Login;
            while (getline(MyFile, line))
            {
                Login = _ConvertLoginLineToRecord(line);
                vLogins.push_back(Login);
            }
            MyFile.close();
        }
        return vLogins;
    }
};