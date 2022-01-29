################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/EcuAbstraction/Door/Door.c 

OBJS += \
./src/DCU/EcuAbstraction/Door/Door.o 

C_DEPS += \
./src/DCU/EcuAbstraction/Door/Door.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/EcuAbstraction/Door/%.o: ../src/DCU/EcuAbstraction/Door/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/EcuAbstraction/Door/Door.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


