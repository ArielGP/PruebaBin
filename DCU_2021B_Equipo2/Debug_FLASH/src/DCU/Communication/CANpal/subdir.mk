################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Communication/CANpal/CANpal.c 

OBJS += \
./src/DCU/Communication/CANpal/CANpal.o 

C_DEPS += \
./src/DCU/Communication/CANpal/CANpal.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Communication/CANpal/%.o: ../src/DCU/Communication/CANpal/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Communication/CANpal/CANpal.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


