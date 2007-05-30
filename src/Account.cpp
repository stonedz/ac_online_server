#include "Account.h"
#include  "cppsqlite3.h"
#include "Server.h"
#include "Logger.h"
#include "Char.h"

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
