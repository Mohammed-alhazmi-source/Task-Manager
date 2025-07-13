#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class clsInputValidate
{
public:
	template <typename T> static T ReadNumber(string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number;
		while (!(cin >> Number))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << ErrorMessage;
		}
		return Number;
	}

	template<typename T> static T ReadNumberBetween(T From, T To, string ErrorMessage = "Invalid Number, Enter again\n")
	{
		T Number = ReadNumber<T>();

		while (!IsNumberBetween(Number, From, To))
		{
			cout << "\nPlease Enter Number Of Range From " << From << " To " << To << " , Enter Again : ";
			Number = ReadNumber<T>();
		}
		return Number;
	}

	template<typename T> static T ReadNumberBetween(string Message, T From, T To, string ErrorMessage = "Invalid Number, Enter again\n")
	{
		cout << "\n" << setw(42) << left << "" << Message;
		return ReadNumberBetween(From, To);
	}

	template <typename T> static bool IsNumberBetween(T Number, T From, T To)
	{
		return (Number >= From && Number <= To);
	}

	static string ReadString()
	{
		string  S1 = "";
		getline(cin >> ws, S1);
		return S1;
	}

	static string ReadString(string Message)
	{
		cout << Message;
		return ReadString();
	}
};

