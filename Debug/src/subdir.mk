################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Expression.cpp \
../src/ExpressionArithmetic.cpp \
../src/ExpressionConstant.cpp \
../src/ExpressionSum.cpp \
../src/LispParser.cpp \
../src/ParserUtils.cpp \
../src/RuntimeExpressionInterface.cpp \
../src/tp.cpp 

OBJS += \
./src/Expression.o \
./src/ExpressionArithmetic.o \
./src/ExpressionConstant.o \
./src/ExpressionSum.o \
./src/LispParser.o \
./src/ParserUtils.o \
./src/RuntimeExpressionInterface.o \
./src/tp.o 

CPP_DEPS += \
./src/Expression.d \
./src/ExpressionArithmetic.d \
./src/ExpressionConstant.d \
./src/ExpressionSum.d \
./src/LispParser.d \
./src/ParserUtils.d \
./src/RuntimeExpressionInterface.d \
./src/tp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


