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
        		Uint32 tmpSerial;
       			myServer->getNextGoSerial(tmpSerial);
				std::cout << "serial "<< tmpSerial <<std::endl;
        		myChar = new Char(tmpSerial, GO_PLAYER, myCharID, *client); // We delegate database queries to the Char ctor.
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
