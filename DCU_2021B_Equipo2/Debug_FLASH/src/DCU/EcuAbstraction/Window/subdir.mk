################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/EcuAbstraction/Window/Window.c 

OBJS += \
./src/DCU/EcuAbstraction/Window/Window.o 

C_DEPS += \
./src/DCU/EcuAbstraction/Window/Window.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/EcuAbstraction/Window/%.o: ../src/DCU/EcuAbstraction/Window/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/EcuAbstraction/Window/Window.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


