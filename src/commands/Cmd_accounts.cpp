#include <string>
#include "Cmd_accounts.h"
#include "sha1.h"
#include "../Logger.h"
#include "../cppsqlite3.h"

Cmd_accounts::Cmd_accounts(std::string& params, Server* server)
    : ICommandServer(params, server)
{
    myAccDb.open(DB_ACCOUNTS);
}

Cmd_accounts::~Cmd_accounts()
{
    myAccDb.close();
}

void Cmd_accounts::help(){
    std::cout << "Account manager" << std::endl << "===============" << std::endl ;
    std::cout << "accounts => Show registered accounts." << std::endl;
    std::cout << "accounts help => Show this help." << std::endl;
    std::cout << "accounts add => Adds a new account to the database." << std::endl;
    std::cout << "accounts attach <account_id> => Creates a new basic character and attaches it to the specified account (for testing purposes)." << std::endl;
}

void Cmd_accounts::execute(){
    std::string param1 = getParam(1);

    if (param1 == "" || param1 == "show")
        showAccounts();
    else if (param1 == "help")
        help();
    else if (param1 == "add")
        addAccount();
    else if (param1 == "attach")
        attachChar();
    else
        std::cout << "You passed a wrong parameter to accounts command, run \"accounts help\" for further info." << std::endl;

}

void Cmd_accounts::showAccounts(Uint32 recordsPerPage){
    try{
        CppSQLite3Query q = myAccDb.execQuery("select * from registered_users order by id;");
        if(q.eof())
            std::cout << "Accounts database is EMPTY, use < accounts add > to add an entry." << std::endl;
        else{
                std::cout << std::setw(3) << "id" << " | ";
                std::cout << std::setw(15) << "username" << " | ";
                std::cout << std::setw(10) << "name" << " | ";
                std::cout << std::setw(10) << "surname" << " | ";
                std::cout << std::setw(7) << "char id" << " | ";
                std::cout << std::setw(20) << "email" << " | " << std::endl;
                std::cout << "----------------------------------------------------------------------------------" << std::endl;
            while (!q.eof()){
                std::cout << std::setw(3) << q.fieldValue(0) << " | ";
                std::cout << std::setw(15) << q.fieldValue(1) << " | ";
                std::cout << std::setw(10) << q.fieldValue(3) << " | ";
                std::cout << std::setw(10) << q.fieldValue(4) << " | ";
                std::cout << std::setw(7) << q.fieldValue(6) << " | ";
                std::cout << std::setw(20) <<q.fieldValue(5) << " | " << std::endl;
                q.nextRow();
            }
        }
    }
    catch (CppSQLite3Exception& e){ // No database!
        std::cout << "No accounts database found!, creating a new one...";
        try{
            Sint32 nRows;
            nRows = myAccDb.execDML("CREATE TABLE IF NOT EXISTS registered_users ( id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, index_hash TEXT, surname TEXT, name TEXT, email TEXT, pc_id INTEGER DEFAULT 0);");
            nRows = myAccDb.execDML("CREATE UNIQUE INDEX IF NOT EXISTS sha1_index ON registered_users (index_hash);");
            std::cout << "OK" << std::endl;
        }
        catch (CppSQLite3Exception& e){ // Failed database creation
            std::cout << "FAILED! Seems we've some problems creating a new database." << std::endl;
        }
    }


}

void Cmd_accounts::addAccount(const std::string& username,
                                const std::string& password,
                                const std::string& name,
                                const std::string& surname,
                                const std::string& email)
{
    std::string username_, password_, name_, surname_, email_;
    SHA1 pwdSHA1;
	Uint32 shaData[5];

	Logger* logger = Logger::getInstance();

    if (username == "" || password  == "" || name == "" || surname == "" || email == ""){
        std::cout << "\nACCOUNTS CREATOR\n";
        std::cout << "================\n";
        std::cout << "Use this program to create simple user data into sqlite3 db.\n";
        std::cout << "User name : ";
        std::getline(std::cin, username_);
        std::cout << "Password: ";
        std::getline(std::cin, password_);
        std::cout << "Real name: ";
        std::getline(std::cin, name_);
        std::cout << "Real surname: ";
        std::getline(std::cin, surname_);
        std::cout << "Email address: ";
        std::getline(std::cin, email_);
    }
    else{
        username_ = username;
        password_= password;
        name_ = name;
        surname_ = surname;
        email_ = email;
    }

    std::string temp = username_+password_;
	pwdSHA1.Reset();
	for (unsigned int i = 0; i < temp.size(); i++){
		pwdSHA1.Input(temp[i]);
	}

	if (!pwdSHA1.Result(shaData)){
		std::cerr<<"Sha could not compute message digest for login informations." << std::endl;
		logger->log("Error during SHA1 computation in addAccount() method.", LOGMODE_ERROR);
	}
	else{ // We have a valid SHA1 hash.
        char hash[40];
        for (int i = 1; i < 6; i++){ // Transforms the hash in a readable format.
            sprintf(hash + (8*(i-1)), "%08x", shaData[i-1]);
        }

        Sint32 nRows;
        #ifdef TESTPHASE
        nRows = myAccDb.execDML("CREATE TABLE IF NOT EXISTS registered_users ( id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT UNIQUE, index_hash TEXT, surname TEXT, name TEXT, email TEXT, pc_id INTEGER DEFAULT 0);");
        nRows = myAccDb.execDML("CREATE UNIQUE INDEX IF NOT EXISTS sha1_index ON registered_users (index_hash);");
        #endif
        std::string query = "insert into registered_users(username, index_hash, surname, name, email) values ( \""+username_+"\", \""+hash+"\", \""+name_+"\", \""+surname_+"\", \""+email_+"\");";
        nRows = myAccDb.execDML(query.data());

        std::cout << "OK account for username \"" << username_ << "\" created." << std::endl;
	}

}

void Cmd_accounts::attachChar(){
    std::string charname, xPos, yPos, zPos, accNumber;

    std::cout << "Account ID :";
    std::getline(std::cin, accNumber);
    std::cout << "Initial X position :";
    std::getline(std::cin, xPos);   // Not really good...
    std::cout << "Initial Y position :";
    std::getline(std::cin, yPos);
    std::cout << "Initial Z position :";
    std::getline(std::cin, zPos);              //This neither
    std::cout << "Character name :";
    std::getline(std::cin, charname);

    Sint32 nRows;
    #ifdef TESTPHASE
    nRows = myAccDb.execDML("CREATE TABLE IF NOT EXISTS characters (id INTEGER PRIMARY KEY AUTOINCREMENT, account_id INTEGER, name TEXT UNIQUE, x_position INTEGER, y_position INTEGER, z_position INTEGER);");
    #endif
    std::string query = "insert into characters(account_id, name, x_position, y_position, z_position) VALUES ( \""+accNumber+"\", \""+charname+"\", \""+xPos+"\", \""+yPos+"\", \""+zPos+"\");";
    nRows = myAccDb.execDML(query.data());

    if (nRows){
        query = "select id from characters WHERE name = \""+charname+"\";";
        CppSQLite3Query q = myAccDb.execQuery(query.data());
        if(!q.eof()){
            nRows = 0;
            std::ostringstream oss;
            oss << q.fieldValue(0);
            query = "UPDATE registered_users SET pc_id = \""+oss.str()+"\" WHERE id = \""+accNumber+"\";";
            nRows = myAccDb.execDML(query.data());
            if (nRows == 0){ //no tables updated, something went wrong, delete the char and print a warning.
                query = "DELETE FROM characters WHERE id = \""+oss.str()+"\";";
                nRows = myAccDb.execDML(query.data());
                Logger::getInstance()->log("Failed to insert a new character due to an invalid account id.", LOGMODE_DB);
            }
        }

    }


}
