#pragma once
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <fstream>
#include "helper.h"
using namespace std;

namespace QS{
	class Question;
	class User;

	class system
	{
	public:
		
		void mainMenu();
		void login();
		void Sign_up();
		void load_questions();
		void load_users();
		void save_questions();
		void save_users();
	};
	extern  vector<shared_ptr<User>> _users;
	extern  vector<shared_ptr<Question>> _questions;
}

