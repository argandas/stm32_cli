################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.c 

OBJS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.o 

C_DEPS += \
./Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.o: ../Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/git/stm32_cli/UPS Basic/Inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USB_HID_Keyboard_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/console/inc" -I"C:/git/stm32_cli/UPS Basic/cmd_parser/inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USART_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USB_CDC_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/git/stm32_cli/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/git/stm32_cli/UPS Basic/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


