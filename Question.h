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
		Question();
		string _question;
		string _answer;
		int id, _likes, who_answered_this_question, who_asked_this_question;
		
	};
}