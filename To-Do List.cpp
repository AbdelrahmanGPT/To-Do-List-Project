#include<iostream>
#include<vector>
#include<string>
#include"ABODAstd.h"

using namespace std;

enum MenuChoice{AddATask = 1 , EditATask = 2 , RemoveATask = 3 , ShowTasksMenu = 4 , ClearTaskMenu = 5 , Exit = 6};

int ReadTaskNumber(int From, int To)
{
		string Message = "ENTER TASK NUMBER (BETWEEN " + to_string(From) + " & " + to_string(To) + ")";

		return ValidateNumberInRange(From, To, Message);
}

string ReadTask()
{
	return ReadSentence("ENTER THE TASK YOU WANT TO ADD");
}

void AddTask(vector<string>&TasksMenu, string &Task)
{
	TasksMenu.push_back(Task);
	cout << "THE TASK IS ADDED SUCCESSFULLY\n";
}

void PrintTasksMenu(vector<string>& TasksMenu)
{
	if (TasksMenu.empty() == true)
	{
		cout << "THE TASKS MENU IS EMPTY PLEASE ADD TASKS\n";
	}

	else
	{
		cout << "NUMBER OF TASKS = " << TasksMenu.size() << "\n";
		cout << "---------------------------------------------------\n";
		for (int i = 0; i < TasksMenu.size(); i++)
		{
			cout << "TASK [" << i + 1 << "] : " << TasksMenu[i] << "\n";
		}
		cout << "---------------------------------------------------\n";

	}
}

void EditTask(vector<string>& TasksMenu)
{
	if (TasksMenu.empty())
	{
		cout << "THE TASKS MENU IS EMPTY PLEASE ADD TASKS\n";
	}

	else
	{
		PrintTasksMenu(TasksMenu);
		int TaskNumber = ReadTaskNumber(1, TasksMenu.size());
		string NewTaskEdit = ReadSentence("ENTER THE NEW TASK");

		TasksMenu[TaskNumber - 1] = NewTaskEdit;
		cout << "THE TASK [" << TaskNumber << "] IS EDITTED SUCCESSFULLY\n";
	}
	
}

void RemoveTask(vector<string>&TasksMenu)
{
	if (TasksMenu.empty() == true)
	{
		cout << "THE TASKS MENU IS EMPTY PLEASE ADD TASKS\n";
	}

	else
	{
		PrintTasksMenu(TasksMenu);
		int TaskNumber = ReadTaskNumber(1, TasksMenu.size());
		TasksMenu.erase(TasksMenu.begin() + (TaskNumber - 1));
		cout << "THE TASK [" << TaskNumber << "] IS REMOVED SUCCESSFULLY\n";
	}
}

void ClearTasksMenu(vector<string>& TasksMenu)
{
	TasksMenu.clear();
	cout << "THE TASKS MENU IS CLEARED SUCCESSFULY\n";
}

void PrintMainMenu()
{
	cout << "---------------------------\n" <<
		"ADD A TASK       : 1\n" <<
		"EDIT A TASK      : 2\n" <<
		"REMOVE A TASK    : 3\n" <<
		"SHOW TASKS MENU  : 4\n" <<
		"CLEAR TASKS MENU : 5\n" <<
		"EXIT             : 6\n" <<
		"---------------------------\n";
}

MenuChoice ReadMenuChoice()
{
	return (MenuChoice)(ValidateNumberInRange(1, 6));
}

void To_Do_List()
{
	cout << "WELCOME TO TO-DO LIST\n";
	vector<string>TasksMenu;
	LoadDataFromFileToVector("Tasks.txt", TasksMenu);

	while (true)
	{
		
		PrintMainMenu();
		MenuChoice MenuChoice = ReadMenuChoice();
		if (MenuChoice == MenuChoice::AddATask)
		{
			string Task = ReadTask();
			AddTask(TasksMenu , Task);
		}

		else if (MenuChoice == MenuChoice::EditATask)
		{
			EditTask(TasksMenu);
		}

		else if (MenuChoice == MenuChoice::RemoveATask)
		{
			RemoveTask(TasksMenu);
		}

		else if (MenuChoice == MenuChoice::ShowTasksMenu)
		{
			PrintTasksMenu(TasksMenu);
		}

		else if (MenuChoice == MenuChoice::ClearTaskMenu)
		{
			ClearTasksMenu(TasksMenu);
		}

 		else if (MenuChoice == MenuChoice::Exit)
		{
			SaveVectorDataToFile("Tasks.txt", TasksMenu);
			cout << "GOOD BYE :)\n";
			break;
		}

		else
		{
			cout << "INVALID CHOICE\n";
		}
	}
}

int main()
{
	
	To_Do_List();

	return 0;
}