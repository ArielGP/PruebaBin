################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Microcontroller/Mpu/Mpu.c 

OBJS += \
./src/DCU/Microcontroller/Mpu/Mpu.o 

C_DEPS += \
./src/DCU/Microcontroller/Mpu/Mpu.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Microcontroller/Mpu/%.o: ../src/DCU/Microcontroller/Mpu/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Microcontroller/Mpu/Mpu.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


