#include <iostream>
#include "clsMainScreen.h"
#include "clsTasksManagement.h"

using namespace std;

int main()
{		
	clsTasksManagement::LoadAllTaskToMemory();
	clsMainScreen::ShowMainMenu();
}