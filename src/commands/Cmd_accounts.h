#ifndef CMD_ACCOUNTS_H
#define CMD_ACCOUNTS_H

#include "ICommandServer.h"
#include "../cppsqlite3.h"

/**
 * The account manager. For more help please take a look at developers documentation.
 */
class Cmd_accounts : public ICommandServer
{
public:
    Cmd_accounts(std::string& params, Server* server);

    virtual ~Cmd_accounts();

    void help();

    void execute();

private:

    /**
     * Shows the registered accounts, if recordsPerPage is specified it will
     * divide the results in pages with N recrods in it to ease record lecture.
     *
     * @author stonedz
     * @since pre-alpha
     * @param recordsPerPage How many records we want on a page?
     * @todo recordsPerPage mechanism to be implemented!
     */
    void showAccounts(Uint32 recordsPerPage = 0);

    /**
     * Adds a new account to the database. If one or more of the parameters are omitted
     * you will be asked to filla form with the informations needed.
     *
     * Code based on the account-creator.
     *
     * @author stonedz
     * @since pre-alpha
     * @param username Account's username.
     * @param password Account's password.
     * @param name Real name.
     * @param surname Real surname.
     * @param email Valid email address.
     * @todo Find a way to separate SQL code form C++.
     */
    void addAccount(const std::string& username = "",
                    const std::string& password = "",
                    const std::string& name = "",
                    const std::string& surname = "",
                    const std::string& email = "");

    /**
     * Attaches a new basic character to an existing account.
     *
     * @author stonedz
     * @since pre-alpha
     * @todo No erro handling, this may cause serious damage to the database...
     */
    void attachChar();

    CppSQLite3DB myAccDb;  /**< Local DB reference to avoid multiple db accesses. */
};



#endif // CMD_ACCOUNTS_H
