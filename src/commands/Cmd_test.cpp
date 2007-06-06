#include <string>
#include "Cmd_test.h"
#include "Client.h"

Cmd_test::~Cmd_test()
{
}

void Cmd_test::help(){ // What to print out if a help request in needed.
	std::cout << "Prints a string." << std::endl << "Syntax: test [parameter1]" << std::endl << "-------------" << std::endl;
	std::cout << "Here is a list of available tests with their respective syntax, in alphabetical order" << std::endl << std::endl;
	//Movement validation test
	std::cout << "< test validateMove ax ay az bx by bz > : validates a movement from point P1(ax,ay,az) to P2(bx,by,bz)." << std::endl;
}

void Cmd_test::execute(void){   // Actual implemetation of the command.
    std::string param1 = getParam(1);

    if (param1 == "help" || param1 == "-h" )
        help();
    else if (param1 == "validateMove")
        test_move();
    else
        std::cout << "You passed this string as parameter(s): " << getParam(1,true);
}

void Cmd_test::test_move(){
    Uint32 ax,ay,az,bx,by,bz;
    try{
        // We use boost::lexical_cast to convert from std::String to int, so much better than streams.
        ax = boost::lexical_cast< int >(getParam(2));
        ay = boost::lexical_cast< int >(getParam(3));
        az = boost::lexical_cast< int >(getParam(4));
        bx = boost::lexical_cast< int >(getParam(5));
        by = boost::lexical_cast< int >(getParam(6));
        bz = boost::lexical_cast< int >(getParam(7));
    }
    catch(const boost::bad_lexical_cast &){
        std::cerr << "Problems while parsing the parameters, please enter 6(six) integers as the parameter" << std::endl;
        return; // No reasons to continue.
    }

    Location  a = Location(ax,ay,az);
    Location  b = Location(bx,by,bz);
    if (myServer->getMapManager()->validateMove(a, b))
        std::cout << "This is a valid move for MapManager::validateMove()" <<std::endl;
    else
        std::cout << "This is NOT a valid move for MapManager::validateMove()!!!" << std::endl;

}

