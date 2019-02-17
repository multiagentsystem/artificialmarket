################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/world/environment/historicalmarket/HistoricalMarket.cpp 

OBJS += \
./src/world/environment/historicalmarket/HistoricalMarket.o 

CPP_DEPS += \
./src/world/environment/historicalmarket/HistoricalMarket.d 


# Each subdirectory must supply rules for building sources it contributes
src/world/environment/historicalmarket/%.o: ../src/world/environment/historicalmarket/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/yusuke/git/artificialmarket/src/common" -I"/Users/yusuke/git/artificialmarket/src/world/agent/fx" -I"/Users/yusuke/git/artificialmarket/src/world/environment" -I"/Users/yusuke/git/artificialmarket/src/world/environment/fx" -I"/Users/yusuke/git/artificialmarket/src/world/agent" -I"/Users/yusuke/git/artificialmarket/src/world" -I"/Users/yusuke/git/artificialmarket/src/world/learning/generic" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


