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
}
