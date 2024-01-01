#include<iostream>
#include<vector>
#include<string>

using namespace std;

enum MenuChoice{AddATask= 1 , RemoveATask = 2 , ShowTasksMenu= 3 , Exit = 4};

short ValidateNumberInRange(short From, short To)
{
	short Number;
	do
	{
		cout << "ENTER A CHOICE BETWEEN " << From << " & " << To << "\n";
		cin >> Number;

	} while (Number < From || Number > To);

	return Number;
}

int ReadTaskNumber(int From, int To)
{
	int Number;
	do
	{
		cout << "ENTER TASK NUMBER (BETWEEN " << From << " & " << To << ")\n";
		cin >> Number;

	} while (Number < From || Number > To);

	return Number;
}

string ReadSentence(string Message)
{
	string Sentence;
	cout << Message << "\n";
	cin.ignore(1 , '\n');
	getline(cin, Sentence);

	return Sentence;
}

void AddTask(vector<string>&TasksMenu, string &Task)
{
	TasksMenu.push_back(Task);
	cout << "THE TASK IS ADDED SUCCESSFULLY\n";
}

void PrintTasksMenu(vector<string>TasksMenu)
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

void PrintMainMenu()
{
	cout << "---------------------------\n" <<
		"ADD A TASK      : 1\n" <<
		"REMOVE A TASK   : 2\n" <<
		"SHOW TASKS MENU : 3\n" <<
		"EXIT            : 4\n" <<
		"---------------------------\n";
}

MenuChoice ReadMenuChoice()
{
	return (MenuChoice)(ValidateNumberInRange(1, 4));
}

void To_Do_List()
{
	cout << "WELCOME TO TO-DO LIST\n";
	vector<string>TasksMenu;
	while (true)
	{
		
		PrintMainMenu();
		MenuChoice MenuChoice = ReadMenuChoice();
		if (MenuChoice == MenuChoice::AddATask)
		{
			string Task = ReadSentence("ENTER THE TASK YOU WANT TO ADD");
			AddTask(TasksMenu, Task);
		}

		else if (MenuChoice == MenuChoice::RemoveATask)
		{
			RemoveTask(TasksMenu);
		}

		else if (MenuChoice == MenuChoice::ShowTasksMenu)
		{
			PrintTasksMenu(TasksMenu);
		}

 		else if (MenuChoice == MenuChoice::Exit)
		{
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