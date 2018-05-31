################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/InputOutput.cpp \
../src/LogicLayer.cpp \
../src/Userinterface.cpp \
../src/main.cpp 

OBJS += \
./src/InputOutput.o \
./src/LogicLayer.o \
./src/Userinterface.o \
./src/main.o 

CPP_DEPS += \
./src/InputOutput.d \
./src/LogicLayer.d \
./src/Userinterface.d \
./src/main.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	arm-atollic-eabi-g++ -c "$<" -mthumb -mcpu=cortex-m4 -std=gnu++98 -DSTM32F4XX -DSTM32F40XX -DUSE_STDPERIPH_DRIVER -DUSE_STM32F4_DISCOVERY -DHSE_VALUE=8000000 -I../src -I../Libraries/CMSIS/Include -I../Libraries/Device/STM32F4xx/Include -I../Libraries/STM32F4xx_StdPeriph_Driver/inc -I../Libraries/UB_VGA/inc -I../Utilities/STM32F4-Discovery -O0 -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions -g -fstack-usage -Wall -fno-threadsafe-statics -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -specs=nano.specs -o "$@"

