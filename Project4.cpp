

#include <iostream>
#include<vector>
#include <cctype>
#include <fstream>
#include <string>
#include<iomanip>
using namespace std;
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool markToDelete = false;
};
enum enATM { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eLogout = 5};
void Login();
void ATMscreen();
sClient CurrentUser;
string ConvertRecordToString(sClient Client, string seprator = "#//#") {

	string line;
	line += Client.AccountNumber + seprator;
	line += Client.PinCode + seprator;
	line += Client.Name + seprator;
	line += Client.Phone + seprator;
	line += to_string(Client.AccountBalance);
	return line;
}
vector<sClient> SaveToFile(vector<sClient> vClients) {
	fstream MyFile;
	string line;
	MyFile.open("MyFile.txt", ios::out);
	if (MyFile.is_open()) 
	{
		for (sClient& C : vClients) 
		{
				line = ConvertRecordToString(C);
				MyFile << line << endl;
			
		}
	}MyFile.close();
	return vClients;
}
vector<string> SplitString(string line, string seprator = "#//#") {
	vector <string> vClient;
	string sWord;
	short pos = 0;
	while ((pos = line.find(seprator)) != std::string::npos) {
		sWord = line.substr(0, pos);
		if (sWord != "") {
			vClient.push_back(sWord);
		}line.erase(0, pos + seprator.length());
	}if (line != "") {
		vClient.push_back(line);
	}
	return vClient;
}
sClient ConvertLineToRecord(string line) {
	vector<string> vClient;
	vClient = SplitString(line);
	sClient Client;
	Client.AccountNumber = vClient[0];
	Client.PinCode = vClient[1];
	Client.Name = vClient[2];
	Client.Phone = vClient[3];
	Client.AccountBalance = stod(vClient[4]);
	return Client;
}
vector<sClient> LoadFileData() {
	fstream MyFile;
	sClient Client;
	vector<sClient> vClients;
	MyFile.open("MyFile.txt", ios::in);
	if (MyFile.is_open()) {
		string line;
		while (getline(MyFile, line)) {
			Client = ConvertLineToRecord(line);
			vClients.push_back(Client);
			//break;
		}
	}
	return vClients;
}
bool FindClientByAccountNumer(string AccountNumber, string PinCode, sClient& Client ) {
	vector<sClient> vClients;
	vClients = LoadFileData();
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber && C.PinCode == PinCode) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool loadUserInfo(string AccountNumber, string PinCode)
{
	if (FindClientByAccountNumer(AccountNumber, PinCode, CurrentUser)) {
		return true;
	}
	else return false;

}

void GoBackToATMmenue()
{
	cout << "\nPress any key to go back to ATM menue...";
	system("pause>0");
	ATMscreen();
}
int whatDoYouWant()
{
	int num;
	cout << "\nChoose what do you want to do? [1 to 5] ";
	cin >> num;
	return num;
}
void CheckBalances() 
{
	vector<sClient> vClients;
	vClients = LoadFileData();
	int TotalBalanc = 0;
	for (sClient& C : vClients) 
	{
		if (C.AccountNumber == CurrentUser.AccountNumber)
		{
			TotalBalanc += C.AccountBalance;
		}
	}
	cout << "\t\t\t\nYour Balance is " << TotalBalanc << endl;
}
void PrintQuickWithdrawScreen()
{
	cout << "==========================================\n";
	cout << "\tQuick Withdraw";
	cout << "\n==========================================\n";
	cout << "\t[1] 20 \t[2] 50\n";
	cout << "\t[3] 100\t[4] 200\n";
	cout << "\t[5] 400\t[6] 600\n";
	cout << "\t[7] 800\t[8] 1000\n";
	cout << "\t[9] Exit\n";
	cout << "\n==========================================\n";
}
void QuickWithdraw()
{
	short num;
	char answer = 'y';
	vector<sClient> vClients;
	vClients = LoadFileData();
	PrintQuickWithdrawScreen();
	CheckBalances();
	cout << "\nChoose what to withdraw from[1] to [8] ? ";
	cin >> num;
	if (num == 9) ATMscreen();
	cout << "\nAre you sure you want to perform this transaction ? Y/N ";
	cin >> answer;
	if (answer == 'y' || answer == 'Y')
	{
		switch (num)
		{
		case 1:
			CurrentUser.AccountBalance -= 20;
			cout << "\nDone Successfully, Now Balance is "<< CurrentUser.AccountBalance;
			break;
		case 2:
			CurrentUser.AccountBalance -= 50;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 3:
			CurrentUser.AccountBalance -= 100;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 4:
			CurrentUser.AccountBalance -= 200;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 5:
			CurrentUser.AccountBalance -= 400;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 6:
			CurrentUser.AccountBalance -= 600;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 7:
			CurrentUser.AccountBalance -= 800;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		case 8:
			CurrentUser.AccountBalance -= 1000;
			cout << "\nDone Successfully, Now Balance is " << CurrentUser.AccountBalance;
			break;
		}
	}
	for (sClient& C : vClients) {
		if (C.AccountNumber == CurrentUser.AccountNumber) {
			C.AccountBalance = CurrentUser.AccountBalance;
		}
	}
	SaveToFile(vClients);

}
void Withdraw() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	vector<sClient> vClients;
	vClients = LoadFileData();
	int Amount = 0;
	do{
		cout << "\nEnter an Amount with multiple of 5s ? ";
		cin >> Amount;
	} while (Amount % 5 != 0);

	while (Amount > CurrentUser.AccountBalance) {
		cout << "\nAmount Exeeds the  balance, you can withdraw up tp : " << CurrentUser.AccountBalance << endl;
		cout << "Please Enter anthor amount? ";
		cin >> Amount;
	}
	cout << "\nAre you sure you want this transaction ? Y/N? ";
	char sure;
	cin >> sure;
	if (sure == 'y' || sure == 'Y') 
	{
		CurrentUser.AccountBalance -= Amount;
		for (sClient& C : vClients) {
			if (C.AccountNumber == CurrentUser.AccountNumber) {
				C.AccountBalance = CurrentUser.AccountBalance;
			}
		}
		SaveToFile(vClients);
		cout << "\nDone successfully, New Account Balance is: " << CurrentUser.AccountBalance;
	}

}
void Deposit() 
{
	int Amount = 0;
	vector<sClient> vClients;
	vClients = LoadFileData();
	cout << "\nPlease Enter deposit amount? ";
	cin >> Amount;
	cout << "\nAre you sure you want this transaction ? Y/N? ";
	char sure;
	cin >> sure;
	if (sure == 'y' || sure == 'Y') 
	{
		
		CurrentUser.AccountBalance += Amount;
		for (sClient& C : vClients) {
			if (C.AccountNumber == CurrentUser.AccountNumber) {
				C.AccountBalance = CurrentUser.AccountBalance;
			}
		}
		SaveToFile(vClients);
		cout << "\nDone successfully, New Account Balance is: " << CurrentUser.AccountBalance;
	}

}

void performATM(enATM Optins) {
	switch (Optins)
	{
	case eQuickWithdraw:
		system("cls");
		QuickWithdraw();
		GoBackToATMmenue();
		break;
	case eNormalWithdraw:
		system("cls");
		Withdraw();
		GoBackToATMmenue();
		break;
	case eDeposit:
		system("cls");
		Deposit();
		GoBackToATMmenue();
		break;
	case eCheckBalance:
		system("cls");
		CheckBalances();
		GoBackToATMmenue();
		break;
	case eLogout:
		Login();
		break;
	}
}
void ATMscreen() {
	system("cls");
	cout << "==========================================\n";
	cout << "\tATM Main Menue Screen";
	cout << "\n==========================================\n";
	cout << "\t[1] Quick Withdraw.\n";
	cout << "\t[2] Normal Withdraw.\n";
	cout << "\t[3] Deposit.\n";
	cout << "\t[4] Check Balance.\n";
	cout << "\t[5] Logout.";
	cout << "\n==========================================\n";
	performATM((enATM)whatDoYouWant());
}
void Login() {
	bool LoginFaild = false;
	string AccountNumber, PinCode;
	do {
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-----------------------------------\n";
		if (LoginFaild) {
			cout << "Invalid UserName/Password\n";
		}
		cout << "Enter Account Number? ";
		cin >> AccountNumber;
		cout << "Enter PinCode? ";
		cin >> PinCode;
		LoginFaild = !loadUserInfo(AccountNumber, PinCode);

	} while (LoginFaild);

	ATMscreen();

}

int main()
{
	Login();
}

