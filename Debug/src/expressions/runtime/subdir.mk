################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/runtime/ExpressionFunction.cpp \
../src/expressions/runtime/ExpressionSync.cpp \
../src/expressions/runtime/ExpressionVariable.cpp 

OBJS += \
./src/expressions/runtime/ExpressionFunction.o \
./src/expressions/runtime/ExpressionSync.o \
./src/expressions/runtime/ExpressionVariable.o 

CPP_DEPS += \
./src/expressions/runtime/ExpressionFunction.d \
./src/expressions/runtime/ExpressionSync.d \
./src/expressions/runtime/ExpressionVariable.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/runtime/%.o: ../src/expressions/runtime/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


