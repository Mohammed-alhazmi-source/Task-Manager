#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsUtil.h"
#include "clsTasksManagement.h"
#include "clsAddTaskScreen.h"
#include "clsDeleteTaskScreen.h"
#include "clsFindTaskScreen.h"
#include "clsShowTasksIncompleteScreen.h"
#include "clsShowTasksCompleteScreen.h"
#include "clsShowAllTasksScreen.h"

using namespace std;


class clsMainScreen : protected clsScreen
{
	enum enMainMenuOptions
	{
		AddTask = 1, DeleteTask = 2, ShowTasksIncomplete = 3,
		ShowTasksComplete = 4, ShowAllTasks = 5, Find = 6, Exit = 7
	};

	static short _ReadOption()
	{
		return clsUtil::ReadOption(1, 7, "Choose An Operation From 1 To 7 ? ");
	}

	static void _GoBackToMainMenu()
	{
		cout << endl;
		system("pause");
		ShowMainMenu();
	}

	static void _ShowAddTaskScreen()
	{
		clsAddTaskScreen::ShowAddTaskScreen();
	}

	static void _ShowDeleteTaskScreen()
	{
		clsDeleteTaskScreen::ShowDeleteTaskScreen();
	}

	static void _ShowFindTaskScreen()
	{
		clsFindTaskScreen::ShowFindTaskScreen();
	}

	static void _ShowTasksIncompleteScreen()
	{
		clsShowTasksIncompleteScreen::ShowTasksIncompleteScreen();
	}

	static void _ShowTasksCompleteScreen()
	{
		clsShowTasksCompleteScreen::ShowTasksCompleteScreen();
	}

	static void _ShowAllTasksScreen()
	{
		clsShowAllTasksScreen::ShowAllTasksScreen();
	}

	static void _Exit()
	{
		cout << endl << "--------------------------------------";
		cout << "\nEnd Program :-)";
		cout << endl << "--------------------------------------\n";
	}

	static void _ExecuteTheSelectedOption(enMainMenuOptions Option)
	{
		switch (Option)
		{
		case clsMainScreen::AddTask:
		{
			system("cls");
			_ShowAddTaskScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::DeleteTask:
		{
			system("cls");
			_ShowDeleteTaskScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::ShowTasksIncomplete:
		{
			system("cls");
			_ShowTasksIncompleteScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::ShowTasksComplete:
		{
			system("cls");
			_ShowTasksCompleteScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::ShowAllTasks:
		{
			system("cls");
			_ShowAllTasksScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::Find:
		{
			system("cls");
			_ShowFindTaskScreen();
			_GoBackToMainMenu();
			break;
		}

		case clsMainScreen::Exit:
		{
			system("cls");
			_Exit();
			break;
		}
		}
	}

	static void _PrintMainMenu()
	{
		cout << "\n\n\n" << setw(42) << left << "" << "======================================";
		cout << "\n" << setw(42) << left << "" << "Enter <1> Add Task.";
		cout << "\n" << setw(42) << left << "" << "Enter <2> Delete Task.";
		cout << "\n" << setw(42) << left << "" << "Enter <3> Tasks Incomplete.";
		cout << "\n" << setw(42) << left << "" << "Enter <4> Tasks Complete.";
		cout << "\n" << setw(42) << left << "" << "Enter <5> All Tasks.";
		cout << "\n" << setw(42) << left << "" << "Enter <6> Find Task.";
		cout << "\n" << setw(42) << left << "" << "Enter <7> Exit.";
		cout << "\n" << setw(42) << left << "" << "======================================";
	}

public:
	static void ShowMainMenu()
	{
		system("cls");
		_DrawHeaderScreen("\t     Tasks Management System");
		_PrintMainMenu();
		_ExecuteTheSelectedOption((enMainMenuOptions)_ReadOption());
	}
};