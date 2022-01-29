################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_callbacks.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_core.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_hal.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_callbacks.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_core.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_hal.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_callbacks.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_core.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_hal.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_callbacks.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_core.c \
../src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_hal.c \
../src/DCU/Communication/Calvos/comgen_CAN_common.c 

OBJS += \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_callbacks.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_core.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_hal.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_callbacks.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_core.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_hal.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_callbacks.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_core.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_hal.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_callbacks.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_core.o \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_hal.o \
./src/DCU/Communication/Calvos/comgen_CAN_common.o 

C_DEPS += \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_callbacks.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_core.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_hal.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_callbacks.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_core.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_PS_hal.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_callbacks.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_core.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RL_hal.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_callbacks.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_core.d \
./src/DCU/Communication/Calvos/comgen_CAN_DCM_RR_hal.d \
./src/DCU/Communication/Calvos/comgen_CAN_common.d 


# Each subdirectory must supply rules for building sources it contributes
src/DCU/Communication/Calvos/%.o: ../src/DCU/Communication/Calvos/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Standard S32DS C Compiler'
	arm-none-eabi-gcc "@src/DCU/Communication/Calvos/comgen_CAN_DCM_DR_callbacks.args" -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


