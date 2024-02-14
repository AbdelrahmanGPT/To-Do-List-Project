#include<iostream>
#include<vector>
#include<string>
#include"ABODAstd.h"

using namespace std;

enum MenuChoice{AddATask = 1 , EditATask = 2 , RemoveATask = 3 , ShowTasksMenu = 4 , FindTasks = 5 , ClearTaskMenu = 6 , ChangeSystemThemes = 7 , Exit = 8};

enum EditTaskMenuChoices {EditTitle = 1 , EditDescription = 2 };

enum FindTaskMenuChoices {FindByTitle = 1 , FindByDescription = 2};

string TasksDataFileName = "TASKS.txt";

struct Task
{
	string Title;
	string Description;
};

void SaveTasksDataToFile(vector<Task> & Tasks);

int ReadTaskNumber(int From, int To)
{
		string Message = "ENTER TASK NUMBER (BETWEEN " + to_string(From) + " & " + to_string(To) + ")";

		return ValidateNumberInRange(From, To, Message);
}

Task ReadTask()
{
	Task Task;
	Task.Title = ReadStringLine("ENTER THE TASK TITLE YOU WANT TO ADD");
	Task.Description = ReadStringLine("ENTER THE TASK DESCRIPTION YOU WANT TO ADD");

	return Task;
}

void AddTask(vector<Task>&TasksMenu)
{
	SectionBanner("ADD TASK SCREEN", 2 , "=");
	Task Task = ReadTask();
	TasksMenu.push_back(Task);
	SaveTasksDataToFile(TasksMenu);
	cout << "\nTHE TASK IS ADDED SUCCESSFULLY\n";
}

void PrintTasksMenu(vector<Task>& TasksMenu)
{


	if (TasksMenu.empty() == true)
	{
		SectionBanner("THE TASKS MENU IS EMPTY PLEASE ADD TASKS", 2, "=");
	}

	else
	{
		printf("\n\n");
		cout << Tab(5) << "TASK LIST (" << TasksMenu.size() << ") TASK(S).";

		PrintLineWithNewLines("_", 105);
		PrintStringElementInTable("NO.", 6);
		PrintStringElementInTable("TASK TITLE", 15);
		PrintStringElementInTable("TASK DESCRIPTION", 80);
		PrintLineWithNewLines("_", 105);
		

		int TasksCounter = 0;
		for (Task& Task : TasksMenu)
		{
			PrintNumberElementInTable(++TasksCounter, 6);
			PrintStringElementInTable(Task.Title, 15);
			PrintStringElementInTable(Task.Description, 80);
			printf("\n");
		}

		PrintLineWithNewLines("_", 105 , 1 );

	}
}

void PrintEditTaskMenu()
{
	cout << "====================================================================\n\n";
	cout << Tab(3) << "EDIT TASK MENU SCREEN\n\n";
	cout << "====================================================================\n";
	cout << Tab(3) << "[1] EDIT TASK TITLE." << "\n";
	cout << Tab(3) << "[2] EDIT TASK DESCRIPTION." << "\n";
	cout << "====================================================================\n\n";
}

EditTaskMenuChoices ReadEditTaskMenuChoices()
{
	return (EditTaskMenuChoices)(ValidateNumberInRange(1, 2, "CHOOSE WHAT DO YOU WANT TO DO ? [1 TO 2] ? "));
}

void PerformEditTaskMenuChoice(EditTaskMenuChoices EditTaskMenuChoice , int TaskNumber , vector<Task>&TasksMenu)
{
	switch (EditTaskMenuChoice)
	{
	case EditTitle:
		TasksMenu[TaskNumber - 1].Title = ReadStringLine("ENTER NEW TASK TITLE");
		SaveTasksDataToFile(TasksMenu);
		printf("\nYOUR TASK TITLE IS EDITTED SUCCESSFULLY\n");
		break;
	case EditDescription:
		TasksMenu[TaskNumber - 1].Description = ReadStringLine("ENTER NEW TASK DESCRIPTION");
		SaveTasksDataToFile(TasksMenu);
		printf("\nYOUR TASK DESCRIPTION IS EDITTED SUCCESSFULLY\n");
		break;
	}
}

void EditTask(vector<Task>& TasksMenu)
{

	if (TasksMenu.empty())
	{
		SectionBanner("THE TASKS MENU IS EMPTY PLEASE ADD TASKS" , 2 , "=");
	}

	else
	{
		do
		{

			PrintTasksMenu(TasksMenu);
			int TaskNumber = ReadTaskNumber(1, TasksMenu.size());

			do
			{
				PrintEditTaskMenu();
				EditTaskMenuChoices EditTaskMenuChoice = ReadEditTaskMenuChoices();
				PerformEditTaskMenuChoice(EditTaskMenuChoice, TaskNumber , TasksMenu);
				SaveTasksDataToFile(TasksMenu);
			} while (DoYouWantToDoThisWithoutClear("DO YOU WANT TO EDIT ANOTHER INFORMATION ABOUT THIS TASK"));
			
			SaveTasksDataToFile(TasksMenu);
		} while (DoYouWantToDoThisWithClear("DO YOU WANT TO EDIT ANOTHER TASK"));
	}
	
}

void RemoveTask(vector<Task>&TasksMenu)
{
	SectionBanner("REMOVE TASK SCREEN", 2 , "=");

	if (TasksMenu.empty() == true)
	{
		cout << "\nTHE TASKS MENU IS EMPTY PLEASE ADD TASKS\n";
	}

	else
	{
		PrintTasksMenu(TasksMenu);
		int TaskNumber = ReadTaskNumber(1, TasksMenu.size());
		TasksMenu.erase(TasksMenu.begin() + (TaskNumber - 1));

		SaveTasksDataToFile(TasksMenu);
		cout << "\nTHE TASK [" << TaskNumber << "] IS REMOVED SUCCESSFULLY\n";
	}
}

void PrintFindTaskMenu()
{
	cout << "====================================================================\n\n";
	cout << Tab(3) << "FIND TASK MENU SCREEN\n\n";
	cout << "====================================================================\n";
	cout << Tab(3) << "[1] FIND TASK BY TITLE." << "\n";
	cout << Tab(3) << "[2] FIND TASK BY DESCRIPTION." << "\n";
	cout << "====================================================================\n\n";

}

FindTaskMenuChoices ReadFindTaskMenuChoices()
{
	return (FindTaskMenuChoices)(ValidateNumberInRange(1, 2, "CHOOSE WHAT DO YOU WANT TO DO ? [1 TO 2] ? "));
}

void FindTaskByTitle(vector<Task>&TasksMenu)
{
	string TaskTitle = ReadStringLine("PLEASE ENTER TASK TITLE");
	int SearchResults = 0;

	printf("\n\n%s SEARCH RESULT(S) FOR TASK TITLE (%s)\n" , Tab(5).c_str(), TaskTitle.c_str());

	PrintLineWithNewLines("_", 105);
	PrintStringElementInTable("NO.", 6);
	PrintStringElementInTable("TASK TITLE", 15);
	PrintStringElementInTable("TASK DESCRIPTION", 80);
	PrintLineWithNewLines("_", 105);

	for (Task& Task : TasksMenu)
	{
		if (LowerCaseAllString(TaskTitle) == LowerCaseAllString(Task.Title) || (LowerCaseAllString(Task.Title).find(TaskTitle) != std::string::npos))
		{
			PrintNumberElementInTable(++SearchResults, 6);
			PrintStringElementInTable(Task.Title, 15);
			PrintStringElementInTable(Task.Description, 80);
			printf("\n");
		}
	}

	PrintLineWithNewLines("_", 105);

	printf("\n%s%d SEARCH RESULT(S) ARE FOUND\n\n", Tab(5).c_str(), SearchResults);
}

void FindTaskByDescription(vector<Task>& TasksMenu)
{
	string TaskDescription = ReadStringLine("PLEASE ENTER TASK DESCRIPTION");
	int SearchResults = 0;

	printf("\n\n%s SEARCH RESULT(S) FOR TASK DESCRIPTION (%s)\n", Tab(5).c_str(), TaskDescription.c_str());

	PrintLineWithNewLines("_", 105);
	PrintStringElementInTable("NO.", 6);
	PrintStringElementInTable("TASK TITLE", 15);
	PrintStringElementInTable("TASK DESCRIPTION", 80);
	PrintLineWithNewLines("_", 105);

	for (Task& Task : TasksMenu)
	{
		if (LowerCaseAllString(TaskDescription) == LowerCaseAllString(Task.Description) || (LowerCaseAllString(Task.Description).find(TaskDescription) != std::string::npos))
		{
			PrintNumberElementInTable(++SearchResults, 6);
			PrintStringElementInTable(Task.Title, 15);
			PrintStringElementInTable(Task.Description, 80);
			printf("\n");
		}
	}

	PrintLineWithNewLines("_", 105);

	printf("\n%s%d SEARCH RESULT(S) ARE FOUND\n\n", Tab(5).c_str(), SearchResults);
}

void PerformFindTaskMenuChoice(FindTaskMenuChoices FindTaskMenuChoice , vector<Task> &TasksMenu)
{
	switch (FindTaskMenuChoice)
	{
	case FindByTitle:
		FindTaskByTitle(TasksMenu);
		break;
	case FindByDescription:
		FindTaskByDescription(TasksMenu);
		break;
	}
}

void FindTask(vector<Task>& TasksMenu)
{

	if (TasksMenu.empty() == true)
	{
		SectionBanner("THE TASKS MENU IS EMPTY PLEASE ADD TASKS\n" , 0 , "=");
	}

	else
	{
		do

		{
			PrintFindTaskMenu();
			FindTaskMenuChoices FindTaskMenuChoice = ReadFindTaskMenuChoices();
			PerformFindTaskMenuChoice(FindTaskMenuChoice, TasksMenu);

			
		} while (DoYouWantToDoThisWithClear("DO YOU WANT TO FIND ANOTHER TASK ?"));

		
	}
}

void ClearTasksMenu(vector<Task>& TasksMenu)
{
	SectionBanner("CLEAR TASKS SCREEN", 2 , "=");

	TasksMenu.clear();
	SaveTasksDataToFile(TasksMenu);
	cout << "THE TASKS MENU IS CLEARED SUCCESSFULY\n";
}

void PrintMainMenu()
{
	cout << "====================================================================\n\n";
	cout << Tab(3) << "CONTROL MENU					 \n\n";
	cout << "====================================================================\n";
	cout << Tab(3) << "[1] ADD A TASK." << "\n";
	cout << Tab(3) << "[2] EDIT A TASK." << "\n";
	cout << Tab(3) << "[3] REMOVE A TASK." << "\n";
	cout << Tab(3) << "[4] SHOW TASKS MENU." << "\n";
	cout << Tab(3) << "[5] FIND TASKS." << "\n";
	cout << Tab(3) << "[6] CLEAR TASKS MENU." << "\n";
	cout << Tab(3) << "[7] CHANGE SYSTEM THEME." << "\n";
	cout << Tab(3) << "[8] EXIT." << "\n";
	cout << "====================================================================\n\n";

}

MenuChoice ReadMenuChoice()
{
	return (MenuChoice)(ValidateNumberInRange(1, 8 , "CHOOSE WHAT YOU WANT TO DO [1 TO 8]"));
}

string TaskToRecord(Task& Task , string Separator)
{
	return Task.Title + Separator + Task.Description;
}

Task RecordToTask(string Record, string Separator)
{
	vector<string>TaskVector = SpiltStringWordsToVector(Record, Separator);

	Task Task;
	
	Task.Title = TaskVector[0];
	Task.Description = TaskVector[1];

	return Task;
}

void SaveTasksDataToFile(vector<Task>& Tasks)
{
	fstream File;
	File.open(TasksDataFileName, ios::out);

	if (File.is_open())
	{
		for (Task& Task : Tasks)
		{
			File << TaskToRecord(Task , "#//#") << "\n";
		}

		File.close();
	}
}

void LoadTasksDataFromFile(vector<Task>& Tasks)
{
	fstream File;

	File.open(TasksDataFileName, ios::in);

	if (File.is_open())
	{
		string Record;
		while (getline(File, Record))
		{
			Tasks.push_back(RecordToTask(Record , "#//#"));
		}

		File.close();
	}
}

void To_Do_List()
{
	LoadSystemThemeColorsFromFile();
	ChangeCLIColors(SystemThemeColor.BackgroundColor, SystemThemeColor.ForegroundColor);
	vector<Task>TasksMenu;
	LoadTasksDataFromFile(TasksMenu);
	StartProgram("TO-DO LIST", 2, "=", 60 , SystemThemeColor.BackgroundColor , SystemThemeColor.ForegroundColor);
	while (true)
	{
		ClearScreen();
		PrintMainMenu();
		MenuChoice MenuChoice = ReadMenuChoice();
		if (MenuChoice == MenuChoice::AddATask)
		{
			ClearScreen();
			AddTask(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

		else if (MenuChoice == MenuChoice::EditATask)
		{
			ClearScreen();
			EditTask(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

		else if (MenuChoice == MenuChoice::RemoveATask)
		{
			ClearScreen();
			RemoveTask(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

		else if (MenuChoice == MenuChoice::ShowTasksMenu)
		{
			ClearScreen();
			PrintTasksMenu(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}
		
		else if (MenuChoice == MenuChoice::FindTasks)
		{
			ClearScreen();
			FindTask(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

		else if (MenuChoice == MenuChoice::ClearTaskMenu)
		{
			ClearScreen();
			ClearTasksMenu(TasksMenu);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

		else if (MenuChoice == MenuChoice::ChangeSystemThemes)
		{
			ClearScreen();
			ChangeSystemTheme(SystemThemeColor);
			GoToPauseMessage("\n\nPRESS ANY KEY TO GO BACK TO CONTROL MENU...");
		}

 		else if (MenuChoice == MenuChoice::Exit)
		{
			SaveTasksDataToFile(TasksMenu);
			ExitProgram("GOOD BYE , TO-DO LIST :-)", 2, "=", 60, SystemThemeColor.BackgroundColor, SystemThemeColor.ForegroundColor);
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