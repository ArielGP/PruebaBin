################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Microcontroller/Wdg/Wdg.c 

OBJS += \
./src/DCU/Microcontroller/Wdg/Wdg.o 

C_DEPS += \
./src/DCU/Microcontroller/Wdg/Wdg.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Microcontroller/Wdg/%.o: ../src/DCU/Microcontroller/Wdg/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Microcontroller/Wdg/Wdg.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


