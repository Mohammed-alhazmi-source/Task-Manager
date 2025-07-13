#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsTasksManagement.h"
#include "clsTask.h"
#include "clsUtil.h"

class clsAddTaskScreen : protected clsScreen
{
private:
	static void _CleanScreenAndDrawScreen()
	{
		system("cls");
		_DrawHeaderScreen("\t       Add Task Screen");
	}

	static clsTask::stTaskInfo _ReadTaskInfo()
	{
		clsTask::stTaskInfo Task;

		cout << "\nPlease Enter TaskID : ";
		Task.Id = clsInputValidate::ReadNumber<int>();
		
		if (Task.Id == 0)
			return Task;

		while (clsTasksManagement::FindTaskByIdFromFile(Task.Id))
		{
			cout << Task.Id << " Is Exists, Enter Again : ";
			Task.Id = clsInputValidate::ReadNumber<int>();

			if (Task.Id == 0)
				return Task;
		}

		cout << "\n\nRead Task Info\n";

		cout << "Please Enter Description : ";
		getline(cin >> ws, Task.Description);

		Task.StartDate.GetSystemDate();

		if (LinkedList.Count() == 0)
		{
			Task.EndDate = clsDate::IncreaseDateByOneWeek(clsDate::GetSystemDate());
		}

		else
			Task.EndDate = clsDate::AddOneDay(LinkedList.LastNode()->Data.EndDate);

		return Task;
	}

	static void _Add()
	{
		char AddMore = 'n';

		do
		{
			cout << "\n\nExit[0].\n";
			clsTask::stTaskInfo Task = _ReadTaskInfo();

			if (Task.Id == 0)
				return;

			if (clsTasksManagement::AddTask(Task))
			{
				cout << "Added Successfully...\n";
				AddMore = clsUtil::DoYouWantToContinue("Do You Want To Add More ? y/n ? ");
				if (AddMore == 'Y' || AddMore == 'y')
					_CleanScreenAndDrawScreen();
			}

			else
			{
				cout << "Added Failed:-(\n";
				AddMore = 'n';
			}
		} while (AddMore == 'Y' || AddMore == 'y');
	}

public:
	static void ShowAddTaskScreen()
	{
		_CleanScreenAndDrawScreen();
		_Add();
	}
};