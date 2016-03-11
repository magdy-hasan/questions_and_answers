#include "helper.h"

namespace QS{

	int helper::menuOptions(vector<string> &options){
		cout << "Choose one of the following option\n";
		for (int option = 0; option < options.size(); option++)
			cout << "\t" << option + 1 << " - " << options[option] << '\n';
		cout << "Enter you choice: ";
		int choice = readInt(1,options.size());
		return choice;
	}

	int helper::readInt(int min_option,int max_option){
		string input;
		cin >> input;
		int choice;
		istringstream iss(input);
		iss >> choice;
		if (iss.fail()){
			cout << "You've entered invalid option... Please try again\n\n";
			return readInt(min_option,max_option);
		}
		if (choice >= min_option && choice <= max_option)
			return choice;
		cout << "You've enterd out of range number... Please try again\n\n";
		return readInt(min_option,max_option);
	}

	void helper::read_informatoin_about_user(ifstream &inputStream, vector<int> &data_to_read){
		int numberOfdata;
		int temp_data;
		inputStream >> numberOfdata;
		while (numberOfdata--){
			inputStream >> temp_data;
			data_to_read.push_back(temp_data);
		}
		return;
	}

	void helper::save_informatoin_about_user(ofstream &outputStream, vector<int> &data_to_save){
		outputStream << data_to_save.size() << "\n";
		for (auto _data : data_to_save){
			outputStream << _data << " ";
		}
		outputStream << "\n";
		return;
	}

	string helper::read_one_sentence(istream &inputStream){
		string sentence = "";
		string temp_word = "";
		while (inputStream >> temp_word){
			sentence = sentence + (sentence.size() > 0 ? " " : "") + temp_word;
			if (temp_word[0] == '#')
				break;
		}
		return sentence;
	}

}
