################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/EcuAbstraction/Button/InDebounce/InDebounce.c 

OBJS += \
./src/DCU/EcuAbstraction/Button/InDebounce/InDebounce.o 

C_DEPS += \
./src/DCU/EcuAbstraction/Button/InDebounce/InDebounce.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/EcuAbstraction/Button/InDebounce/%.o: ../src/DCU/EcuAbstraction/Button/InDebounce/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/EcuAbstraction/Button/InDebounce/InDebounce.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


