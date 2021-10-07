################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/EcuAbstraction/Button/Button.c 

OBJS += \
./src/DCU/EcuAbstraction/Button/Button.o 

C_DEPS += \
./src/DCU/EcuAbstraction/Button/Button.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/EcuAbstraction/Button/%.o: ../src/DCU/EcuAbstraction/Button/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/EcuAbstraction/Button/Button.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


