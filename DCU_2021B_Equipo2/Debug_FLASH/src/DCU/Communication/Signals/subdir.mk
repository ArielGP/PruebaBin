################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Communication/Signals/Signals.c 

OBJS += \
./src/DCU/Communication/Signals/Signals.o 

C_DEPS += \
./src/DCU/Communication/Signals/Signals.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Communication/Signals/%.o: ../src/DCU/Communication/Signals/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Communication/Signals/Signals.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


