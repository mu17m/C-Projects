#pragma once
#include "clsScreen.h"

class clsShowTransferLogScreen : protected clsScreen
{
private:
	static clsBankClient::stTransferLogRecord _ConvertLineToTransferLogRecord(string line)
	{
		vector<string> vString = clsString::Split(line, "#//#");
		clsBankClient::stTransferLogRecord TransferLogRecord;
		TransferLogRecord.DateTime = vString[0];
		TransferLogRecord.Sacc = vString[1];
		TransferLogRecord.Dacc = vString[2];
		TransferLogRecord.amount = stoi(vString[3]);
		TransferLogRecord.Sbalance = stoi(vString[4]);
		TransferLogRecord.Dbalance = stoi(vString[5]);
		TransferLogRecord.UserName = vString[6];

		return TransferLogRecord;
	}
	static vector<clsBankClient::stTransferLogRecord> _LoadTransferLogFromFile()
	{
		vector<clsBankClient::stTransferLogRecord> vRecord;
		fstream MyFile;
		MyFile.open("TransferLog.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
			clsBankClient::stTransferLogRecord TransferLogRecord = _ConvertLineToTransferLogRecord(line);
			vRecord.push_back(TransferLogRecord);
			}
			MyFile.close();
		}
		return vRecord;
	}
	static void PrintTransferLogRecordLine(clsBankClient::stTransferLogRecord TransferLogRecord)
	{

		cout << setw(8) << left << "" << "| " << setw(23) << left << TransferLogRecord.DateTime;
		cout << "| " << setw(8) << left << TransferLogRecord.Sacc;
		cout << "| " << setw(8) << left << TransferLogRecord.Dacc;
		cout << "| " << setw(8) << left << TransferLogRecord.amount;
		cout << "| " << setw(10) << left << TransferLogRecord.Sbalance;
		cout << "| " << setw(10) << left << TransferLogRecord.Dbalance;
		cout << "| " << setw(8) << left << TransferLogRecord.UserName;


	}

public:
	static void _ShowTransferLogScreen()
	{


		vector <clsBankClient::stTransferLogRecord> vTransferLogRecord = _LoadTransferLogFromFile();

		string Title = "\tTransfer Log List Screen";
		string SubTitle = "\t    (" + to_string(vTransferLogRecord.size()) + ") Record(s).";

		_DrawScreenHeader(Title, SubTitle);

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		cout << setw(8) << left << "" << "| " << left << setw(23) << "Date/Time";
		cout << "| " << left << setw(8) << "s.Acct";
		cout << "| " << left << setw(8) << "d.Acct";
		cout << "| " << left << setw(8) << "Amount";
		cout << "| " << left << setw(10) << "s.Balance";
		cout << "| " << left << setw(10) << "d.Balance";
		cout << "| " << left << setw(8) << "User";

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;

		if (vTransferLogRecord.size() == 0)
			cout << "\t\t\t\tNo Transfers Available In the System!";
		else

			for (clsBankClient::stTransferLogRecord Record : vTransferLogRecord)
			{

				PrintTransferLogRecordLine(Record);
				cout << endl;
			}

		cout << setw(8) << left << "" << "\n\t_______________________________________________________";
		cout << "_________________________________________\n" << endl;
	}

};

