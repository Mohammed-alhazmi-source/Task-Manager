#pragma once
#include <iostream>
#include "clsTasksManagement.h"
#include "clsUtil.h"
#include "clsInputValidate.h"
#include "clsScreen.h"
#include "clsDate.h"

class clsFindTaskScreen : protected clsScreen
{
private:
	static void _PrintTaskCard(const clsTask::stTaskInfo &Task)
	{
		cout << "\n\nTask Card : " << Task.Id << "\n";
		cout << "--------------------------------------\n";
		cout << "ID          : " << Task.Id << endl;
		cout << "Description : " << Task.Description << endl;
		cout << "Start Date  : " << clsDate::DateToString(Task.StartDate) << endl;
		cout << "End Date    : " << clsDate::DateToString(Task.EndDate) << endl;
		cout << "Completed   : " << (Task.Completed == false ? "false" : "true") << endl;
		cout << "--------------------------------------\n";
	}

	static void _Execute()
	{

		if (LinkedList.IsEmpty())
		{
			clsUtil::PrintMessage("\t    Tasks File Is Empty");
			return;
		}

		cout << "\n\nExit[0].\n";
		cout << "\nPlease Enter TaskId : ";
		int Id = clsInputValidate::ReadNumber<int>();

		if (Id == 0)
			return;

		if (clsTasksManagement::IsTaskByIdExists(Id))
			_PrintTaskCard(clsTasksManagement::GetTaskById(Id));

		else
			cout << Id << " Is Not Found ...\n";
	}

	static void _Find()
	{
		_Execute();
	}

public:
	static void ShowFindTaskScreen()
	{
		system("cls");
		_DrawHeaderScreen("\t      Find Task Screen");
		_Find();
	}
};