//
// C++ Implementation: Cmd_map
//
// Description: 
//
//
// Author: Paolo Fagni, Alessandro Sperindé, Davide Bardone <paolo.fagni@gmail.com>, (C) 2008
//
// Copyright: See COPYING file that comes with this distribution
//
//
#include <string>
#include "Cmd_map.h"
#include "Client.h"

Cmd_map::~Cmd_map()
{
}

void Cmd_map::help(){
	std::cout << "Test map management" << std::endl << "Syntax: map [parameter1]" << std::endl << "-------------" << std::endl;
	std::cout << "map get <X> <Y> : Gets the information for the given coordinates." <<std::endl;
}

void Cmd_map::execute(void){
	std::string param1 = getParam(1);

    if (param1 == "help" || param1 == "-h" )
        help();
	else if(param1 == "create")
		create(getParam(2,true));
	else if(param1 == "get")
		getInfo(getParam(2,false), getParam(3,false));
	else
		std::cout << "You passed a wrong parameter to map command, run \"map help\" for further info." << std::endl;
}

void Cmd_map::create(const std::string& filename){
	std::cout<<"Creating map, please wait...";
	ofstream fout;
	fout.open( filename.c_str(), ios::binary);
	Uint16 x = 4000;
	Uint16 y = 4000;
	fout.write((char *) (&x), sizeof(x));
	fout.write((char *) (&y), sizeof(y));
	Uint32 tot = x*y;
	Uint32 count = 0;
	Uint8 terrain_type = 0;
	Uint8 z = 1;
	for (; count < tot; count++){
		terrain_type =count;
		fout.write ((char *) (&z), sizeof(z));
		fout.write ((char *) (&terrain_type), sizeof(terrain_type));
	}
	fout.close();
	std::cout<<"DONE!"<<std::endl;
	
	ifstream fin;
	fin.open ( filename.c_str(), ios::binary);
	Uint16 xx, yy;
	fin.read((char *) (&xx), sizeof(xx));
	fin.read((char *) (&yy), sizeof(yy));
	
	
	std::cout << "x: "<< xx << std::endl << "y: "<< yy<<std::endl;
	
	fin.close();
}

void Cmd_map::getInfo(const std::string& x, const std::string& y){
	coord tmp;
	tmp = myServer->getMapManager()->getInfo(boost::lexical_cast< Uint16 >(x), boost::lexical_cast< Uint16 >(y));
	std::cout<< "------------" << std::endl;
	std::cout<< "z: " << (int)(tmp.z)<< std::endl;
	std::cout<< "type: " << (int)(tmp.t_type) << std::endl;
	std::cout<< "------------" << std::endl;
}

