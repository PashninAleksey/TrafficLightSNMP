################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"F:/STM/SvetoforSNMP/Inc" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/system" -I"F:/STM/SvetoforSNMP/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/STM/SvetoforSNMP/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/apps/httpd" -I"F:/STM/SvetoforSNMP/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/netif" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/posix" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/system/arch" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/apps/snmp" -I"F:/STM/SvetoforSNMP/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


