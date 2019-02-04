################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/world/environment/fx/FxMarket.cpp \
../src/world/environment/fx/News.cpp \
../src/world/environment/fx/RealFx.cpp 

OBJS += \
./src/world/environment/fx/FxMarket.o \
./src/world/environment/fx/News.o \
./src/world/environment/fx/RealFx.o 

CPP_DEPS += \
./src/world/environment/fx/FxMarket.d \
./src/world/environment/fx/News.d \
./src/world/environment/fx/RealFx.d 


# Each subdirectory must supply rules for building sources it contributes
src/world/environment/fx/%.o: ../src/world/environment/fx/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/naritomi/git/multiagent-systems-tmp/src/common" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/environment" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/agent" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/agent/fx" -I"/Users/naritomi/git/multiagent-systems-tmp/src/world/environment/fx" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


