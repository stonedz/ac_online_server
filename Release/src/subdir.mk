################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Client.cpp \
../src/Connection.cpp \
../src/ConnectionData.cpp \
../src/Server.cpp \
../src/main.cpp 

OBJS += \
./src/Client.o \
./src/Connection.o \
./src/ConnectionData.o \
./src/Server.o \
./src/main.o 

CPP_DEPS += \
./src/Client.d \
./src/Connection.d \
./src/ConnectionData.d \
./src/Server.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I/usr/include/SDL -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


