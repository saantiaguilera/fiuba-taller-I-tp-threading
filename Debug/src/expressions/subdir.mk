################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/ExpressionCommon.cpp \
../src/expressions/ExpressionConstant.cpp \
../src/expressions/ExpressionIf.cpp \
../src/expressions/ExpressionPrint.cpp 

OBJS += \
./src/expressions/ExpressionCommon.o \
./src/expressions/ExpressionConstant.o \
./src/expressions/ExpressionIf.o \
./src/expressions/ExpressionPrint.o 

CPP_DEPS += \
./src/expressions/ExpressionCommon.d \
./src/expressions/ExpressionConstant.d \
./src/expressions/ExpressionIf.d \
./src/expressions/ExpressionPrint.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/%.o: ../src/expressions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


