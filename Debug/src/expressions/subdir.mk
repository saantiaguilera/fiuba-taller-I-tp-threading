################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/ExpressionArithmetic.cpp \
../src/expressions/ExpressionConstant.cpp \
../src/expressions/ExpressionDivide.cpp \
../src/expressions/ExpressionMultiply.cpp \
../src/expressions/ExpressionSubstraction.cpp \
../src/expressions/ExpressionSum.cpp 

OBJS += \
./src/expressions/ExpressionArithmetic.o \
./src/expressions/ExpressionConstant.o \
./src/expressions/ExpressionDivide.o \
./src/expressions/ExpressionMultiply.o \
./src/expressions/ExpressionSubstraction.o \
./src/expressions/ExpressionSum.o 

CPP_DEPS += \
./src/expressions/ExpressionArithmetic.d \
./src/expressions/ExpressionConstant.d \
./src/expressions/ExpressionDivide.d \
./src/expressions/ExpressionMultiply.d \
./src/expressions/ExpressionSubstraction.d \
./src/expressions/ExpressionSum.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/%.o: ../src/expressions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


