#include "IDServer.h"
#include <iostream>

#include "cppsqlite3.h"
#include <boost/lexical_cast.hpp>


IDServer::IDServer(Server* server)
	:myObjNum(0),
	myServer(server)
{
	try{
		CppSQLite3DB myServerDb;
		myServerDb.open(DB_SERVER);
		std::string query = "SELECT time_gid FROM gids ;";
		CppSQLite3Query q = myServerDb.execQuery(query.c_str());
		if (!q.eof()){
			myTime = q.getIntField(0) + 1; // Skip to the next time slice.
		}
		myServerDb.close();
	}
	catch(CppSQLite3Exception e){
		std::string error = "Error reading time_gid time slice , SQLite says: ";// e.errorMessage();
		Logger::getInstance()->log(error, LOGMODE_DB);
		myServer->getConsole().printMsg(error, CONSOLE_ERROR);
	}
}

IDServer::~IDServer(){
	
}

Uint64 IDServer::getNewId(const Uint8& type){
	Uint64 result;
	Uint64 tmp = myTime;
	Uint64 tmp_type = type<<24;
	Uint64 tmp_obj = myObjNum;
	
	result = ((tmp<<32)^tmp_type)^tmp_obj;
		
	std::cout << tmp_type << std::endl;
	std::cout << result << std::endl;
	std::cout << myTime <<std::endl;
	return tmp;
}

Uint32 IDServer::updateTime(){
	myTime++;
	return myTime;
}