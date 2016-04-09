################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/arithmetic/ExpressionArithmetic.cpp \
../src/expressions/arithmetic/ExpressionDivide.cpp \
../src/expressions/arithmetic/ExpressionMultiply.cpp \
../src/expressions/arithmetic/ExpressionSubstraction.cpp \
../src/expressions/arithmetic/ExpressionSum.cpp 

OBJS += \
./src/expressions/arithmetic/ExpressionArithmetic.o \
./src/expressions/arithmetic/ExpressionDivide.o \
./src/expressions/arithmetic/ExpressionMultiply.o \
./src/expressions/arithmetic/ExpressionSubstraction.o \
./src/expressions/arithmetic/ExpressionSum.o 

CPP_DEPS += \
./src/expressions/arithmetic/ExpressionArithmetic.d \
./src/expressions/arithmetic/ExpressionDivide.d \
./src/expressions/arithmetic/ExpressionMultiply.d \
./src/expressions/arithmetic/ExpressionSubstraction.d \
./src/expressions/arithmetic/ExpressionSum.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/arithmetic/%.o: ../src/expressions/arithmetic/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


