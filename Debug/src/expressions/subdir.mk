################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/ExpressionCommon.cpp 

OBJS += \
./src/expressions/ExpressionCommon.o 

CPP_DEPS += \
./src/expressions/ExpressionCommon.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/%.o: ../src/expressions/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


