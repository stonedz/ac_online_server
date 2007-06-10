#ifndef CONSOLE_LINUX_H
#define CONSOLE_LINUX_H
#include <iostream>
#include <iomanip>

namespace colors{

    inline void clr(){
        system("clear");
    }

    inline std::ostream& reset( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& red( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& green( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& blue( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& white( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& cyan( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& magenta( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& yellow( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& black( std::ostream& os )
    {
        return os;
    }

    inline std::ostream& grey( std::ostream& os )
    {
        return os;
    }
}
#endif
