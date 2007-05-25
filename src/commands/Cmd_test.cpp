#include <string>
#include "Cmd_test.h"


Cmd_test::~Cmd_test()
{
}

void Cmd_test::help(){ // What to print out if a help request in needed.
	std::cout << "Prints a string." << std::endl << "Syntax: test [parameter1]" << std::endl;
}

void Cmd_test::execute(void){   // Actual implemetation of the command.
	std::cout << "This is a test command." << std::endl ;
	std::cout << "It could be used to test some server's internals." <<std::endl;
    std::string param1 = getParam(1);

    if (param1 == "help" || param1 == "-h" )
        help();
    else if (param1 == "movement")
        test_move();
    else
        std::cout << "You passed this string as parameter(s): " << getParam(1,true);


    //<< "The parameters you entered: "  << this->getParam(1,true);
}

void Cmd_test::test_move(){
    Location * a = new Location(1,1,1);
    Location * b = new Location(2,1,1);
    if (myServer->getMapManager()->validateMove(a, b))
        std::cout << "BVENEEE" <<std::endl;
    else
        std::cout << "MALESSS" << std::endl;

    delete a;
    delete b;
}
