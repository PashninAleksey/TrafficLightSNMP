################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.c \
../Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.c 

OBJS += \
./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.o \
./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.o 

C_DEPS += \
./Middlewares/Third_Party/LwIP/src/core/ipv6/dhcp6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ethip6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/icmp6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/inet6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_addr.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/ip6_frag.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/mld6.d \
./Middlewares/Third_Party/LwIP/src/core/ipv6/nd6.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/LwIP/src/core/ipv6/%.o: ../Middlewares/Third_Party/LwIP/src/core/ipv6/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -DUSE_HAL_DRIVER -DSTM32F407xx -I"F:/STM/snmp_traffic_light/Inc" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/system" -I"F:/STM/snmp_traffic_light/Drivers/STM32F4xx_HAL_Driver/Inc" -I"F:/STM/snmp_traffic_light/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/FreeRTOS/Source/include" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/netif/ppp" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/apps/httpd" -I"F:/STM/snmp_traffic_light/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/lwip" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/lwip/apps" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/lwip/priv" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/lwip/prot" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/netif" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/posix" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/include/posix/sys" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/system/arch" -I"F:/STM/snmp_traffic_light/Middlewares/Third_Party/LwIP/src/apps/snmp" -I"F:/STM/snmp_traffic_light/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


