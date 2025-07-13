#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include <iomanip>
using namespace std;

class clsUtil
{
public:

	static short ReadOption(short From, short To, string Message = "Choose An Operation From 1 To 11 ? ")
	{
		short Choose = 0;
		cout << endl << setw(42) << left << "" << Message;
		Choose = clsInputValidate::ReadNumberBetween(From, To);
		return Choose;
	}

	static void PrintMessage(const string& Message = "")
	{
		cout << "\n\n";
		cout << setw(35) << left << "" << "____________________________________________________";
		cout << "\n" << setw(45) << left << "" << Message;
		cout << "\n" << setw(35) << left << "" << "____________________________________________________\n";
	}

	static char DoYouWantToContinue(string AnswerMessage = "")
	{
		char Answer = 'n';
		cout << AnswerMessage;
		cin >> Answer;
		return Answer;
	}
};

