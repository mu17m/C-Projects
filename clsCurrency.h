#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class clsCurrency
{
private:
	enum enMode { EmptyMode = 0, UpdateMode = 1 };
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static vector<string>Split(string line)
	{
		vector<string> vString;
		short pos = 0;
		string sWord;
		while ((pos = line.find("#//#")) != std::string::npos)
		{
			sWord = line.substr(0, pos);
			if (sWord != " ")
			{
				vString.push_back(sWord);
			}
			line.erase(0, pos + 4);
		}
		if (line != "")
		{
			vString.push_back(line);
		}
		return vString;
	}
	static clsCurrency _ConvertLineToCurrencyObject(string line)
	{
		vector<string> vString = Split(line);
		return clsCurrency(enMode::UpdateMode, vString[0], vString[1], vString[2], stof(vString[3]));
	}
	static vector<clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector<clsCurrency> vCurrencies;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string line;
			while (getline(MyFile, line))
			{
				clsCurrency Currency = _ConvertLineToCurrencyObject(line);
				vCurrencies.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencies;
	}
	void _Update()
	{
		vector<clsCurrency> vCurrencys;
		vCurrencys = _LoadCurrencysDataFromFile();
		for (clsCurrency& C : vCurrencys)
		{
			if (C.CurrencyCode() == _CurrencyCode)
			{
				C = *this;
				break;
			}
		}
	}
	static string UpperAllString(string line)
	{
		for (short i = 0; i < line.length(); i++)
		{
			line[i] = toupper(line[i]);
		}
		return line;
	}

public:
	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return _Mode == enMode::EmptyMode;
	}

	string Countery()
	{
		return _Country;
	}

	string CurrencyCode()
	{
		return _CurrencyCode;
	}

	string CurrencyName()
	{
		return _CurrencyName;
	}

	float Rate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = UpperAllString(CurrencyCode);
		vector<clsCurrency>vCurrencies = _LoadCurrencysDataFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (C.CurrencyCode() == CurrencyCode)
			{
				return C;
			}
		}
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);

	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = UpperAllString(Country);
		vector<clsCurrency>vCurrencies = _LoadCurrencysDataFromFile();
		for (clsCurrency& C : vCurrencies)
		{
			if (UpperAllString(C.Countery()) == Country)
			{
				return C;
			}
		}
		return clsCurrency(enMode::EmptyMode, "", "", "", 0);

	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
		return  !Currency.IsEmpty();
	}

	static vector<clsCurrency> GetCurrenciesList()
	{
		return _LoadCurrencysDataFromFile();
	}

	float ConvertToUSDCurrency(short amount)
	{
		return (float)(amount / Rate());
	}

	float ConvertToOtherCurrency(float amount, clsCurrency Currency2)
	{
		float AmountInUSD = ConvertToUSDCurrency(amount);
		if (Currency2.CurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		else
		{
			return (float)(AmountInUSD * Currency2.Rate());
		}
	}

};

