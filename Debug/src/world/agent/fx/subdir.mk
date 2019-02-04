################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/world/agent/fx/FxAgent.cpp 

OBJS += \
./src/world/agent/fx/FxAgent.o 

CPP_DEPS += \
./src/world/agent/fx/FxAgent.d 


# Each subdirectory must supply rules for building sources it contributes
src/world/agent/fx/%.o: ../src/world/agent/fx/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/naritomi/git/multiagent-systems-tmp/src/common" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/environment" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/agent" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/agent/fx" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/environment/fx" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


