################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/IO.cpp \
../src/Main.cpp \
../src/OpTab.cpp \
../src/Parser.cpp \
../src/StringUtilities.cpp \
../src/Validate.cpp 

OBJS += \
./src/IO.o \
./src/Main.o \
./src/OpTab.o \
./src/Parser.o \
./src/StringUtilities.o \
./src/Validate.o 

CPP_DEPS += \
./src/IO.d \
./src/Main.d \
./src/OpTab.d \
./src/Parser.d \
./src/StringUtilities.d \
./src/Validate.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


