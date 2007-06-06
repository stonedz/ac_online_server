#include "Cmd_top.h"
#include <vector>
#include <ostream>


Cmd_top::~Cmd_top()
{
    //dtor
}


void Cmd_top::help(){
    std::cout << "Shows real-time server performances and load" << std::endl;
    std::cout << "Run without arguments to get a resume of the performances data, press \\q to quit." << std::endl;
    std::cout << "Run with --stat to obtain detailed statistics on server's performance." << std::endl;
}

void Cmd_top::execute(){
    std::string param1 = getParam(1);

    if (param1 == "help" || param1 == "-h" || param1 == "--hellp" )
        help();
    else if(param1 == "stat" || param1 == "--stat" || param1 == "stats" || param1 == "--stats")
        stats();
    else
        resume();

}

void Cmd_top::resume(){
    Uint16 perfInst, perfShort, perfMed, perfLong;

        perfInst = (myServer->getGamefsm()).getPerformanceInst();
        perfShort = (myServer->getGamefsm()).getPerformanceShort();
        perfMed = (myServer->getGamefsm()).getPerformanceMedium();
        //perfLong = (myServer->getGamefsm()).getPerformanceLong();


        std::cout << colors::green << "Server's performances" << colors::reset << std::endl << "For a full overview the server should be running for 30"
                 << " minutes."<< std::endl;

        std::cout << std::endl << std::setw(15) << "Instant -> " << colors::blue << perfInst << " % " << colors::reset;
        for (Uint16 counter = 0 ; counter < (perfInst/2); counter++){
            if( counter <= 30)
                std::cout << colors::green << "|" << colors::reset;
            else if ( counter <=40)
                std::cout << colors::magenta << "|" << colors::reset;
            else
                std::cout << colors::red << "|" << colors::reset;
        }

        std::cout << std::endl << std::setw(15) <<  "60 seconds -> " << colors::blue << perfShort << " % " << colors::reset;
        for (Uint16 counter = 0 ; counter < (perfShort/2); counter++){
            if( counter <= 30)
                std::cout << colors::green << "|" << colors::reset;
            else if ( counter <=40)
                std::cout << colors::magenta << "|" << colors::reset;
            else
                std::cout << colors::red << "|" << colors::reset;
        }

        std::cout << std::endl << std::setw(15) << "30 minutes -> " << colors::blue << perfMed << " % " << colors::reset;
        for (Uint16 counter = 0 ; counter < (perfMed/2); counter++){
            if( counter <= 30)
                std::cout << colors::green << "|" << colors::reset;
            else if ( counter <=40)
                std::cout << colors::magenta << "|" << colors::reset;
            else
                std::cout << colors::red << "|" << colors::reset;
        }
        std::cout << std::endl;

}

void Cmd_top::stats(){
    Uint16 perfMed, perfLong;

    perfMed = (myServer->getGamefsm()).getPerformanceMedium();
    perfLong = (myServer->getGamefsm()).getPerformanceLong();
    Uint32 uptime = SDL_GetTicks() / 1000;

    Uint16 uptimeH = uptime / 3600;
    Uint16 uptimeM = (uptime - (uptimeH * 3600)) / 60 ;
    Uint16 uptimeS = (uptime - (uptimeH * 3600) ) % 60;


    std::cout << colors::green << "Server's statistics" << colors::reset << std::endl << "For a full overview the server should be running for 30"
                 << " minutes."<< std::endl;
    std::cout << std::left;
    std::cout << std::endl << std::setw(30) << " Performances (30 minutes): " << colors::blue << perfMed << " % " << colors::reset;
    std::cout << std::endl << std::setw(30) << " Performances (2 days)    : " << colors::blue << perfLong << " % " << colors::reset;
    std::cout << std::endl << std::setw(30) << " Uptime                   : " << colors::blue << std::setw(2) << uptimeH << ":"
                << std::setw(2) << uptimeM << ":" << std::setw(2) << uptimeS << colors::reset;
    std::cout << std::endl << std::setw(30) << " Connected clients        : " << colors::blue << myServer->getClients().size() << colors::reset;



    std::cout << std::endl;
}


