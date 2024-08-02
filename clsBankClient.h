#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "clsPerson.h"
#pragma once
using namespace std;

class clsBankClient : public clsPerson
{
private:
	enum enMode {EmptyMode = 0, UpdateMode = 1, AddNewMode = 2};
	enMode _Mode;
	string _AccountNumber;
	string _PinCode;
	float _AccountBalance;
	bool _MarkToDelete = false;

	static clsBankClient _GetEmptyClient()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static clsBankClient _ConvertLineToObject(string line)
	{
		vector<string> vString;
		vString = clsString::Split(line, "#//#");
		return clsBankClient(enMode::UpdateMode, vString[0], vString[1], vString[2], vString[3], vString[4], vString[5], stod(vString[6]));
	}

	static clsBankClient _GetEmptyClientObject()
	{
		return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
	}

	static vector<clsBankClient> _LoadClientDataFromFile()
	{
		vector<clsBankClient> _vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsBankClient Client = _ConvertLineToObject(line);
				_vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _vClients;
	}

	static string _ConvertClientObjectToLine(clsBankClient Client)
	{
		string line = "";
		line += Client.FirstName + "#//#";
		line += Client.LastName + "#//#";
		line += Client.Email + "#//#";
		line += Client.Phone + "#//#";
		line += Client.AccountNumber() + "#//#";
		line += Client.PinCode + "#//#";
		line += to_string(Client.AccountBalance) + "#//#";

		return line;
	}

	static void _SaveClientDateToFile(vector<clsBankClient> _vClients)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out);
		if (MyFile.is_open())
		{
			for (clsBankClient& C : _vClients)
			{
				if (C._MarkToDelete == false)
				{
				MyFile << _ConvertClientObjectToLine(C) << endl;
				}
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == AccountNumber())
			{
				C = *this;
				break;
			}
		}
		_SaveClientDateToFile(_vClients);
	}

	void _AddDataLineToFile(string line)
	{
		fstream MyFile;
		MyFile.open("Clients.txt", ios::out | ios::app);
		if (MyFile.is_open())
		{
			MyFile << line << endl;
			MyFile.close();
		}
	}

	void _AddNew()
	{
		string line = _ConvertClientObjectToLine(*this);
		_AddDataLineToFile(line);
	}


public:
	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
	{
		this->_Mode = Mode;
		this->_AccountNumber = AccountNumber;
		this->_PinCode = PinCode;
		this->_AccountBalance = AccountBalance;
	}
	 bool IsEmpty()
	{
		return (_Mode == enMode::EmptyMode);
	}

	string AccountNumber()
	{
		return this->_AccountNumber;
	}

	void SetPinCode(string PinCode)
	{
		this->_PinCode = PinCode;
	}
	string GetPinCode()
	{
		return this->_PinCode;
	}
	__declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

	void SetAccountBalance(float AccountBalance)
	{
		this->_AccountBalance = AccountBalance;
	}
	float GetAccountBalance()
	{
		return this->_AccountBalance;
	}
	__declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;

	static clsBankClient Find(string AccountNumber)
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
		    string line;
			while (getline(MyFile, line))
			{
				clsBankClient Client = _ConvertLineToObject(line);
				if (Client.AccountNumber() == AccountNumber)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClient();
	}

	static clsBankClient Find(string AccountNumber, string PinCode)
	{
		vector<clsBankClient> vClients;
		fstream MyFile;
		MyFile.open("Clients.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsBankClient Client = _ConvertLineToObject(line);
				if (Client.AccountNumber() == AccountNumber && Client.PinCode == PinCode)
				{
					MyFile.close();
					return Client;
				}
				vClients.push_back(Client);
			}
			MyFile.close();
		}
		return _GetEmptyClient();
	}

	static bool IsClientExist(string AccountNumber)
	{
		clsBankClient Client1 = clsBankClient::Find(AccountNumber);
		return (! Client1.IsEmpty());
	}

	enum enSaveResult {svFailEmptyObject = 0, svSucceded = 1, svFailAccountNumberExist = 2};
	enSaveResult Save()
	{
		switch (_Mode)
		{
		case clsBankClient::EmptyMode:
			return enSaveResult::svFailEmptyObject;
			break;

		case clsBankClient::UpdateMode:
			_Update();
			return enSaveResult::svSucceded;
			break;
		
		case clsBankClient::AddNewMode:
			if (clsBankClient::IsClientExist(_AccountNumber))
			{
				return enSaveResult::svFailAccountNumberExist;
			}
			else 
			{
			    _AddNew();
				_Mode = enMode::UpdateMode;
				return enSaveResult::svSucceded;

			}
			break;
		}
	}

	static clsBankClient GetAddNewClientObject(string AccountNumber)
	{
		return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
	}

	bool Delete()
	{
		vector<clsBankClient> _vClients;
		_vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : _vClients)
		{
			if (C.AccountNumber() == _AccountNumber)
			{
				C._MarkToDelete = true;
				break;
			}

		}
		_SaveClientDateToFile(_vClients);
		*this = _GetEmptyClient();
		return true;
	}

	static vector<clsBankClient> GetClientList()
	{
		return _LoadClientDataFromFile();
	}

	static float GetTotalBalances()
	{
		double TotalBalances = 0;
		vector<clsBankClient> vClients = _LoadClientDataFromFile();
		for (clsBankClient& C : vClients)
		{
			TotalBalances += C.AccountBalance;
		}
		return TotalBalances;
	}

	void Deposite(float amount)
	{
		_AccountBalance += amount;
		_Mode = enMode::UpdateMode;
		Save();
	}

	void Withdrew(float amount)
	{
		_AccountBalance -= amount;
		_Mode = enMode::UpdateMode;
		Save();
	}

	static int TotalBalances(vector<clsBankClient> vCLients)
	{
		int total = 0;
		for (short i = 0; i < vCLients.size(); i++)
		{
		total += vCLients[i].AccountBalance;
		}
		return total;
	}

	void Transfer(short amount, clsBankClient& Client2)
	{
		Withdrew(amount);
		Client2.Deposite(amount);
	}

	struct stTransferLogRecord
	{
		string DateTime;
		string Sacc;
		string Dacc;
		float amount;
		float Sbalance;
		float Dbalance;
		string UserName;

	};
};

