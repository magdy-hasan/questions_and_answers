#include <iostream>
#include "system.h"

using namespace std;


int main(){
	QS::system new_system;
	new_system.load_questions();
	new_system.load_users();
	new_system.mainMenu();
	new_system.save_questions();
	new_system.save_users();
	return 0;
}