################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Microcontroller/Dio/Dio.c 

OBJS += \
./src/DCU/Microcontroller/Dio/Dio.o 

C_DEPS += \
./src/DCU/Microcontroller/Dio/Dio.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Microcontroller/Dio/%.o: ../src/DCU/Microcontroller/Dio/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Microcontroller/Dio/Dio.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


