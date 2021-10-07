################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/DCU/Runtime/subdir.mk
-include src/DCU/Microcontroller/Wdg/subdir.mk
-include src/DCU/Microcontroller/Mpu/subdir.mk
-include src/DCU/Microcontroller/Mcu/subdir.mk
-include src/DCU/Microcontroller/Dio/subdir.mk
-include src/DCU/Microcontroller/Adc/subdir.mk
-include src/DCU/EcuAbstraction/Window/subdir.mk
-include src/DCU/EcuAbstraction/HwConfig/subdir.mk
-include src/DCU/EcuAbstraction/Door/subdir.mk
-include src/DCU/EcuAbstraction/Button/subdir.mk
-include src/DCU/Communication/Signals/subdir.mk
-include src/DCU/Application/WindowApp/subdir.mk
-include src/DCU/Application/DoorApp/subdir.mk
-include src/subdir.mk
-include board/subdir.mk
-include SDK/rtos/FreeRTOS/Source/portable/MemMang/subdir.mk
-include SDK/rtos/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include SDK/rtos/FreeRTOS/Source/subdir.mk
-include SDK/platform/drivers/src/pins/subdir.mk
-include SDK/platform/drivers/src/interrupt/subdir.mk
-include SDK/platform/drivers/src/clock/S32K1xx/subdir.mk
-include SDK/platform/devices/S32K144/startup/subdir.mk
-include SDK/platform/devices/subdir.mk
-include Project_Settings/Startup_Code/subdir.mk
-include Project_Settings/Linker_Files/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_SIZE += \
DCU_2021B_Equipo2.siz \


# All Target
all: DCU_2021B_Equipo2.elf secondary-outputs

# Tool invocations
DCU_2021B_Equipo2.elf: $(OBJS) C:\nxp\S32DS.3.4\S32DS\software\S32SDK_S32K1XX_RTM_4.0.2\platform\devices\S32K144\linker\gcc\S32K144_64_flash.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Standard S32DS C Linker'
	arm-none-eabi-gcc -o "DCU_2021B_Equipo2.elf" "@DCU_2021B_Equipo2.args"  $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

DCU_2021B_Equipo2.siz: DCU_2021B_Equipo2.elf
	@echo 'Invoking: Standard S32DS Print Size'
	arm-none-eabi-size --format=berkeley DCU_2021B_Equipo2.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) ./*
	-@echo ' '

secondary-outputs: $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets
