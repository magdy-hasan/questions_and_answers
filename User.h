#pragma once
#include "system.h"
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

namespace QS{
	class Question;

	class User
	{
	public:
		// constructors
		User() {}
		// user information
		int id;
		string user_name, first_name, last_name, e_mail,password,about_user;
		vector<int> answered_questions, unanswered_questions, new_questions, asked_questions;
		vector<int> followeres, following;

		// methods
		void user_Menu();
		void view_new_questions();
		void view_unanswered_questions();
		void view_answered_questions();
		void view_asked_questions();
		void view_followers();
		void view_following();
		void view_user();
		void edit_user_information();
		int get_user_id(string username_email);
		void get_suggested_users();
	};

}