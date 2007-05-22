bin_PROGRAMS = lotestserver

lotestserver_SOURCES = main.cpp \
		       Account.cpp Account.h \
		       Char.cpp Char.h \
		       Client.cpp Client.h \
		       Clientfsm.cpp Clientfsm.h \
		       CommandManager.cpp CommandManager.h \
		       CommandScheduler.cpp CommandScheduler.h \
		       Connection.cpp Connection.h \
		       ConnectionData.cpp ConnectionData.h \
		       Console.cpp Console.h \
		       IGameObject.cpp IGameObject.h \
		       IMoveableObject.cpp IMoveableObject.h \
		       Location.cpp Location.h \
		       Logger.cpp Logger.h \
		       Message.cpp Message.h \
		       MessageIn.cpp MessageIn.h \
		       MessageOut.cpp MessageOut.h \
		       NetPacket.cpp NetPacket.h \
		       Packet.cpp Packet.h \
		       Server.cpp Server.h \
		       cppsqlite3.cc cppsqlite3.h \
		       crc32.cpp crc32.h \
		       sha1.cc sha1.h 

SUBDIRS = commands pawn

INCLUDES = -I/usr/include/SDL -Ipawn/ -Icommands/ -I./

LDADD = commands/libcommands.a pawn/libpawn.a -lSDL -lSDL_net -lm -lsqlite3 -lpthread
