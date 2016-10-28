################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../libs/socket_utils_server.c 

OBJS += \
./libs/socket_utils_server.o 

C_DEPS += \
./libs/socket_utils_server.d 


# Each subdirectory must supply rules for building sources it contributes
libs/%.o: ../libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


