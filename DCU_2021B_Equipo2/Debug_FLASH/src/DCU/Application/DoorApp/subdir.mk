################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Application/DoorApp/DoorApp.c 

OBJS += \
./src/DCU/Application/DoorApp/DoorApp.o 

C_DEPS += \
./src/DCU/Application/DoorApp/DoorApp.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Application/DoorApp/%.o: ../src/DCU/Application/DoorApp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Application/DoorApp/DoorApp.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


