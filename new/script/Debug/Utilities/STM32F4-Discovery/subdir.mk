################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Utilities/STM32F4-Discovery/stm32f4_discovery.c \
../Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.c \
../Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.c 

OBJS += \
./Utilities/STM32F4-Discovery/stm32f4_discovery.o \
./Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.o \
./Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.o 

C_DEPS += \
./Utilities/STM32F4-Discovery/stm32f4_discovery.d \
./Utilities/STM32F4-Discovery/stm32f4_discovery_audio_codec.d \
./Utilities/STM32F4-Discovery/stm32f4_discovery_lis302dl.d 


# Each subdirectory must supply rules for building sources it contributes
Utilities/STM32F4-Discovery/%.o: ../Utilities/STM32F4-Discovery/%.c
	arm-atollic-eabi-gcc -c "$<" -mthumb -mcpu=cortex-m4 -std=gnu11 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000 -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Libraries/UB_VGA/inc -I../Utilities/STM32F4-Discovery -I../Libraries/CMSIS/src -I../src -O0 -ffunction-sections -fdata-sections -g -fstack-usage -Wall -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

