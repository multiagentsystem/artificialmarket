################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/main/simulation/FX/FxSimulationParameters.cpp \
../src/main/simulation/FX/main.cpp 

OBJS += \
./src/main/simulation/FX/FxSimulationParameters.o \
./src/main/simulation/FX/main.o 

CPP_DEPS += \
./src/main/simulation/FX/FxSimulationParameters.d \
./src/main/simulation/FX/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/main/simulation/FX/%.o: ../src/main/simulation/FX/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/naritomi/git/artificialmarket/src/common" -I"/Users/naritomi/git/artificialmarket/src/world/agent/fx" -I"/Users/naritomi/git/artificialmarket/src/world/environment" -I"/Users/naritomi/git/artificialmarket/src/world/environment/fx" -I"/Users/naritomi/git/artificialmarket/src/world/agent" -I"/Users/naritomi/git/artificialmarket/src/world" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


