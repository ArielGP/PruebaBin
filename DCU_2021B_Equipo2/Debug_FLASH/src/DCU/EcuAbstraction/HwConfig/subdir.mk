################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/EcuAbstraction/HwConfig/HwConfig.c 

OBJS += \
./src/DCU/EcuAbstraction/HwConfig/HwConfig.o 

C_DEPS += \
./src/DCU/EcuAbstraction/HwConfig/HwConfig.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/EcuAbstraction/HwConfig/%.o: ../src/DCU/EcuAbstraction/HwConfig/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/EcuAbstraction/HwConfig/HwConfig.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


