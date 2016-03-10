#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "system.h"
using namespace std;

namespace QS{

	class helper
	{
	public:
		static int readInt(int min_option, int max_option);
		static int menuOptions(vector<string> &options);
	};

}