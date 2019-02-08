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
	g++ -I"/Users/yusuke/git/artificialmarket/src/common" -I"/Users/yusuke/git/artificialmarket/src/world/agent/fx" -I"/Users/yusuke/git/artificialmarket/src/world/environment" -I"/Users/yusuke/git/artificialmarket/src/world/environment/fx" -I"/Users/yusuke/git/artificialmarket/src/world/agent" -I"/Users/yusuke/git/artificialmarket/src/world" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


