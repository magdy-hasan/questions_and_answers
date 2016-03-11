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
			get_user_id(); // find a user by his user_name/e-mail
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

	void User::view_user(int user_id){ 
		// information about the user
		cout << "\n\n\nFirst name: " << first_name << " Last name: " << last_name << "\n";
		cout << "about him:" << about_user << "\n\n";

		// give option for this user
		vector<string> options = { "view his answered questions","ask him a question",
			"see if you are following/want to follow this user", "back" };

		int choice = helper::menuOptions(options);
		if (choice == 1){
			view_answered_questions();
			view_user(user_id);
		}
		else if (choice == 2){
			// create a new question
			shared_ptr<Question> new_question(new Question(user_id, id));
			_questions.push_back(new_question);

			// push the questoin in the user unanswered questions
			unanswered_questions.push_back(new_question->id);
			// push the question in your asked questions list
			_users[user_id]->asked_questions.push_back(new_question->id);

			view_user(user_id);
		}
		else if (choice == 3){
			add_a_follower(user_id);
			view_user(user_id);
		}
		// option 4 is just return
		return;
	}

	void User::view_asked_questions(){
		if (asked_questions.size() == 0){
			cout << "You havn't asked any questions yet\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions you have asked\n\n\n";
		for (auto _question_id : asked_questions){
			// view the question
			_questions[_question_id]->view_question();

			cout << "\nDo you like this answer ? \n";
			cout << "\t1 - like this answer\n";
			cout << "\t2 - continue\n";
			int choice = helper::readInt(1, 2);
			if (choice == 1)
				_questions[_question_id]->_likes++;
		}
		cout << "\n\nEnd of all new Questions\n\n\n\n";
		return;
	}

	void User::view_new_questions(){
		// if user have np new questions
		if (new_questions.size() == 0){
			cout << "You don't have any new answered questions now\n\n\n\n";
			return;
		}

		cout << "\n\n\nQuestions has been answered recently\n\n\n";
		for (auto _question_id : new_questions){
			auto new_question = _questions[_question_id];
			// view this question
			new_question->view_question();

			cout << "Do you like this answer ? \n";
			cout << "\t1 - like this answer\n";
			cout << "\t2 - continue\n";
			int choice = helper::readInt(1,2);
			if (choice == 1)
				new_question->_likes++;
		}

		// remove all questions from his news feed ( he already seen them )
		new_questions.clear();
		cout << "\n\nEnd of all new Questions\n\n\n\n";
		return;
	}

	void User::view_unanswered_questions(){
		if (unanswered_questions.size() == 0){
			cout << "You don't have any unanswered questions now\n\n\n\n";
			return;
		}

		cout << "\n\n\nQuestions That you hasn't answered yet\n\n\n";
		for (int it = 0; it < (int)unanswered_questions.size(); it++){
			// view question
			_questions[unanswered_questions[it]]->view_question();

			cout << "Do you want to answer this Question now ? \n";
			cout << "\t1 - Yes, answer this question now\n";
			cout << "\t2 - continue\n";
			cout << "Enter your choice: ";
			int choice = helper::readInt(1, 2);
			if (choice == 1){
				// answer this question
				_questions[unanswered_questions[it]]->answer_question();

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
		cout << "\n\nEnd of all new Questions\n\n\n\n";
		return;
	}

	void User::view_answered_questions(){
		if (answered_questions.size() == 0){
			cout << "User don't have any answered questions now\n\n\n\n";
			return;
		}
		cout << "\n\n\nQuestions That've been answered\n\n\n";
		for (auto _question_id : answered_questions)
			 _questions[_question_id]->view_question();

		cout << "\nEnd of all answered Questions\n\n\n\n";
		return;
	}

	void User::get_user_id(){
		string username_emai;
		cout << "\n\n\nEnter user name/email: ";
		cin >> username_emai;
		
		for (auto _user : _users)
			if (_user->user_name == username_emai || _user->e_mail == username_emai){
				// we found a user with such username/e-mail
				_user->view_user(id);
				return;
			}
		// we didn't find that user
		cout << "User doesn't exist.. Taking you back to your menu\n\n\n";
		return;
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
					found_atleast_one = 1;
					view_user_information_again:

					// output user information
					cout << "First name: " << _users[_friend_of_friend]->first_name << " Last name: " <<
						_users[_friend_of_friend]->last_name << " User name: " << _users[_friend_of_friend]->user_name << "\n";

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

	void User::add_a_follower(int user_id){
		if (find(followeres.begin(), followeres.end(), user_id) != followeres.end())
			cout << "You're following this User\n\n\n";
		else {
			vector<string> options = { "Follow this user", "back" };
			int choice = helper::menuOptions(options);
			if (choice == 1){
				cout << "You're following this user now\n\n\n";
				// add this current peroson to the perosn he is following now follwers list
				_users[user_id]->following.push_back(id);
				// add the new followed person to the current user following users
				followeres.push_back(user_id);
			}
		}
		return;
	}

}