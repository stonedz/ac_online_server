#include "Cmd_top.h"
#include <vector>

Cmd_top::~Cmd_top()
{
    //dtor
}


void Cmd_top::help(){
    std::cout << "Shows real-time server performances and load" << std::endl;
}

void Cmd_top::execute(){
    std::vector<Uint16>& perfShort = (myServer->getGamefsm()).getPerformanceShort();
    std::vector<Uint16>& perfLong = (myServer->getGamefsm()).getPerformanceLong();
    float sizeShort = perfShort.size();
    float sizeLong = perfLong.size();
    float tmpShort = 0;
    float tmpLong = 0;

    for(Uint16 count = 0; count < sizeShort; count++)
        tmpShort += perfShort[count];

    //tmpShort = tmpShort/sizeShort;
    std::cout << "somma = " << tmpShort << std::endl;
    std::cout << "quanto = " << sizeShort << std::endl;
    std::cout << "media = " << tmpShort/sizeShort << std::endl;

}
