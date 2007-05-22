#include <string>
#include "Cmd_chat.h"

Cmd_chat::~Cmd_chat()
{
    //dtor
}

void Cmd_chat::help(){
    std::cout << "Transforms the console in a basic chat application to send MSG_CHAT messages to attached clients" << std::endl;
}

void Cmd_chat::execute(){
    bool exit = false; // When to exit from the chat
    std::string msg;

    myServer->setChatMode();
    std::cout << "Chat mode activated. To exit please enter \"\\quit\" or \"\\q\"" << std::endl;

    while(!exit){
        std::getline(std::cin, msg);
        if(msg == "\\quit" || msg == "\\q")
            break;
        myServer->generalChatMsg(0, msg);

    }

    myServer->setChatMode(false);
    std::cout << "Quitting chat mode..." << std::endl;
}


