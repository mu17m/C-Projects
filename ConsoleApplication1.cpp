
#include <iostream>
#include<vector>
#include <cctype>
#include <fstream>
#include <string>
#include<iomanip >
using namespace std;
struct sClient {
	string AccountNumber;
	string PinCode;
	string Name;
	string Phone;
	double AccountBalance = 0;
	bool markToDelete = false;
};
struct sUser {
	string UserName;
	string Password;
	int Permssions = 0;
	bool MarkToDelete = false;
};
enum enMainMenueOptions { eListClients = 1, eAddNewClient = 2, eDeleteClient = 3, eUpdateClient = 4, eFindClient = 5, eTransaction = 6, eManageUsers = 7, eLogout = 8 };
enum enTransactionOptions { eDeposit = 1, eWithdraw = 2, eTotalBalances = 3, eMainMenue = 4 };
enum enManageUsers { eListUsers =1, eAddNewUser =2, eDeleteUser =3, eUpdateUser =4, eFindUser =5, eBackMenue =6};
enum enPermessions {eAll =-1, pShowList =1, pAddNewUser =2, pDeleteUser =4, pUpdateUser =8, pFindUser =16, pTransAction =32, pManageUsers =64};
sUser CurrentUser;
string UserFileName = "Users.txt";
sClient Record() {

	sClient Client;
	cout << "\nEnter Account Number ? ";
	getline(cin >> ws, Client.AccountNumber);
	cout << "Enter PinCode ? ";
	getline(cin, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}
sClient Record(string AccountNumber) {

	sClient Client;
	Client.AccountNumber = AccountNumber;
	cout << "Enter PinCode ? ";
	getline(cin >> ws, Client.PinCode);
	cout << "Enter Name ? ";
	getline(cin, Client.Name);
	cout << "Enter Phone ? ";
	getline(cin, Client.Phone);
	cout << "Enter Account Balance ? ";
	cin >> Client.AccountBalance;
	return Client;
}
string ConvertRecordToString(sClient Client, string seprator = "#//#") {

	string line;
	line += Client.AccountNumber + seprator;
	line += Client.PinCode + seprator;
	line += Client.Name + seprator;
	line += Client.Phone + seprator;
	line += to_string(Client.AccountBalance);
	return line;
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
void ConvertLineToFile(string line) {
	fstream MyFile;
	MyFile.open("MyFile.txt", ios::out | ios::app);
	if (MyFile.is_open()) {
		MyFile << line << endl;
	}MyFile.close();
}
void PrintClientCard(sClient Client) {
	cout << "\nThe following are the client details:\n";
	cout << "\nAccout Number: " << Client.AccountNumber;
	cout << "\nPin Code     : " << Client.PinCode;
	cout << "\nName         : " << Client.Name;
	cout << "\nPhone        : " << Client.Phone;
	cout << "\nAccount Balance: " << Client.AccountBalance;
	cout << endl;
}

void PrintClientRecord(sClient Client) {
	cout << "| " << setw(15) << left << Client.AccountNumber;
	cout << "| " << setw(10) << left << Client.PinCode;
	cout << "| " << setw(40) << left << Client.Name;
	cout << "| " << setw(12) << left << Client.Phone;
	cout << "| " << setw(12) << left << Client.AccountBalance;
}
void PrintAllClientsData(vector <sClient> vClients) {
	cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	cout << "| " << left << setw(15) << "Accout Number";
	cout << "| " << left << setw(10) << "Pin Code";
	cout << "| " << left << setw(40) << "Client Name";
	cout << "| " << left << setw(12) << "Phone";
	cout << "| " << left << setw(12) << "Balance";
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
	for (sClient Client : vClients)
	{
		PrintClientRecord(Client);
		cout << endl;
	}
	cout << "\n_______________________________________________________";
	cout << "_________________________________________\n" << endl;
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
		}
	}
	return vClients;
}
string ReadAccountNumber() {
	string AccountNumber;
	cout << "Plase Enter Account Number ? ";
	cin >> AccountNumber;
	return AccountNumber;
}
bool FindClientByAccountNumer(string AccountNumber, sClient& Client) {
	vector<sClient> vClients;
	vClients = LoadFileData();
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool FindClientByAccountNumer(string AccountNumber, sClient& Client, vector<sClient> vClients) {
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccountNumber) {
			Client = C;
			return true;
		}
	}
	return false;
}
bool MarkClient(string AccoubntNumber, vector<sClient>& vClients) {
	for (sClient& C : vClients) {
		if (C.AccountNumber == AccoubntNumber) {
			C.markToDelete = true;
			return true;
		}
	}
	return false;
}
vector<sClient> saveToFileWithDelete(vector<sClient> vClients) {
	fstream MyFile;
	string line;
	MyFile.open("MyFile.txt", ios::out);
	if (MyFile.is_open()) {
		for (sClient& C : vClients) {
			if (C.markToDelete == false) {
				line = ConvertRecordToString(C);
				MyFile << line << endl;
			}
		}
	}MyFile.close();
	return vClients;
}

void ShowAccessDeniedMessage() 
{ 
	cout << "\n------------------------------------\n";     
	cout << "Access Denied, \nYou dont Have Permission To Do this,\nPlease Conact Your Admin.";     
	cout << "\n------------------------------------\n"; 
}
bool CheckAccessPermission(enPermessions Permssion)
{
	if (CurrentUser.Permssions == enPermessions::eAll)
	{
		return true;
	};
	if ((Permssion & CurrentUser.Permssions) == Permssion)
	{
		return true;
	}
	else return false;
}
void GoBackToMainMenue();

void ShowAllClients() {
	if (!CheckAccessPermission(enPermessions::pShowList))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	vector<sClient> vClient;
	vClient = LoadFileData();
	PrintAllClientsData(vClient);

}
void AddClient() {
	if (!CheckAccessPermission(enPermessions::pAddNewUser))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	char answer = 'y';
	do {
		system("cls");
		cout << "Adding New Client:\n";
		sClient Client;
		Client = Record();
		string line;
		line = ConvertRecordToString(Client);
		ConvertLineToFile(line);
		cout << "\nClient Added Successfully, do you want to add more ? Y/N ?";
		cin >> answer;
	} while (answer == 'y' || answer == 'Y');

}
void DeleteClient() {
	if (!CheckAccessPermission(enPermessions::pDeleteUser))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	vector<sClient> vClients;
	vClients = LoadFileData();
	sClient Client;
	char answer = 'y';
	if (FindClientByAccountNumer(AccountNumber, Client, vClients)) {
		PrintClientCard(Client);
		cout << "\n\nAre you Sure you want to delete this CLient ? Y/N ?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			MarkClient(AccountNumber, vClients);
			saveToFileWithDelete(vClients);

			vClients = LoadFileData();
			cout << "\nClient Deleted successfully\n";
		}
	}
}
void UpdateMaui() {
	if (!CheckAccessPermission(enPermessions::pUpdateUser))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	vector<sClient> vClients;
	vClients = LoadFileData();
	sClient Client;
	if (FindClientByAccountNumer(AccountNumber, Client, vClients)) {
		PrintClientCard(Client);
		char answer = 'y';
		cout << "\nAre you sure you want to Update this client ? Y/N? ";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C = Record(AccountNumber);
					break;
				}
			}

		}
		saveToFileWithDelete(vClients);
		cout << "\nClient Updated Successfully\n";

	}
}
void FindClient() {
	if (!CheckAccessPermission(enPermessions::pFindUser))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	sClient Client;
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	if (FindClientByAccountNumer(AccountNumber, Client)) {
		PrintClientCard(Client);
	}
	else {
		cout << "\nClient NOT Found\n";
	}
}

void Deposit() {
	cout << "\n-----------------------------------\n";
	cout << "\tDeposit Screen";
	cout << "\n-----------------------------------\n";
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	vector<sClient> vClients;
	vClients = LoadFileData();
	sClient Client;
	 while(!FindClientByAccountNumer(AccountNumber, Client, vClients)) {
		 cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
		 AccountNumber = ReadAccountNumber();
	}
		PrintClientCard(Client);
		double Amount = 0;
		cout<<"\nPlease Enter deposit amount? ";
		cin >> Amount;
		cout << "\nAre you sure you want this transaction ? Y/N? ";
		char sure;
		cin >> sure;
		if (sure == 'y' || sure == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C.AccountBalance += Amount;
					saveToFileWithDelete(vClients);
					cout << "\nDone successfully, New Account Balance is: "<<C.AccountBalance;
				}
			}
		}

	
}
short choose() {
	short num = 0;
	cout << "Choose what do you want to do ? [1-8] ? \n";
	cin >> num;
	return num;
}
short whatDoYouWant() {
	short Num = 0;
	cout << "Choose What Do you want to do ? [1-4] ? ";
	cin >> Num;
	return Num;
}
void GoBackToTransactionMenue();
void TotalBalances() {
	vector<sClient> vClients;
	vClients = LoadFileData();
	int TotalBalanc=0;
	for (sClient& C : vClients) {
		TotalBalanc += C.AccountBalance;
	}
	cout << "\t\t\t\nTotal Balances = " << TotalBalanc<<endl;
}
void MainMenue();


//Extention 2
sUser ConvertLineOfUsersToRecord(string line) {
	sUser User;
	vector<string> vUser;

	vUser = SplitString(line);

	User.UserName = vUser[0];
	User.Password = vUser[1];
	User.Permssions = stoi(vUser[2]);

	return User;
}
vector<sUser> LoadUserFileData() {
	vector<sUser> vUsers;

	fstream MyFile;
	MyFile.open(UserFileName, ios::in);

	if (MyFile.is_open())
	{
		string line;
		sUser User;
		while (getline(MyFile, line))
		{
			User = ConvertLineOfUsersToRecord(line);
			vUsers.push_back(User);
		}
	}
	return vUsers;
}
bool FindUserByUserNameAndPassword(string UserName, string Password, sUser& User)
{
	vector <sUser> vUser = LoadUserFileData();

	for (sUser& U : vUser)
	{
		if (U.UserName == UserName && U.Password == Password) {
			User = U;
			return true;
		}
	}
	return false;
}
bool loadUserInfo(string UserName, string Password)
{
	if (FindUserByUserNameAndPassword(UserName, Password, CurrentUser)) {
		return true;
	}
	else return false;

}
void Login() {
	bool LoginFaild = false;
	string UserName, Password;
	do {
		system("cls");
		cout << "\n-----------------------------------\n";
		cout << "\tLogin Screen";
		cout << "\n-----------------------------------\n";
		if (LoginFaild) {
			cout << "Invalid UserName/Password\n";
		}
		cout << "Enter UserName? ";
		cin >> UserName;
		cout << "Enter Password? ";
		cin >> Password;
		LoginFaild = !loadUserInfo(UserName, Password);

	} while (LoginFaild);

	MainMenue();
}
int chooseFromManageMenue() {
	int num;
	cout << "Choose what do you want to do? [1 to 8]? ";
	cin >> num;
	return num;
}
void PrintUserRecordLine(sUser User) 
{ 
	cout << "| " << setw(15) << left << User.UserName;     
	cout << "| " << setw(10) << left << User.Password;     
	cout << "| " << setw(40) << left << User.Permssions; 
} 
bool UserExsistByUserName(string UserName) {
	fstream MyFile;
	MyFile.open(UserFileName, ios::in);
	if (MyFile.is_open())
	{
		sUser User;
		string line;
		while (getline(MyFile, line))
		{
			User = ConvertLineOfUsersToRecord(line);
			if (User.UserName == UserName) {
				MyFile.close();
				return true;
			}
		}
	}
	MyFile.close();
	return false;
}
int ReadPermssion() {
	int Permssion = 0;
	char access;
	cout << "Do you want to give full access? Y/N ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		return -1;
	}
	cout << "Do you want to give access\n";
	cout << "\nShow Client List? Y/N ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pShowList;
	}
	cout << "\nAdd new client? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pAddNewUser;
	}
	cout << "\nDelete client? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pDeleteUser;
	}
	cout << "\nUpdate client? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pUpdateUser;
	}
	cout << "\nFind client? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pFindUser;
	}
	cout << "\nTransaction client? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y') {
		Permssion += enPermessions::pTransAction;
	}
	cout << "\nManage clients? y/n ";
	cin >> access;
	if (access == 'y' || access == 'Y')
	{
		Permssion += enPermessions::pManageUsers;
	}
	return Permssion;
}
string ConvertUserRecordToLine(sUser User) {
	string s1 ="";
	s1 += User.UserName + "#//#";
	s1 += User.Password + "#//#";
	s1 += to_string(User.Permssions);

	return s1;
}
void AddUserToFile(string s1) {
	fstream MyFile;
	MyFile.open(UserFileName, ios::out | ios::app);

	if(MyFile.is_open())
	{
		MyFile << s1 << endl;
	    MyFile.close();
	}
}
sUser ReadUser()
{
	sUser User;
	cout << "Enter UserName? ";
	getline(cin >> ws, User.UserName);
	while (UserExsistByUserName(User.UserName)) 
	{
		cout << "\nUserName with [" << User.UserName << "] Already Exsist, Enter another UserName\n";
		getline(cin >> ws, User.UserName);
	}
	cout << "\nEnter Password? ";
	getline(cin, User.Password);

	User.Permssions = ReadPermssion();
	return User;
}
void ManageUsers();
void GoBackmanageMenue() {
	cout << "\nPress any key to go back to manage menue";
	system("pause>0");
	system("cls");
	ManageUsers();
}
bool FindUserByUserName(string UserName, sUser& User)
{
	vector <sUser> vUser = LoadUserFileData();

	for (sUser& U : vUser)
	{
		if (U.UserName == UserName) {
			User = U;
			return true;
		}
	}
	return false;
}
bool MarkUser(string UserName, vector<sUser>& vUsers) {
	for (sUser& U : vUsers) {
		if (U.UserName == UserName) {
			U.MarkToDelete = true;
			return true;
		}
	}
	return false;
}
vector<sUser> saveUserToFileWithDelete(vector<sUser> vUsers) {
	fstream MyFile;
	string line;
	MyFile.open(UserFileName, ios::out);
	if (MyFile.is_open()) {
		for (sUser& U : vUsers) {
			if (U.MarkToDelete == false) {
				line = ConvertUserRecordToLine(U);
				MyFile << line << endl;
			}
		}
	}MyFile.close();
	return vUsers;
}

void ShowAllUsersScreen() 
{ 
	vector <sUser> vUsers = LoadUserFileData();     
	cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";     
	cout << "\n_______________________________________________________";     
	cout << "_________________________________________\n" << endl;     
	cout << "| " << left << setw(15) << "User Name";     
	cout << "| " << left << setw(10) << "Password";     
	cout << "| " << left << setw(40) << "Permissions";     
	cout << "\n_______________________________________________________";     
	cout << "_________________________________________\n" << endl; 
	if (vUsers.size() == 0)         
		cout << "\t\t\t\tNo Users Available In the System!"; 
	
	else for(sUser User : vUsers) 
	{ 
		PrintUserRecordLine(User);             
		cout << endl; 
	}     
	cout << "\n_______________________________________________________";     
	cout << "_________________________________________\n" << endl; 
}
void AddNewUser()
{
	sUser User;
	User = ReadUser();
	AddUserToFile(ConvertUserRecordToLine(User));
}
void DeleteUser() 
{
	cout << "\n-----------------------------------\n";
	cout << "\tDelete User Screen";
	cout << "\n-----------------------------------\n";
	sUser User;
	cout << "Enter UserName? ";
	getline(cin >> ws, User.UserName);
	while (!UserExsistByUserName(User.UserName))
	{
		cout << "\nUserName with [" << User.UserName << "] Is NOT Exsist, Enter another UserName\n";
		getline(cin >> ws, User.UserName);
	}
	vector<sUser> vUsers;
	vUsers = LoadUserFileData();
	char answer = 'y';
	if (FindUserByUserName(User.UserName, User)) {
		PrintUserRecordLine(User);
		cout << "\n\nAre you Sure you want to delete this user ? Y/N ?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') {
			MarkUser(User.UserName, vUsers);
			saveUserToFileWithDelete(vUsers);

			vUsers = LoadUserFileData();
			cout << "\nUser Deleted successfully\n";
		}
	}
}
void UpdateUser() 
{
	cout << "\n-----------------------------------\n";
	cout << "\tUpdate User Screen";
	cout << "\n-----------------------------------\n";
	sUser User;
	cout << "Enter UserName? ";
	getline(cin >> ws, User.UserName);
	while (!UserExsistByUserName(User.UserName))
	{
		cout << "\nUserName With [" << User.UserName << "] Is NOT Exsist, Enter Another UserName\n";
		getline(cin >> ws, User.UserName);
	}
	vector<sUser> vUsers;
	vUsers = LoadUserFileData();
	char answer = 'y';
	if (FindUserByUserName(User.UserName, User)) 
	{
		PrintUserRecordLine(User);
		cout << "\n\nAre you Sure You Want To Update This User ? Y/N ?";
		cin >> answer;
		if (answer == 'y' || answer == 'Y') 
		{
			for (sUser& U : vUsers) 
			{
				if (U.UserName == User.UserName) 
				{
			        cout << "\nEnter Password? ";
					cin >> U.Password;
					U.Permssions = ReadPermssion();
					break;
				}
			}
		}
	}
	saveUserToFileWithDelete(vUsers);
	cout << "\nClient Updated Successfully\n";
}
void FindUser()
{
	cout << "\n-----------------------------------\n";
	cout << "\tFind User Screen";
	cout << "\n-----------------------------------\n";
	sUser User;
	cout << "Enter UserName? ";
	getline(cin >> ws, User.UserName);
	if (UserExsistByUserName(User.UserName))
	{
		vector<sUser> vUsers;
		vUsers = LoadUserFileData();
		for (sUser& U : vUsers) 
		{
			if (U.UserName == User.UserName)
			{
		    PrintUserRecordLine(U);
			}
		}
	}
}
void PerformManageMenue(enManageUsers Option) {
	switch (Option)
	{
	case eListUsers:
		system("cls");
		ShowAllUsersScreen();
		GoBackmanageMenue();
		break;
	case eAddNewUser:
		system("cls");
		AddNewUser();
		GoBackmanageMenue();
		break;
	case eDeleteUser:
		system("cls");
		DeleteUser();
		GoBackmanageMenue();
		break;
	case eUpdateUser:
		system("cls");
		UpdateUser();
		GoBackmanageMenue();
		break;
	case eFindUser:
		system("cls");
		FindUser();
		GoBackmanageMenue();
		break;
	case eBackMenue:
		MainMenue();
		break;
	}
}
void ManageUsers() {
	if (!CheckAccessPermission(enPermessions::pManageUsers))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	cout << "\n-----------------------------------\n";
	cout << "\tManage Users Menue Screen";
	cout << "\n-----------------------------------\n";
	cout << "\t [1] List Users.\n";
	cout << "\t [2] Add New User.\n";
	cout << "\t [3] Delete User.\n";
	cout << "\t [4] Update User.\n";
	cout << "\t {5] Find User.\n";
	cout << "\t [6] Main Menue.\n";
	cout << "\n-----------------------------------\n";
	PerformManageMenue(enManageUsers(chooseFromManageMenue()));

}

//Extention 1
void Withdraw() {
	cout << "\n-----------------------------------\n";
	cout << "\tWithdraw Screen";
	cout << "\n-----------------------------------\n";
	string AccountNumber;
	AccountNumber = ReadAccountNumber();
	vector<sClient> vClients;
	vClients = LoadFileData();
	sClient Client;
	while(!FindClientByAccountNumer(AccountNumber, Client, vClients)) {
		cout << "Client with [" << AccountNumber << "] does not exist.\n";
		AccountNumber = ReadAccountNumber();
	}
		PrintClientCard(Client);
		double Amount = 0;
		cout<<"\nPlease Enter Withdraw amount? ";
		cin >> Amount;

		while (Amount > Client.AccountBalance) {
			cout << "\nAmount Exeeds the  balance, you can withdraw up tp : " << Client.AccountBalance << endl;
			cout << "Please Enter anthor amount? ";
			cin >> Amount;
		}
		cout << "\nAre you sure you want this transaction ? Y/N? ";
		char sure;
		cin >> sure;
		if (sure == 'y' || sure == 'Y') {
			for (sClient& C : vClients) {
				if (C.AccountNumber == AccountNumber) {
					C.AccountBalance -= Amount;
					saveToFileWithDelete(vClients);
					cout << "\nDone successfully, New Account Balance is: " << C.AccountBalance;
				}
			}
		}
		
}
void performTransactionMenue(enTransactionOptions Optins) {
	switch (Optins)
	{
	case eDeposit:
		system("cls");
		Deposit();
		GoBackToTransactionMenue();
		break;
	case eWithdraw:
		system("cls");
		Withdraw();
		GoBackToTransactionMenue();
		break;
	case eTotalBalances:
		system("cls");
		ShowAllClients();
		TotalBalances();
		GoBackToTransactionMenue();
		break;
	case eMainMenue:
		MainMenue();
		break;
	}
}
void TransactionMenueScreen() {
	if (!CheckAccessPermission(enPermessions::pTransAction))
	{
		ShowAccessDeniedMessage();
		GoBackToMainMenue();
	}
	system("cls");
	cout << "==========================================\n";
	cout << "\tTransaction Menue Screen";
	cout << "\n==========================================\n";
	cout << "\t[1] Deposit.\n";
	cout << "\t[2] Withdraw.\n";
	cout << "\t[3] TotalBalances.\n";
	cout << "\t[4] Main Menue.";
	cout << "\n==========================================\n";
	performTransactionMenue((enTransactionOptions)whatDoYouWant());
}
void GoBackToTransactionMenue() {
	cout << "\nPress any key to back to Transaction Menue...";
	system("pause>0");
	TransactionMenueScreen();
}

//Main Menue
void PerformMainMenueOption(enMainMenueOptions MenueOptions) {
	switch (MenueOptions)
	{
	case eListClients:
		system("cls");
		ShowAllClients();
		GoBackToMainMenue();
		break;
	case eAddNewClient:
		system("cls");
		AddClient();
		GoBackToMainMenue();
		break;
	case eDeleteClient:
		system("cls");
		DeleteClient();
		GoBackToMainMenue();
		break;
	case eUpdateClient:
		system("cls");
		UpdateMaui();
		GoBackToMainMenue();
		break;
	case eFindClient:
		system("cls");
		FindClient();
		GoBackToMainMenue();
		break;
	case eTransaction:
		system("cls");
		TransactionMenueScreen();
		break;
	case eManageUsers:
		system("cls");
		ManageUsers();
		break;
	case eLogout:
		system("cls");
		Login();
		break;
	}
}
void MainMenue() {
	system("cls");
	cout << "\n============================================================\n";
	cout << "\t\t\tMain Menue Screen";
	cout << "\n============================================================\n";
	cout << "\t[1] Show All Clients.\n";
	cout << "\t[2] Add New Client.\n";
	cout << "\t[3] Delete Client.\n";
	cout << "\t[4] Update Client Info.\n";
	cout << "\t[5] Find Client.\n";
	cout << "\t[6] Transaction.\n";
	cout << "\t[7] Manage Users.\n";
	cout << "\t[8] Logout.";
	cout << "\n============================================================\n";
	PerformMainMenueOption((enMainMenueOptions)choose());
}
void GoBackToMainMenue() {
	cout << "\nPress any key to back to the menue...";
	system("pause>0");
	MainMenue();
}

int main()
{
	Login();
}