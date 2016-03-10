#include "system.h"
#include "helper.h"
#include "Question.h"	
#include "User.h"


namespace QS{

	
	extern  vector<shared_ptr<User>> _users = vector<shared_ptr<User>>();
	extern  vector<shared_ptr<Question>> _questions = vector<shared_ptr<Question>>();


	void system::load_questions(){
		ifstream inputStram("questions_data.txt");
		if (inputStram.fail())
			return;
		int numberOfQuestions;
		inputStram >> numberOfQuestions;
		while (numberOfQuestions--){
			// create the new question
			shared_ptr<Question> new_question(new Question());
			new_question->_question = "";
			new_question->_answer = "";
			string _temp_word;
			// read the question

			

			while (inputStram >> _temp_word ){
				new_question->_question = new_question->_question + (new_question->_question.size() > 0 ?  " ":"" ) + _temp_word;
				if (_temp_word[0] == '#')
					break;
			}

			// read the answer
			while (inputStram >> _temp_word){
				new_question->_answer = new_question->_answer + (new_question->_answer.size() > 0 ?  " ":"" )+ _temp_word;
				if (_temp_word[0] == '#')
					break;

			}

			// read number of likes, who_answered_this_question, who_asked_this_question
			inputStram >> new_question->_likes >> new_question->who_answered_this_question >> new_question->who_asked_this_question;
			// identify the id of the question
			new_question->id = _questions.size();
			// add the question to the questions list
			_questions.push_back(new_question);

		}
		inputStram.close();
	}

	void system::load_users(){
		ifstream inputStram("users_data.txt");
		if (inputStram.fail())
			return;
		int numberOfUsers, numberOfAnsweredQuestions, numberOfUnAnsweredQuestions, numberOfnewQuestions, numberOfAskedQuestions,
			question_id, numberOfFollowers, numberOfFollowing, user_id;
		inputStram >> numberOfUsers;
		while (numberOfUsers--){
			shared_ptr<User> new_user(new User());
			inputStram >> new_user->user_name>> new_user->first_name >> new_user->last_name >> new_user->e_mail >> new_user->password >> new_user->id;
			new_user->about_user = "";
			string _temp_word;
			// read the information about user
			while (inputStram >> _temp_word){
				new_user->about_user = new_user->about_user + (new_user->about_user.size() > 0 ?  " ":"") + _temp_word;
				if (_temp_word[0] == '#')
					break;
			}
			// read number of answered questions 
			inputStram >> numberOfAnsweredQuestions;
			while (numberOfAnsweredQuestions--){
				inputStram >> question_id;
				new_user->answered_questions.push_back(question_id);
			}
			// read number of unanswered questions 
			inputStram >> numberOfUnAnsweredQuestions;
			while (numberOfUnAnsweredQuestions--){
				inputStram >> question_id;
				new_user->unanswered_questions.push_back(question_id);
			}
			// read number of new questions 
			inputStram >> numberOfnewQuestions;
			while (numberOfnewQuestions--){
				inputStram >> question_id;
				new_user->new_questions.push_back(question_id);
			}
			// read number of asked questions 
			inputStram >> numberOfAskedQuestions;
			while (numberOfAskedQuestions--){
				inputStram >> question_id;
				new_user->asked_questions.push_back(question_id);
			}
			// read number of followers 
			inputStram >> numberOfFollowers;
			while (numberOfFollowers--){
				inputStram >> user_id;
				new_user->followeres.push_back(user_id);
			}
			// read number of following 
			inputStram >> numberOfFollowing;
			while (numberOfFollowing--){
				inputStram >> user_id;
				new_user->following.push_back(user_id);
			}
			// identify the number of the user
			new_user->id = _users.size();
			// push the user into the users list
			_users.push_back(new_user);
		}
		inputStram.close();
	}


	void system::save_questions(){
		ofstream outputStram("questions_data.txt");
		if (outputStram.fail())
			return;
		outputStram << _questions.size() << "\n";
		for (auto _one_question : _questions){
			outputStram << _one_question->_question << "\n" << _one_question->_answer << "\n" << _one_question->_likes << "\n"
				<< _one_question->who_answered_this_question << "\n" << _one_question->who_asked_this_question << "\n\n";

		}
		outputStram.close();
	}

	void system::save_users(){
		ofstream outputStram("users_data.txt");
		if (outputStram.fail())
			return;
		outputStram << _users.size() << "\n";
		for (auto _one_user : _users){
			outputStram << _one_user->user_name << " " << _one_user->first_name << " " << _one_user->last_name << " "
				<< _one_user->e_mail << " " << _one_user->password << " " << _one_user->id << "\n" << _one_user->about_user << "\n";
			// print number of answered questions
			outputStram << _one_user->answered_questions.size() << "\n";
			for (auto _one_user_question : _one_user->answered_questions)
				outputStram << _one_user_question << " ";
			outputStram << "\n";
			// print number of unanswered questions
			outputStram << _one_user->unanswered_questions.size() << "\n";
			for (auto _one_user_question : _one_user->unanswered_questions)
				outputStram << _one_user_question << " ";
			outputStram << "\n";
			// print number of new questions
			outputStram << _one_user->new_questions.size() << "\n";
			for (auto _one_user_question : _one_user->new_questions)
				outputStram << _one_user_question << " ";
			outputStram << "\n";
			// print number of asked questions
			outputStram << _one_user->asked_questions.size() << "\n";
			for (auto _one_user_question : _one_user->asked_questions)
				outputStram << _one_user_question << " ";
			// print number of followers
			outputStram << _one_user->followeres.size() << "\n";
			for (auto _one_user_id : _one_user->followeres)
				outputStram << _one_user_id << " ";
			outputStram << "\n";
			// print number of following
			outputStram << _one_user->following.size() << "\n";
			for (auto _one_user_id : _one_user->following)
				outputStram << _one_user_id << " ";
			outputStram << "\n";
			outputStram << "\n\n";

		}
		outputStram.close();
	}


	void system::mainMenu(){
		cout << _users.size() << " " << _questions.size() << endl;
		for (auto _user : _users)
			cout << _user->id << " " << _user->user_name << " " << _user->password << endl;
		cout << "Welcome to Question and Answers system\n\n";
		vector<string> options = { "Login", "Sign up", "Shutdown system" };
		int choice = helper::menuOptions(options);
		if (choice == 1){
			login();
			mainMenu();
		}
		else if (choice == 2){
			Sign_up();
			mainMenu();
		}
		else{
			cout << "Saving data .... \n\n\nGood Bye";
		}
		return;
	}

	void system::login(){
		int _id;
		string _pass;
		cout << "\n\n\nPlease Enter your id: ";
		_id = helper::readInt(0,(1<<30));
		cout << "Enter your password: ";
		cin >> _pass;
		if (_users[_id]->password == _pass){
			cout << "\n\n\n";
			_users[_id]->user_Menu();
		}
		else{
			cout << "Invalid id/password, Please try again \n\n\n";
			login();
		}
		return;
	}
		
	void system::Sign_up(){
		shared_ptr<User> new_user(new User());
		cout << "\n\n\nPlease enter your user name: ";
		cin >> new_user->user_name;
		cout << "Please enter your first name: ";
		cin >> new_user->first_name;
		cout << "Please enter your last name: ";
		cin >> new_user->last_name;
		cout << "Please enter your e-mail: ";
		cin >> new_user->e_mail;

		for (auto _user : _users)
			if (_user->user_name == new_user->user_name || _user->e_mail == new_user->e_mail){
				cout << "This user name/e-mail is unavailable, Please try again with another user name/email \n\n\n\n";
				Sign_up();
				return;
			}

		// add information about user
		new_user->about_user = "";
		string _about_user = "";
		cout << "Please enter information about yourself(end it with separated char #): ";
		while (cin >> _about_user){
			new_user->about_user = new_user->about_user + " " + _about_user;
			if (_about_user[0] == '#')
				break;
		}

		cout << "Please enter your password: ";
		cin >> new_user->password;
		new_user->id = (int)_users.size();

		cout << "Your account has been successfully created, You id is:" << new_user->id << " ,Please log in now.\n\n\n";
		_users.push_back(new_user);
		return;
	}



}

