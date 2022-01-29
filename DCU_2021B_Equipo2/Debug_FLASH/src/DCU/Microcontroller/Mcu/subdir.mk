################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Microcontroller/Mcu/Mcu.c 

OBJS += \
./src/DCU/Microcontroller/Mcu/Mcu.o 

C_DEPS += \
./src/DCU/Microcontroller/Mcu/Mcu.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Microcontroller/Mcu/%.o: ../src/DCU/Microcontroller/Mcu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Microcontroller/Mcu/Mcu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


