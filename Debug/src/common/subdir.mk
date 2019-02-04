################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/common/errorlog.cpp \
../src/common/tracelog.cpp \
../src/common/utility.cpp 

OBJS += \
./src/common/errorlog.o \
./src/common/tracelog.o \
./src/common/utility.o 

CPP_DEPS += \
./src/common/errorlog.d \
./src/common/tracelog.d \
./src/common/utility.d 


# Each subdirectory must supply rules for building sources it contributes
src/common/%.o: ../src/common/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cross G++ Compiler'
	g++ -I"/Users/naritomi/git/artificialmarket/src/common" -I"/Users/naritomi/git/artificialmarket/src/world/agent/fx" -I"/Users/naritomi/git/artificialmarket/src/world/environment" -I"/Users/naritomi/git/artificialmarket/src/world/environment/fx" -I"/Users/naritomi/git/artificialmarket/src/world/agent" -I"/Users/naritomi/git/artificialmarket/src/world" -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


