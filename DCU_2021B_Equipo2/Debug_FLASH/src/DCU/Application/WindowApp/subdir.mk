################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Application/WindowApp/WindowApp.c 

OBJS += \
./src/DCU/Application/WindowApp/WindowApp.o 

C_DEPS += \
./src/DCU/Application/WindowApp/WindowApp.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Application/WindowApp/%.o: ../src/DCU/Application/WindowApp/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Application/WindowApp/WindowApp.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


