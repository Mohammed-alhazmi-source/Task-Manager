#pragma once
#include <iostream>
#include "clsInputValidate.h"
#include "clsTasksManagement.h"
#include "clsTask.h"
#include <iomanip>
#include "clsScreen.h"
#include "clsDate.h"
using namespace std;

class clsShowTasksCompleteScreen :protected clsScreen
{
private:
    static void _PrintTaskRecordLine(clsTask::stTaskInfo& Task)
    {
        cout << setw(8) << left << "" << "| " << setw(15) << left << Task.Id;
        cout << "| " << setw(20) << left << Task.Description;
        cout << "| " << setw(12) << left << clsDate::DateToString(Task.StartDate);
        cout << "| " << setw(20) << left << clsDate::DateToString(Task.EndDate);
        cout << "| " << setw(10) << left << (Task.Completed == false ? "Incomplete" : "Complete");
        cout << endl;
    }

    static void ShowTasksList()
    {
        vector<clsTask::stTaskInfo> vTasks;
        string Title = "\t Tasks Complete Screen\n";
        string SubTitle = "\t    (" + to_string(clsTasksManagement::TotalCompleteTasks()) + ") Task(s).";

        system("cls");
        _DrawHeaderScreen(Title, SubTitle);

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        cout << setw(8) << left << "" << "| " << left << setw(15) << "Id";
        cout << "| " << left << setw(20) << "Description";
        cout << "| " << left << setw(12) << "Start Date";
        cout << "| " << left << setw(20) << "End Date";
        cout << "| " << left << setw(10) << "Completed";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;


        if (clsTasksManagement::TotalCompleteTasks() == 0)
            cout << "\t\t\t\tNo Tasks Available In the System!";

        else
        {
            Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();
            while (Task != nullptr)
            {
                if (Task->Data.Completed == true)
                    _PrintTaskRecordLine(Task->Data);
                
                Task = Task->Next;
            }
        }
            /*for (clsTask::stTaskInfo &Task : vTasksLoaded)
            {
                if (Task.Completed == true)
                    _PrintTaskRecordLine(Task);
            }*/

        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n" << endl;
    }


public:
    static void ShowTasksCompleteScreen()
    {
        system("cls");
        ShowTasksList();
    }
};