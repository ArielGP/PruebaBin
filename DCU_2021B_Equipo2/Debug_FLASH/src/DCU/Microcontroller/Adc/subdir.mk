################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Microcontroller/Adc/Adc.c 

OBJS += \
./src/DCU/Microcontroller/Adc/Adc.o 

C_DEPS += \
./src/DCU/Microcontroller/Adc/Adc.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Microcontroller/Adc/%.o: ../src/DCU/Microcontroller/Adc/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Microcontroller/Adc/Adc.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


