################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/logical/ExpressionEquals.cpp \
../src/expressions/logical/ExpressionHigher.cpp \
../src/expressions/logical/ExpressionIf.cpp \
../src/expressions/logical/ExpressionLogical.cpp \
../src/expressions/logical/ExpressionLower.cpp 

OBJS += \
./src/expressions/logical/ExpressionEquals.o \
./src/expressions/logical/ExpressionHigher.o \
./src/expressions/logical/ExpressionIf.o \
./src/expressions/logical/ExpressionLogical.o \
./src/expressions/logical/ExpressionLower.o 

CPP_DEPS += \
./src/expressions/logical/ExpressionEquals.d \
./src/expressions/logical/ExpressionHigher.d \
./src/expressions/logical/ExpressionIf.d \
./src/expressions/logical/ExpressionLogical.d \
./src/expressions/logical/ExpressionLower.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/logical/%.o: ../src/expressions/logical/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


