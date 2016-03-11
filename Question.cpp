#include "Question.h"



namespace QS{

	Question::Question(int who_ask,int who_answer){
		cout << "Enter You question(end it with a seperated char #): ";
		_question = helper::read_one_sentence(cin);
		who_asked_this_question = who_ask;
		who_answered_this_question = who_answer;
		_answer = "havn't been answered yet #";
		_likes = 0;
		id = _questions.size();
	}

	void Question::view_question(){
		cout << "This question has been asked by: " << _users[who_asked_this_question]->first_name << '\n';
		cout << "This question has been answered by:" << _users[who_answered_this_question]->first_name << "\n\n";
		cout << "\t\tQuestion" << '\n';
		cout << _question << '\n';
		cout << "\t\t Answer" << '\n';
		cout << _answer << "\n";
		cout << "\t  Number Of Likes: " << _likes << "\n\n\n\n";
	}

	void Question::answer_question(){
		cout << "Please Enter your answer here(end it with seperate char #):";
		_answer = helper::read_one_sentence(cin);
		cout << "Your answer has been submitted successfully\n\n\n\n";
	}

}