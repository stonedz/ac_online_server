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
        os << "\033[0m";

        return os;
    }

    inline std::ostream& red( std::ostream& os )
    {
        os << "\033[31;1m";

        return os;
    }

    inline std::ostream& green( std::ostream& os )
    {
        os << "\033[32;1m";

        return os;
    }

    inline std::ostream& blue( std::ostream& os )
    {
        os << "\033[34;1m";

        return os;
    }

    inline std::ostream& white( std::ostream& os )
    {
        os << "\033[37;1m";

        return os;
    }

    inline std::ostream& cyan( std::ostream& os )
    {
        os << "\033[36;1m";

        return os;
    }

    inline std::ostream& magenta( std::ostream& os )
    {
        os << "\033[35;1m";

        return os;
    }

    inline std::ostream& yellow( std::ostream& os )
    {
        os << "\033[33;1m";

        return os;
    }

    inline std::ostream& black( std::ostream& os )
    {
        os << "\033[30;1m";

        return os;
    }

    inline std::ostream& grey( std::ostream& os )
    {
        os << "\033[37;1m";

        return os;
    }
}
#endif
