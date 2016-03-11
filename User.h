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
		vector<int> answered_questions; // this's the quesions i have answered
		vector<int> unanswered_questions; // this's the questions i havn't answered yet
		vector<int> new_questions; // this's the questions that my friends have answered and i havn't seen it yet
		vector<int> asked_questions; // this's the questoins i have asked 
		vector<int> followeres; // this's the peoble that are following me
		vector<int> following; // this's the peoblem iam following

		// methods
		void user_Menu();
		void view_new_questions();
		void view_unanswered_questions();
		void view_answered_questions();
		void view_asked_questions();
		void view_followers();
		void view_following();
		void add_a_follower(int user_id);
		void view_user(int user_id);
		void edit_user_information();
		void get_user_id();
		void get_suggested_users();
	};

}