#include "User.h"
#include "Question.h"


namespace QS{


	void User::user_Menu(){
		vector<string> options = { "Open new Questions answered by your friends", "view your unanswered questions",
			"view your answered questions", "view your asked questions", "view User by his email/user name",
			"view users that are following you","view users that you're following","edit your information","view suggested users","Logout" };
		int choice = helper::menuOptions(options);
		if (choice == 1){
			view_new_questions();
		}
		else if (choice == 2){
			view_unanswered_questions();
		}
		else if (choice == 3){
			view_answered_questions();
		}
		else if (choice == 4){
			view_asked_questions();
		}
		else if (choice == 5){
			view_user();
		}
		else if (choice == 6){
			view_followers();
		}
		else if (choice == 7){
			view_following();
		}
		else if (choice == 8){
			edit_user_information();
		}
		else if (choice == 9){
			get_suggested_users();
		}
		else if (choice == 10){
			// go back to main menu
			return;
		}
		user_Menu();
		return;
	}

	
	void User::view_user(){ 
		string username_emai;
		cout << "\n\n\nEnter user name/email: ";
		cin >> username_emai;
		int user_id = get_user_id(username_emai);
		if (user_id == -1){
			cout << "User doesn't exist.. Taking you back to your menu\n\n\n";
			return;
		}
		view_user_information_again:
		cout << "\n\n\nFirst name: " << _users[user_id]->first_name << " Last name: " << _users[user_id]->last_name << "\n\n";
		cout << "about him:" << _users[user_id]->about_user << "\n\n";
		vector<string> options = { "view his answered questions","ask him a question",
			"see if you are following/want to follow this user", "back" };
		int choice = helper::menuOptions(options);
		if (choice == 1){
			_users[user_id]->view_answered_questions();
			goto view_user_information_again;
		}
		else if (choice == 2){
			// create a new question
			shared_ptr<Question> new_question(new Question());
			new_question->id = _questions.size();
			new_question->who_asked_this_question = id;
			new_question->who_answered_this_question = user_id;
			new_question->_likes = 0;
			new_question->_question = "";
			new_question->_answer = "havn't been answered yet #";
			// take the question form input
			string question_word;
			cout << "Enter you question(end it with seperated char #): ";
			while (cin >> question_word){
				new_question->_question = new_question->_question + " " + question_word;
				if (question_word[0] == '#')
					break;
			}
			// add the question to the questions list
			_questions.push_back(new_question);
			// push the questoin in the user unanswered questions
			_users[user_id]->unanswered_questions.push_back(new_question->id);
			// push the question in your asked questions list
			asked_questions.push_back(new_question->id);

			goto view_user_information_again;
		}
		else if (choice == 3){
			if (find(following.begin(), following.end(), user_id) != following.end())
				cout << "You're following this User\n\n\n";
			else {
				options = { "Follow this user","back" };
				choice = helper::menuOptions(options);
				if (choice == 1){
					cout << "You're following this user now\n\n\n";
					// add this current peroson to the perosn he is following now follwers list
					_users[user_id]->followeres.push_back(id);
					// add the new followed person to the current user following users
					following.push_back(user_id);
				}
			}
		}
		return;
	}

	void User::view_asked_questions(){
		if (asked_questions.size() == 0){
			cout << "You havn't asked any questions yet\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions you have asked\n\n\n";
		for (auto _question_id : asked_questions){
			auto new_question = _questions[_question_id];
			cout << "Question has been asked by: " <<
				_users[new_question->who_asked_this_question]->first_name << " "
				<< _users[new_question->who_asked_this_question]->last_name
				<< "\nQuestion has been answered by: " <<
				_users[new_question->who_answered_this_question]->first_name << " "
				<< _users[new_question->who_answered_this_question]->last_name
				<< "\nQuestion:\n" << new_question->_question << "\nAnswer:\n" << new_question->_answer << "\nnumber Of likes:"
				<< new_question->_likes << "\n";

			cout << "Do you like this answer ? \n";
			cout << "\t1 - like this answer\n";
			cout << "\t2 - continue\n";
			int choice = helper::readInt(1, 2);
			if (choice == 1)
				new_question->_likes++;
		}
		cout << "End of all new Questions\n\n\n\n";
		return;
	}

	void User::view_new_questions(){
		if (new_questions.size() == 0){
			cout << "You don't have any new answered questions now\n\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions has been answered recently\n\n\n";
		for (auto _question_id : new_questions){
			auto new_question = _questions[_question_id];
			cout << "Question has been asked by: " <<
			_users[new_question->who_asked_this_question]->first_name << " " 
			<< _users[new_question->who_asked_this_question]->last_name
			<< "\nQuestion has been answered by: " <<
			_users[new_question->who_answered_this_question]->first_name << " " 
			<< _users[new_question->who_answered_this_question]->last_name
			<< "\nQuestion:\n" << new_question->_question << "\nAnswer:\n" << new_question->_answer << "\nnumber Of likes:"
			<< new_question->_likes << "\n";

			cout << "Do you like this answer ? \n";
			cout << "\t1 - like this answer\n";
			cout << "\t2 - continue\n";
			int choice = helper::readInt(1,2);
			if (choice == 1)
				new_question->_likes++;
		}
		cout << "End of all new Questions\n\n\n\n";
		return;
	}

	void User::view_unanswered_questions(){
		if (unanswered_questions.size() == 0){
			cout << "You don't have any unanswered questions now\n\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions That you hasn't answered yet\n\n\n";
		
		for (int it = 0; it < (int)unanswered_questions.size(); it++){
			auto new_question = _questions[unanswered_questions[it]];
			cout << "Question has been asked by: " <<
				_users[new_question->who_asked_this_question]->first_name << " "
				<< _users[new_question->who_asked_this_question]->last_name
				<< "\nQuestion:\n" << new_question->_question << "\n\n";

			cout << "Do you want to answer this Question now ? \n";
			cout << "\t1 - Yes, answer this question now\n";
			cout << "\t2 - continue\n";
			cout << "Enter your choice: ";
			int choice = helper::readInt(1, 2);
			if (choice == 1){
				cout << "Please Enter your answer here(end it with seperate char #):";
				string _ans;
				new_question->_answer = "";
				while (cin >> _ans)
				{
					new_question->_answer = new_question->_answer + (new_question->_answer.size() > 0 ? " " : "") + _ans;
					if (_ans[0] == '#')
						break;
				}
				cout << "Your answer has been submitted successfully\n\n\n\n";

				// put this question in his answered questions list
				answered_questions.push_back(unanswered_questions[it]);
				// put this questoin for all his followers news feed
				for (auto _follower : followeres)
					_users[_follower]->new_questions.push_back(unanswered_questions[it]);
				// remove this question from his unanswered question list
				unanswered_questions.erase(unanswered_questions.begin() + it);
				it--;
			}
		}
		cout << "End of all new Questions\n\n\n\n";
		return;
	}

	void User::view_answered_questions(){
		if (answered_questions.size() == 0){
			cout << "User have any answered questions now\n\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions That've been answered\n\n\n";
		for (auto _question_id : answered_questions){
			auto new_question = _questions[_question_id];
			cout << "Question has been asked by: " <<
				_users[new_question->who_asked_this_question]->first_name << " "
				<< _users[new_question->who_asked_this_question]->last_name
				<< "\nQuestion has been answered by: " <<
				_users[new_question->who_answered_this_question]->first_name << " "
				<< _users[new_question->who_answered_this_question]->last_name
				<< "\nQuestion: " << new_question->_question << "\nAnswer:\n" << new_question->_answer << "\nnumber Of likes:"
				<< new_question->_likes << "\n\n";
		}
		cout << "End of all answered Questions\n\n\n\n";
		return;
	}

	int User::get_user_id(string username_email){
		// return -1 if user doesn't exist
		// else return user id
		for (auto _user : _users)
			if (_user->user_name == username_email || _user->e_mail == username_email)
				return _user->id;
		return -1;
	}

	void User::view_followers(){
		if (followeres.size() == 0){
			cout << "No user are following you now\n\n\n";
			return;
		}
		cout << "Users that Are following you\n\n";
		for (int it = 0; it < (int)followeres.size(); it++)
			cout << it + 1 << " - " << _users[followeres[it]]->first_name << " " << _users[followeres[it]]->last_name << "\n";
		cout << "End of the list\n\n\n";
		return;
	}

	void User::view_following(){
		if (following.size() == 0){
			cout << "You're not following any user now\n\n\n";
			return;
		}
		cout << "Users you are following\n\n";
		for (int it = 0; it < (int)following.size(); it++)
			cout << it + 1 << " - " << _users[following[it]]->first_name << " " << _users[following[it]]->last_name << "\n";
		cout << "End of the list\n\n\n";
		return;
	}

	void User::edit_user_information(){
		vector<string> options = { "change first name", "change last name", "change e-mail", "change password",
			"change information about you","back" };
		int choice = helper::menuOptions(options);
		if (choice == 1){
			cout << "Enter Your first name: ";
			cin >> first_name;
		}
		else if (choice == 2){
			cout << "Enter Your last name: ";
			cin >> first_name;
		}
		else if (choice == 3){
			cout << "Enter Your e-mail: ";
			cin >> first_name;
		}
		else if (choice == 4){
			cout << "Enter Your new password: ";
			cin >> first_name;
		}
		else if (choice == 5){
			cout << "Enter Your new information(end it with seperated char #): ";
			about_user = "";
			string _info = "";
			while (cin >> _info)
			{
				if (_info[0] == '#')
					break;
				about_user = about_user + " " + _info;
			}
		}
		else if (choice == 6){
			return;
		}
		cout << "Your information has been changed successfully\n\n\n";
		edit_user_information();
		return;
	}

	void User::get_suggested_users(){
		bool found_atleast_one = 0;
		for (auto _friend:following)
			for (auto _friend_of_friend : _users[_friend]->following)
				if (find(followeres.begin(), followeres.end(), _friend_of_friend) == followeres.end()){
					// now we have found a sugeestion
					found_atleast_one = 1;
					// go back to here if he watchecd the user answered questions
					view_user_information_again:
					// output user information
					cout << "First name: " << _users[_friend_of_friend]->first_name << " Last name: " <<
						_users[_friend_of_friend]->last_name << " User name: " << _users[_friend_of_friend]->user_name << "\n";
					// give option to view his answers or follow him
					vector<string> options = { "view his answered questions", "start following this user", "continue" };
					int choice = helper::menuOptions(options);
					if (choice == 1){
						_users[_friend_of_friend]->view_answered_questions();
						goto view_user_information_again;
					}
					else if (choice == 2){
						cout << "You're following this user now\n\n\n";
						// add this current peroson to the perosn he is following now follwers list
						_users[_friend_of_friend]->followeres.push_back(id);
						// add the new followed person to the current user following users
						following.push_back(_friend_of_friend);
					}
				}
		if (found_atleast_one == false) 
			cout << "No suggested users are avaiable at this time\n\n\n";
		cout << "\n\n\n";
		return;
	}

}