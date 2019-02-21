################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/world/agent/fx/FxAgent.cpp \
../src/world/agent/fx/FxSimulationParameters.cpp 

OBJS += \
./src/world/agent/fx/FxAgent.o \
./src/world/agent/fx/FxSimulationParameters.o 

CPP_DEPS += \
./src/world/agent/fx/FxAgent.d \
./src/world/agent/fx/FxSimulationParameters.d 


# Each subdirectory must supply rules for building sources it contributes
src/world/agent/fx/%.o: ../src/world/agent/fx/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/naritomi/git/artificialmarket/src/common" -I"/Users/naritomi/git/artificialmarket/src/world/agent/fx" -I"/Users/naritomi/git/artificialmarket/src/world/environment" -I"/Users/naritomi/git/artificialmarket/src/world/environment/fx" -I"/Users/naritomi/git/artificialmarket/src/world/agent" -I"/Users/naritomi/git/artificialmarket/src/world" -I"/Users/naritomi/git/artificialmarket/src/world/learning/generic" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


