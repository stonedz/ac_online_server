#include "ICommand.h"

ICommand::ICommand(std::string &params)
	:myParameters(params)
{
}

ICommand::~ICommand()
{
}

std::string ICommand::getParam(Uint16 param, bool toTheEnd){
	std::string tmpString;
	std::string::size_type spos, epos;
	
	tmpString = this->myParameters;
	
	// Finds the starting position.
	for(int counter = 0; counter < param; counter++){ // that's bad :(
		spos = tmpString.find(" ");
		if(spos != std::string::npos) // ok found
			tmpString.assign(tmpString, (spos+1), tmpString.size());
	}
	
	if(spos != std::string::npos){
		if(!toTheEnd){ // Take only this parameter, ignore what follows.
			epos = tmpString.find(" "); // Finds the ending position.
			tmpString.assign(tmpString, 0, epos); // Fills the result string.
		}
	}
	else
		tmpString = "";
	
	
	return tmpString;

}
