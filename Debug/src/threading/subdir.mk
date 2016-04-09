################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/threading/Mutex.cpp \
../src/threading/ParserWorker.cpp \
../src/threading/ReentrantLock.cpp \
../src/threading/Thread.cpp 

OBJS += \
./src/threading/Mutex.o \
./src/threading/ParserWorker.o \
./src/threading/ReentrantLock.o \
./src/threading/Thread.o 

CPP_DEPS += \
./src/threading/Mutex.d \
./src/threading/ParserWorker.d \
./src/threading/ReentrantLock.d \
./src/threading/Thread.d 


# Each subdirectory must supply rules for building sources it contributes
src/threading/%.o: ../src/threading/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -pthread -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


