#include <string>
#include "Cmd_test.h"


Cmd_test::~Cmd_test()
{
}

void Cmd_test::help(){ // What to print out if a help request in needed.
	std::cout << "Prints a string." << std::endl << "Syntax: test [parameter1]" << std::endl;
}

void Cmd_test::execute(void){   // Actual implemetation of the command.
	std::cout << "This is a test command." << std::endl
				<< "The parameters you entered: "  << this->getParam(1,true);
}
