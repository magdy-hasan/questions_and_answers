#pragma once
#include "system.h"
#include <string>
#include <vector>
#include "User.h"
using namespace std;

namespace QS{

	class Question
	{
	public:
		Question() {} // empty constructor
		Question(int who_ask,int who_ans); // constructor will fill all data for a new question
		string _question;
		string _answer;
		int id, _likes, who_answered_this_question, who_asked_this_question;
		
		void create_new_question();
		void answer_question();
		void view_question();
	};
}