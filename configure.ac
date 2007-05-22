AC_INIT(src/main.cpp)

AM_INIT_AUTOMAKE(lo-testserver,0.1)

AC_CONFIG_HEADER(config.h)

AC_PROG_CC

AC_PROG_CXX

AC_PROG_INSTALL

AC_PROG_LIBTOOL

AC_OUTPUT(Makefile src/Makefile src/pawn/Makefile src/commands/Makefile)

LIBS="-lSDL -lSDL_net -lpthread -lm -lsqlite3 $LIBS"
LDFLAGS=$LIBS

AC_SUBST(GLOBALCPPFLAGS, $CPPFLAGS )
AC_SUBST(GLOBALLDFLAGS, $LDFLAGS )
