#include "system.h"
#include "helper.h"
#include "Question.h"	
#include "User.h"


namespace QS{

	
	extern  vector<shared_ptr<User>> _users = vector<shared_ptr<User>>();
	extern  vector<shared_ptr<Question>> _questions = vector<shared_ptr<Question>>();


	void system::load_questions(){
		ifstream inputStream("questions_data.txt");
		if (inputStream.fail())
			return;
		int numberOfQuestions;
		inputStream >> numberOfQuestions;
		while (numberOfQuestions--){
			// create the new question
			shared_ptr<Question> new_question(new Question());
			
			// read the question
			new_question->_question = helper::read_one_sentence(inputStream);
			
			// read the answer
			new_question->_answer = helper::read_one_sentence(inputStream);

			// read number of likes, who_answered_this_question, who_asked_this_question
			inputStream >> new_question->_likes >> new_question->who_answered_this_question >> new_question->who_asked_this_question;

			// identify the id of the question
			new_question->id = _questions.size();

			// add the question to the questions list
			_questions.push_back(new_question);

		}
		inputStream.close();
	}


	void system::load_users(){
		ifstream inputStream("users_data.txt");
		if (inputStream.fail())
			return;
		int numberOfUsers;
		inputStream >> numberOfUsers;
		while (numberOfUsers--){
			// create a new user
			shared_ptr<User> new_user(new User());

			// read his data in the form: first_name, last_name, e-mail, password, id
			inputStream >> new_user->user_name >> new_user->first_name >> new_user->last_name >> new_user->e_mail;
			inputStream >> new_user->password >> new_user->id;

			// read the information about user
			new_user->about_user = helper::read_one_sentence(inputStream);

			// read number of answered questions 
			helper::read_informatoin_about_user(inputStream, new_user->answered_questions);

			// read number of unanswered questions 
			helper::read_informatoin_about_user(inputStream, new_user->unanswered_questions);

			// read number of new questions 
			helper::read_informatoin_about_user(inputStream, new_user->new_questions);

			// read number of asked questions 
			helper::read_informatoin_about_user(inputStream, new_user->asked_questions);

			// read number of followers 
			helper::read_informatoin_about_user(inputStream, new_user->followeres);

			// read number of following 
			helper::read_informatoin_about_user(inputStream, new_user->following);

			// get the idea of the new user
			new_user->id = _users.size();
			// push the user into the users list
			_users.push_back(new_user);
		}
		inputStream.close();
	}


	void system::save_questions(){
		ofstream outputStream("questions_data.txt");
		if (outputStream.fail())
			return;
		// print number of questions
		outputStream << _questions.size() << "\n";
		for (auto _one_question : _questions){
			// print question information in the form:
			// question, answer, numberOflikes, who_answered_this_question, who_asked_this_question
			outputStream << _one_question->_question << "\n" << _one_question->_answer << "\n" << _one_question->_likes << "\n";
			outputStream << _one_question->who_answered_this_question << "\n" << _one_question->who_asked_this_question << "\n\n";
		}
		outputStream.close();
	}


	void system::save_users(){
		ofstream outputStream("users_data.txt");
		if (outputStream.fail())
			return;
		outputStream << _users.size() << "\n";
		for (auto _one_user : _users){
			// print user information in the form:
			// user_name, first_name, last_name, e-mail, password, id, about_user
			outputStream << _one_user->user_name << " " << _one_user->first_name << " " << _one_user->last_name << " ";
			outputStream << _one_user->e_mail << " " << _one_user->password << " " << _one_user->id << "\n" << _one_user->about_user << "\n";

			// print number of answered questions
			helper::save_informatoin_about_user(outputStream, _one_user->answered_questions);
			
			// print number of unanswered questions
			helper::save_informatoin_about_user(outputStream, _one_user->unanswered_questions);
			
			// print number of new questions
			helper::save_informatoin_about_user(outputStream, _one_user->new_questions);
			
			// print number of asked questions
			helper::save_informatoin_about_user(outputStream, _one_user->asked_questions);

			// print number of followers
			helper::save_informatoin_about_user(outputStream, _one_user->followeres);

			// print number of following
			helper::save_informatoin_about_user(outputStream, _one_user->following);

			outputStream << "\n\n";

		}
		outputStream.close();
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
		cout << "Please enter information about yourself(end it with separated char #): ";
		new_user->about_user = helper::read_one_sentence(cin);
		
		cout << "Please enter your password: ";
		cin >> new_user->password;
		new_user->id = (int)_users.size();

		cout << "Your account has been successfully created, You id is:" << new_user->id << " ,Please log in now.\n\n\n";
		_users.push_back(new_user);
		return;
	}


}

