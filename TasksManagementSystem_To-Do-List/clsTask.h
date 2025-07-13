#pragma once
#include <iostream>
#include "clsDate.h"
#include <string>
using namespace std;

class clsTask
{
public:
	struct stTaskInfo
	{
		int Id;
		string Description;
		clsDate StartDate;
		clsDate EndDate;
		bool Completed = false;
		bool MarkedDeleted = false;		

		bool operator==(stTaskInfo& Other)
		{
			return (Id == Other.Id && Description == Other.Description);
		}
		bool operator!=(stTaskInfo& Other)
		{
			return (Id != Other.Id && Description != Other.Description);
		}
	};
};