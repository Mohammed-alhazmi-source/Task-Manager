#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsTask.h"
#include "clsTasksManagement.h"
#include "clsInputValidate.h"
#include "clsUtil.h"

class clsDeleteTaskScreen : protected clsScreen
{
private:
	static void _CleanScreenAndDrawScreen()
	{
		system("cls");
		_DrawHeaderScreen("\t     Delete Task Screen");
	}

	static void _Execute()
	{
		char Answer = 'n';

		if (LinkedList.IsEmpty())
		{
			clsUtil::PrintMessage("\t    Tasks File Is Empty");
			return;
		}

		do
		{
			cout << "\n\nExit[0].\n";
			cout << "\nPlease Enter TaskId : ";
			int Id = clsInputValidate::ReadNumber<int>();

			if (Id == 0)
				return;

			while (!clsTasksManagement::FindTaskByIdFromFile(Id))
			{
				cout << Id << " Not Found, Enter Again : ";
				Id = clsInputValidate::ReadNumber<int>();
				
				if (Id == 0)
					return;
			}

			Answer = clsUtil::DoYouWantToContinue("Are You Sure Delete ? y/n ? ");
			if (Answer == 'Y' || Answer == 'y')
			{
				clsTasksManagement::DeleteTaskByID(Id);
				cout << "\nDeleted Successfully:-)\n";
			}

			if (Answer == 'Y' || Answer == 'y')
			{
				Answer = clsUtil::DoYouWantToContinue("Do You Want To Delete More ? y/n ? ");
				if (Answer == 'Y' || Answer == 'y')
					_CleanScreenAndDrawScreen();
			}
		} while (Answer == 'Y' || Answer == 'y');
	}

	static void _Delete()
	{
		_Execute();
	}

public:
	static void ShowDeleteTaskScreen()
	{
		_CleanScreenAndDrawScreen();
		_Delete();
	}
};