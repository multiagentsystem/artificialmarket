################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/world/environment/Environment.cpp \
../src/world/environment/Market.cpp 

OBJS += \
./src/world/environment/Environment.o \
./src/world/environment/Market.o 

CPP_DEPS += \
./src/world/environment/Environment.d \
./src/world/environment/Market.d 


# Each subdirectory must supply rules for building sources it contributes
src/world/environment/%.o: ../src/world/environment/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/yusuke/git/artificialmarket/src/common" -I"/Users/yusuke/git/artificialmarket/src/world/agent/fx" -I"/Users/yusuke/git/artificialmarket/src/world/environment" -I"/Users/yusuke/git/artificialmarket/src/world/environment/fx" -I"/Users/yusuke/git/artificialmarket/src/world/agent" -I"/Users/yusuke/git/artificialmarket/src/world" -I"/Users/yusuke/git/artificialmarket/src/world/learning/generic" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


