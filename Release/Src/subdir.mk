################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/cgi.c \
../Src/ethernetif.c \
../Src/flash_if.c \
../Src/flash_write.c \
../Src/freertos.c \
../Src/lwip.c \
../Src/main.c \
../Src/my_mibs.c \
../Src/net_param_init.c \
../Src/ssi.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_tim.c \
../Src/stm32f4xx_it.c \
../Src/syscalls.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/cgi.o \
./Src/ethernetif.o \
./Src/flash_if.o \
./Src/flash_write.o \
./Src/freertos.o \
./Src/lwip.o \
./Src/main.o \
./Src/my_mibs.o \
./Src/net_param_init.o \
./Src/ssi.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_tim.o \
./Src/stm32f4xx_it.o \
./Src/syscalls.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/cgi.d \
./Src/ethernetif.d \
./Src/flash_if.d \
./Src/flash_write.d \
./Src/freertos.d \
./Src/lwip.d \
./Src/main.d \
./Src/my_mibs.d \
./Src/net_param_init.d \
./Src/ssi.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_tim.d \
./Src/stm32f4xx_it.d \
./Src/syscalls.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"F:/STM/SvetoforSNMP/Inc" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/system" -I"F:/STM/SvetoforSNMP/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/STM/SvetoforSNMP/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/apps/httpd" -I"F:/STM/SvetoforSNMP/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/netif" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/posix" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/system/arch" -I"F:/STM/SvetoforSNMP/Middlewares/Third_Party/LwIP/src/apps/snmp" -I"F:/STM/SvetoforSNMP/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


