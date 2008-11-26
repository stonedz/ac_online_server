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
}

void Cmd_map::execute(void){
	std::string param1 = getParam(1);

    if (param1 == "help" || param1 == "-h" )
        help();
	else if(param1 == "create")
		create(getParam(2,true));
	else
		std::cout << "You passed a wrong parameter to map command, run \"map help\" for further info." << std::endl;
}

void Cmd_map::create(const std::string& filename){
	std::cout<<"Creating map, please wait...";
	ofstream fout;
	fout.open( filename.c_str(), ios::binary);
	Uint16 x = 6000;
	Uint16 y = 4500;
	fout.write((char *) (&x), sizeof(x));
	fout.write((char *) (&y), sizeof(y));
	Uint32 tot = x*y;
	Uint32 count = 0;
	Uint16 terrain_type = 10;
	Sint8 z = 1;
	for (; count < tot; count++){
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
