//------------------------------------------------------------------------------
// Console.h: interface for the Console manipulators.
//------------------------------------------------------------------------------

#if !defined( CONSOLE_MANIP_H__INCLUDED )
#define CONSOLE_MANIP_H__INCLUDED

//------------------------------------------------------------------------------

//------------------------------------------------------------------"includes"--
#include <iostream>
#include <iomanip>
#include <windows.h>

namespace colors
{
    static const WORD bgMask( BACKGROUND_BLUE      |
                              BACKGROUND_GREEN     |
                              BACKGROUND_RED       |
                              BACKGROUND_INTENSITY   );
    static const WORD fgMask( FOREGROUND_BLUE      |
                              FOREGROUND_GREEN     |
                              FOREGROUND_RED       |
                              FOREGROUND_INTENSITY   );

    static const WORD fgBlack    ( 0 );
    static const WORD fgLoRed    ( FOREGROUND_RED   );
    static const WORD fgLoGreen  ( FOREGROUND_GREEN );
    static const WORD fgLoBlue   ( FOREGROUND_BLUE  );
    static const WORD fgLoCyan   ( fgLoGreen   | fgLoBlue );
    static const WORD fgLoMagenta( fgLoRed     | fgLoBlue );
    static const WORD fgLoYellow ( fgLoRed     | fgLoGreen );
    static const WORD fgLoWhite  ( fgLoRed     | fgLoGreen | fgLoBlue );
    static const WORD fgGray     ( fgBlack     | FOREGROUND_INTENSITY );
    static const WORD fgHiWhite  ( fgLoWhite   | FOREGROUND_INTENSITY );
    static const WORD fgHiBlue   ( fgLoBlue    | FOREGROUND_INTENSITY );
    static const WORD fgHiGreen  ( fgLoGreen   | FOREGROUND_INTENSITY );
    static const WORD fgHiRed    ( fgLoRed     | FOREGROUND_INTENSITY );
    static const WORD fgHiCyan   ( fgLoCyan    | FOREGROUND_INTENSITY );
    static const WORD fgHiMagenta( fgLoMagenta | FOREGROUND_INTENSITY );
    static const WORD fgHiYellow ( fgLoYellow  | FOREGROUND_INTENSITY );
    // Background colors
    /*static const WORD bgBlack    ( 0 );
    static const WORD bgLoRed    ( BACKGROUND_RED   );
    static const WORD bgLoGreen  ( BACKGROUND_GREEN );
    static const WORD bgLoBlue   ( BACKGROUND_BLUE  );
    static const WORD bgLoCyan   ( bgLoGreen   | bgLoBlue );
    static const WORD bgLoMagenta( bgLoRed     | bgLoBlue );
    static const WORD bgLoYellow ( bgLoRed     | bgLoGreen );
    static const WORD bgLoWhite  ( bgLoRed     | bgLoGreen | bgLoBlue );
    static const WORD bgGray     ( bgBlack     | BACKGROUND_INTENSITY );
    static const WORD bgHiWhite  ( bgLoWhite   | BACKGROUND_INTENSITY );
    static const WORD bgHiBlue   ( bgLoBlue    | BACKGROUND_INTENSITY );
    static const WORD bgHiGreen  ( bgLoGreen   | BACKGROUND_INTENSITY );
    static const WORD bgHiRed    ( bgLoRed     | BACKGROUND_INTENSITY );
    static const WORD bgHiCyan   ( bgLoCyan    | BACKGROUND_INTENSITY );
    static const WORD bgHiMagenta( bgLoMagenta | BACKGROUND_INTENSITY );
    static const WORD bgHiYellow ( bgLoYellow  | BACKGROUND_INTENSITY );*/

    static class con_dev
    {
        private:
        HANDLE                      hCon;
        DWORD                       cCharsWritten;
        CONSOLE_SCREEN_BUFFER_INFO  csbi;
        DWORD                       dwConSize;

        public:
        con_dev()
        {
            hCon = GetStdHandle( STD_OUTPUT_HANDLE );
        }
        private:
        void GetInfo()
        {
            GetConsoleScreenBufferInfo( hCon, &csbi );
            dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
        }
        public:
        void Clear()
        {
            COORD coordScreen = { 0, 0 };

            GetInfo();
            FillConsoleOutputCharacter( hCon, TEXT(' '),
                                        dwConSize,
                                        coordScreen,
                                        &cCharsWritten );
            GetInfo();
            FillConsoleOutputAttribute( hCon,
                                        csbi.wAttributes,
                                        dwConSize,
                                        coordScreen,
                                        &cCharsWritten );
            SetConsoleCursorPosition( hCon, coordScreen );
        }
        void SetColor( WORD wRGBI, WORD Mask )
        {
            GetInfo();
            csbi.wAttributes &= Mask;
            csbi.wAttributes |= wRGBI;
            SetConsoleTextAttribute( hCon, csbi.wAttributes );
        }
    } console;

    inline std::ostream& reeset( std::ostream& os ){
        // We use white here as it's the standard color.
        return white(os);
    }

    //inline std::ostream& clr( std::ostream& os )
    inline std::ostream& clr()
    {
        std::ostream os;
        os.flush();
        console.Clear();
        return os;
    };

    inline std::ostream& red( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiRed, bgMask );

        return os;
    }

    inline std::ostream& green( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiGreen, bgMask );

        return os;
    }

    inline std::ostream& blue( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiBlue, bgMask );

        return os;
    }

    inline std::ostream& white( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiWhite, bgMask );

        return os;
    }

    inline std::ostream& cyan( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiCyan, bgMask );

        return os;
    }

    inline std::ostream& magenta( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiMagenta, bgMask );

        return os;
    }

    inline std::ostream& yellow( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgHiYellow, bgMask );

        return os;
    }

    inline std::ostream& black( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgBlack, bgMask );

        return os;
    }

    inline std::ostream& gray( std::ostream& os )
    {
        os.flush();
        console.SetColor( fgGray, bgMask );

        return os;
    }

    //Background manipulators
    /*inline std::ostream& bg_red( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiRed, fgMask );

        return os;
    }

    inline std::ostream& bg_green( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiGreen, fgMask );

        return os;
    }

    inline std::ostream& bg_blue( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiBlue, fgMask );

        return os;
    }

    inline std::ostream& bg_white( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiWhite, fgMask );

        return os;
    }

    inline std::ostream& bg_cyan( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiCyan, fgMask );

        return os;
    }

    inline std::ostream& bg_magenta( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiMagenta, fgMask );

        return os;
    }

    inline std::ostream& bg_yellow( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgHiYellow, fgMask );

        return os;
    }

    inline std::ostream& bg_black( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgBlack, fgMask );

        return os;
    }

    inline std::ostream& bg_gray( std::ostream& os )
    {
        os.flush();
        console.SetColor( bgGray, fgMask );

        return os;
    }*/
}

//------------------------------------------------------------------------------
#endif //!defined ( CONSOLE_MANIP_H__INCLUDED )

