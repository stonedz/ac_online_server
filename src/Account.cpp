#include "Account.h"
#include "cppsqlite3.h"
#include "Server.h"
#include "Logger.h"
#include "Char.h"
#include <boost/lexical_cast.hpp>

Account::Account(Server* server,
                Client* client,
                Uint32 id,
                const std::string& username ,
                const std::string& name ,
                const std::string& surname ,
                const std::string& email,
                Uint32 char_id )
    :myServer(server),
    myClient(client),
    myId(id),
    myUsername(username),
    myName(name),
    mySurname(surname),
    myEmail(email),
    myCharID(char_id),
    myChar(NULL)
{
    // Builds the Character associated with the account.
		try{
				
			myChar = new Char(loadGid(myCharID), GO_PLAYER, myCharID, *client); // We delegate database queries to the Char ctor.
				std::cout << "serial "<< myChar->getSerial() <<std::endl;
    		}
    		catch(CppSQLite3Exception& e){
        		std::ostringstream oss;
        		oss << myCharID;
        		Logger::getInstance()->log("Error creating Char with id :"+oss.str(), LOGMODE_DB);
    		}
}

Account::~Account(){
    if(myChar)
        delete myChar;
}

void Account::save(){
    try{
    CppSQLite3DB myAccDb;
    myAccDb.open(DB_ACCOUNTS);
    std::string query = "UPDATE registered_users SET username=\""+myUsername+"\", name=\""+myName+
                        "\", surname=\""+mySurname+"\", email=\""+myEmail+"\" WHERE id="+ boost::lexical_cast< std::string >(myId) +";";

    myAccDb.execDML(query.data());
    myAccDb.close();
    }
    catch(CppSQLite3Exception e){
        std::string error = "Error saving Account with ID "+boost::lexical_cast< std::string >(myId)+
                                ", SQLite says: "+ e.errorMessage();
        Logger::getInstance()->log(error, LOGMODE_DB);
        myServer->getConsole().printMsg(error, CONSOLE_ERROR);
    }
    myChar->save();
}

Uint64 Account::loadGid(Uint32 db_id){
	try{
		CppSQLite3DB accDb;
		accDb.open(DB_ACCOUNTS);

		std::string query = "SELECT gid FROM characters WHERE id = \""+boost::lexical_cast< std::string >(db_id)+"\";";
		CppSQLite3Query q = accDb.execQuery(query.c_str());
		
		if (!q.eof()){
			return q.getIntField(0);
		}
		else{
			Logger::getInstance()->log("Error getting character gid with ID "+boost::lexical_cast< std::string >(db_id) +" no such character in DB!", LOGMODE_DB);
			return 0;
		}
		
		accDb.close();
	}
	catch(CppSQLite3Exception e){
		std::string error = "Error getting character gid with ID "+boost::lexical_cast< std::string >(db_id)+
				", SQLite says: "+ e.errorMessage();
		Logger::getInstance()->log(error, LOGMODE_DB);
		myServer->getConsole().printMsg(error, CONSOLE_ERROR);
		return 0;
	}
}