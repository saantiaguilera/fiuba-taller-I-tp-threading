################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Expression.cpp \
../src/LispParser.cpp \
../src/tp.cpp 

OBJS += \
./src/Expression.o \
./src/LispParser.o \
./src/tp.o 

CPP_DEPS += \
./src/Expression.d \
./src/LispParser.d \
./src/tp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


