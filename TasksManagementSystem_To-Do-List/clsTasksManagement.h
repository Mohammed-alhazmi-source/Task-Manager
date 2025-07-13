#pragma once
#include <iostream>
#include "clsTask.h"
#include "SinglyLinkedList.h"
#include "Global.h"
#include <sstream>
#include <fstream>
using namespace std;


class clsTasksManagement
{
    // ÊÍæíá ßÇÆä ÇáãåãÉ Åáì ÓØÑ äÕí áÊÎÒíäå İí Çáãáİ
    static string _ConvertTaskObjectToLine(clsTask::stTaskInfo& TaskInfo)
    {
        ostringstream oss;
        oss << to_string(TaskInfo.Id) + "#//#"
            << TaskInfo.Description + "#//#"
            << clsDate::DateToString(TaskInfo.StartDate) + "#//#"
            << clsDate::DateToString(TaskInfo.EndDate) + "#//#"
            << (TaskInfo.Completed == false ? "InComplete" : "Complete");
        return oss.str();
    }

    // ÊÍæíá ÓØÑ äÕí ãä Çáãáİ Åáì ßÇÆä ãåãÉ
    static clsTask::stTaskInfo _ConvertLineToTaskObject(string DataLine)
    {
        vector<string> vDataLine = clsString::Split(DataLine, "#//#");
        clsTask::stTaskInfo Task;

        if (vDataLine.size() < 5)
            cout << "Error The data is incomplete. ";
        else
        {
            Task.Id = stoi(vDataLine[0]);
            Task.Description = vDataLine[1];
            Task.StartDate = clsDate::StringToDate(vDataLine[2]);
            Task.EndDate = clsDate::StringToDate(vDataLine[3]);
            Task.Completed = (vDataLine[4] == "InComplete" ? false : true);
            return Task;
        }
    }

    // ÅÖÇİÉ ãåãÉ Åáì Çáãáİ
    static bool _AddTaskDataToFile(clsTask::stTaskInfo& Task)
    {
        ofstream  MyFile;
        MyFile.open(TasksFile, ios::out | ios::app);
        if (MyFile.is_open())
        {
            string Line = _ConvertTaskObjectToLine(Task);
            MyFile << Line << endl;
            MyFile.close();
            return true;
        }
        return false;
    }

    // ÊÍãíá ßá ÇáãåÇã ãä Çáãáİ Åáì ÇáĞÇßÑÉ
    static SinglyLinkedList<clsTask::stTaskInfo> _LoadTasksDataFromFile()
    {
        ifstream MyFile(TasksFile);
        if (MyFile.is_open())
        {
            string Line = "";
            while (getline(MyFile, Line))
                LinkedList.InsertLast(_ConvertLineToTaskObject(Line));
        }
        return LinkedList;
    }

    // ÊÍÏíÏ åá ÇáãåãÉ ÊÚÊÈÑ ãßÊãáÉ ÍÓÈ ÇáÊÇÑíÎ ÇáÍÇáí
    static bool _IsTaskCompleted(const clsTask::stTaskInfo& Task)
    {
        return (clsDate::CompareDates(Task.EndDate, clsDate::GetSystemDate()) != clsDate::After);
    }

    // ÊÍÏíË ãÍÊæì Çáãáİ Èßá ÇáãåÇã ÇáÍÇáíÉ
    static void _UpdateTasksDataFile()
    {
        ofstream MyFile(TasksFile, ios::out);
        if (!MyFile.is_open())
        {
            cerr << "The task file has not been opened for writing.";
            return;
        }

        Node<clsTask::stTaskInfo>* Temp = LinkedList.FirstNode();
        while (Temp != nullptr)
        {
            MyFile << _ConvertTaskObjectToLine(Temp->Data) << endl;
            Temp = Temp->Next;
        }
    }

    // ÍİÙ ÇáãåÇã ÇáÛíÑ ãÑÔÍÉ ááÍĞİ İí Çáãáİ
    static void _SaveAllTaskToFile()
    {
        fstream MyFile(TasksFile, ios::out);

        if (!MyFile.is_open())
        {
            cerr << "Error Don't Open File";
            return;
        }

        Node<clsTask::stTaskInfo>* Temp = LinkedList.FirstNode();
        string Line = "";
        while (Temp != nullptr)
        {
            if (Temp->Data.MarkedDeleted == false)
            {
                Line = _ConvertTaskObjectToLine(Temp->Data);
                MyFile << Line << endl;
            }
            Temp = Temp->Next;
        }       
    }  

    // ÊÍÏíË ÍÇáÉ ÇáãåÇã ÊáŞÇÆíğÇ ÍÓÈ ÇáÊÇÑíÎ (ãßÊãáÉ Ãæ áÇ)
    static void _UpdateTasksState()
    {
       _LoadTasksDataFromFile();
        bool FileStatus = false;

        Node<clsTask::stTaskInfo>* Temp = LinkedList.FirstNode();
        while (Temp != nullptr)
        {
            if (!Temp->Data.Completed && _IsTaskCompleted(Temp->Data))
            {
                Temp->Data.Completed = true;
                FileStatus = true;
            }
            Temp = Temp->Next;
        }     

        if (FileStatus)
            _UpdateTasksDataFile();
    }      
  
public:  
    // ÅÖÇİÉ ãåãÉ ÌÏíÏÉ Åáì ÇáŞÇÆãÉ æÇáãáİ
    static bool AddTask(clsTask::stTaskInfo& Task)
    {
        if (IsTaskByIdExists(Task.Id))
        {
            cout << "This Task Already exists";
            return false;
        }

        if (LinkedList.IsEmpty())
            LinkedList.InsertFirst(Task);
        else
            LinkedList.InsertLast(Task);

        return _AddTaskDataToFile(Task);
    }

    // ÍĞİ ãåãÉ ÈäÇÁğ Úáì ÑŞã ÇáãÚÑİ
    static void DeleteTaskByID(int ID)
    {
        if (!FindTaskByIdFromFile(ID))
        {
            cerr << ID << " Not Found";
            return;
        }

        Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();

        while (Task != nullptr)
        {
            if (Task->Data.Id == ID)
            {
                Task->Data.MarkedDeleted = true;
                break;
            }
            Task = Task->Next;
        }
      
        _SaveAllTaskToFile();
        DeleteTaskNodeById(ID);
    }

    // ÍĞİ ãåãÉ ÈäÇÁğ Úáì ÇáæÕİ
    static void DeleteTaskByDescription(string& Description)
    {
        if (!FindTaskByDescriptionFromFile(Description))
        {
            cout << Description << " Not Found";
            return;
        }

        Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();

        while (Task != nullptr)
        {
            if (Task->Data.Description == Description)
            {
                Task->Data.MarkedDeleted = true;
                break;
            }
            Task = Task->Next;
        }
     
        _SaveAllTaskToFile();
        DeleteTaskNodeByDescription(Description);
    }

    // ÍĞİ ÚŞÏÉ ãåãÉ ÈäÇÁğ Úáì ÑŞã ÇáãÚÑİ ãä Çáåíßá İí ÇáĞÇßÑÉ
    static bool DeleteTaskNodeById(int ID)
    {
        Node<clsTask::stTaskInfo>* Temp = FindTaskByIdFromLinkedList(ID);
        if (Temp == nullptr)
        {
            return false;
        }
        LinkedList.DeleteNode(Temp->Data);
        return true;
    }

    // ÍĞİ ÚŞÏÉ ãåãÉ ÈäÇÁğ Úáì ÇáæÕİ ãä Çáåíßá İí ÇáĞÇßÑÉ
    static bool DeleteTaskNodeByDescription(string& Description)
    {
        Node<clsTask::stTaskInfo>* Temp = FindTaskByDescriptionFromLinkedList(Description);

        if (Temp == nullptr)
        {
            return false;
        }

        LinkedList.DeleteNode(Temp->Data);
        return true;
    }

    // ÇáÈÍË Úä ãåãÉ ÈÑŞã ÇáãÚÑİ İí Çáåíßá ÇáããËá İí ÇáĞÇßÑÉ 
    static Node<clsTask::stTaskInfo>* FindTaskByIdFromLinkedList(int ID)
    {       
         Node<clsTask::stTaskInfo>* Temp = LinkedList.FirstNode();
         while (Temp != nullptr)
         {
             if (Temp->Data.Id == ID)
                 return Temp;

             Temp = Temp->Next;
         }
         return nullptr;
    }

    // ÇáÈÍË Úä ÚŞÏÉ ãåãÉ ÍÓÈ ÇáæÕİ İí Çáåíßá ÇáããËá İí ÇáĞÇßÑÉ
    static Node<clsTask::stTaskInfo>* FindTaskByDescriptionFromLinkedList(string& Description)
    {
        Node<clsTask::stTaskInfo>* Temp = LinkedList.FirstNode();
        while (Temp != nullptr)
        {
            if (Temp->Data.Description == Description)
                return Temp;

            Temp = Temp->Next;
        }
        return nullptr;
    }

    // ÇáÈÍË Úä ãåãÉ ÈÑŞã ÇáãÚÑİ 
    static bool FindTaskByIdFromFile(int ID)
    {
        ifstream MyFile(TasksFile, ios::in);

        if (!MyFile.is_open())
        {
            cout << "Don't Open File";
            return false;
        }

        string Line;
        while (getline(MyFile, Line))
        {
            if (_ConvertLineToTaskObject(Line).Id == ID)
                return true;
        }
        return false;      
    }

    // ÇáÈÍË Úä ãåãÉ ÍÓÈ ÇáæÕİ
    static bool FindTaskByDescriptionFromFile(string &Description)
    {
        ifstream MyFile(TasksFile, ios::in);

        if (!MyFile.is_open())
        {
            return false;
        }

        string Line;
        while (getline(MyFile,Line))
        {
            if (_ConvertLineToTaskObject(Line).Description == Description)
                return true;
        }
        return false;
    }

    // ÅÑÌÇÚ ÚÏÏ ÇáãåÇã ÇáÅÌãÇáí
    static int TotalNumberTasks()
    {
        return LinkedList.Count();      
    }

    // ÅÑÌÇÚ ÚÏÏ ÇáãåÇã ÛíÑ ÇáãßÊãáÉ
    static int TotalIncompleteTasks()
    {
        int CountTasks = 0;
       
        Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();
        while (Task != nullptr)
        {
            if (Task->Data.Completed == false)
                CountTasks++;

            Task = Task->Next;
        }       
        return CountTasks;
    }

    // ÅÑÌÇÚ ÚÏÏ ÇáãåÇã ÇáãßÊãáÉ
    static int TotalCompleteTasks()
    {
        int CountTasks = 0;
       
        Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();
        while (Task != nullptr)
        {
            if (Task->Data.Completed == true)
                CountTasks++;

            Task = Task->Next;
        }
       
        return CountTasks;
    }   

    static void LoadAllTaskToMemory()
    {
        _UpdateTasksState();
    }

    // ÇáÊÃßÏ ãä æÌæÏ ãåãÉ ãÓÈŞÇ
    static bool IsTaskByIdExists(int ID)
    {
        Node<clsTask::stTaskInfo>* Task = LinkedList.FirstNode();
        while (Task != nullptr)
        {
            if (Task->Data.Id == ID)
                return true;

            Task = Task->Next;
        }
       
        return false;
    }

    // ÇÑÌÇÚ ÈíÇäÇÊ ÚŞÏÉ ÍÓÈ ãÚÑİåÇ
    static clsTask::stTaskInfo GetTaskById(int ID)
    {       
        Node<clsTask::stTaskInfo>* TaskTemp = LinkedList.FirstNode();
        while (TaskTemp != nullptr)
        {
            if (TaskTemp->Data.Id == ID)
                return TaskTemp->Data;

            TaskTemp = TaskTemp->Next;
        }
       
        if (TaskTemp != nullptr)
            return TaskTemp->Data;
         
        clsTask::stTaskInfo Task; // default 
        return Task;
    }
};