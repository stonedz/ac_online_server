################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Account.cpp \
../src/Client.cpp \
../src/Clientfsm.cpp \
../src/CommandManager.cpp \
../src/CommandScheduler.cpp \
../src/Connection.cpp \
../src/ConnectionData.cpp \
../src/Console.cpp \
../src/Logger.cpp \
../src/Message.cpp \
../src/MessageIn.cpp \
../src/MessageOut.cpp \
../src/NetPacket.cpp \
../src/Packet.cpp \
../src/Server.cpp \
../src/crc32.cpp \
../src/main.cpp 

CC_SRCS += \
../src/cppsqlite3.cc \
../src/sha1.cc 

OBJS += \
./src/Account.o \
./src/Client.o \
./src/Clientfsm.o \
./src/CommandManager.o \
./src/CommandScheduler.o \
./src/Connection.o \
./src/ConnectionData.o \
./src/Console.o \
./src/Logger.o \
./src/Message.o \
./src/MessageIn.o \
./src/MessageOut.o \
./src/NetPacket.o \
./src/Packet.o \
./src/Server.o \
./src/cppsqlite3.o \
./src/crc32.o \
./src/main.o \
./src/sha1.o 

CC_DEPS += \
./src/cppsqlite3.d \
./src/sha1.d 

CPP_DEPS += \
./src/Account.d \
./src/Client.d \
./src/Clientfsm.d \
./src/CommandManager.d \
./src/CommandScheduler.d \
./src/Connection.d \
./src/ConnectionData.d \
./src/Console.d \
./src/Logger.d \
./src/Message.d \
./src/MessageIn.d \
./src/MessageOut.d \
./src/NetPacket.d \
./src/Packet.d \
./src/Server.d \
./src/crc32.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTESTPHASE -DFIXEDPOINT -DFLOATINGPOINT -DNDEBUG -DLINUX -I/usr/include/SDL -I../src/pawn/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DTESTPHASE -DFIXEDPOINT -DFLOATINGPOINT -DNDEBUG -DLINUX -I/usr/include/SDL -I../src/pawn/ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


