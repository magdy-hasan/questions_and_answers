#pragma once
#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "system.h"
using namespace std;

namespace QS{

	class helper
	{
	public:
		static int readInt(int min_option, int max_option);
		static int menuOptions(vector<string> &options);
		static void read_informatoin_about_user(ifstream &inputStream,vector<int> &data_to_read);
		static void save_informatoin_about_user(ofstream &outputStream, vector<int> &data_to_save);
		static string read_one_sentence(istream &inputStream);
	};

}