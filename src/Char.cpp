#include "Char.h"
#include "cppsqlite3.h"
#include "Logger.h"

Char::Char(Uint32 serial, Uint16 type, Uint32 dbId, Client& client)
    :IMoveableObject(serial, type),
    myId(dbId),
    myClient(client)
{
    CppSQLite3DB accDb;
    accDb.open("accounts.db");

    std::ostringstream oss;
    oss << myId;
    std::string query = "SELECT * FROM characters WHERE id = \""+oss.str()+"\";";
    CppSQLite3Query q = accDb.execQuery(query.c_str());

    if (!q.eof()){
        setName(q.fieldValue(2));
        setPosition(Location(q.getIntField(3),q.getIntField(4),0));
    }
    else{
        Logger::getInstance()->log("Error creating Character with ID "+oss.str(), LOGMODE_DB);
    }

    accDb.close();
}

Char::~Char()
{
    //dtor
}

void Char::update(){

}



