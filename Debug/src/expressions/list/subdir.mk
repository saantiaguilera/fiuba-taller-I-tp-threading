################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/list/ExpressionList.cpp 

OBJS += \
./src/expressions/list/ExpressionList.o 

CPP_DEPS += \
./src/expressions/list/ExpressionList.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/list/%.o: ../src/expressions/list/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


