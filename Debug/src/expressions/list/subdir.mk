################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/list/ExpressionAppend.cpp \
../src/expressions/list/ExpressionFrontList.cpp \
../src/expressions/list/ExpressionList.cpp \
../src/expressions/list/ExpressionTailList.cpp 

OBJS += \
./src/expressions/list/ExpressionAppend.o \
./src/expressions/list/ExpressionFrontList.o \
./src/expressions/list/ExpressionList.o \
./src/expressions/list/ExpressionTailList.o 

CPP_DEPS += \
./src/expressions/list/ExpressionAppend.d \
./src/expressions/list/ExpressionFrontList.d \
./src/expressions/list/ExpressionList.d \
./src/expressions/list/ExpressionTailList.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/list/%.o: ../src/expressions/list/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


