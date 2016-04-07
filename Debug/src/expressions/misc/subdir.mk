################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/expressions/misc/ExpressionConstant.cpp \
../src/expressions/misc/ExpressionPrint.cpp 

OBJS += \
./src/expressions/misc/ExpressionConstant.o \
./src/expressions/misc/ExpressionPrint.o 

CPP_DEPS += \
./src/expressions/misc/ExpressionConstant.d \
./src/expressions/misc/ExpressionPrint.d 


# Each subdirectory must supply rules for building sources it contributes
src/expressions/misc/%.o: ../src/expressions/misc/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


