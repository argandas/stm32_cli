################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/USART_Handler/src/circ_buffers.c \
../Middlewares/USART_Handler/src/usart_handler.c 

OBJS += \
./Middlewares/USART_Handler/src/circ_buffers.o \
./Middlewares/USART_Handler/src/usart_handler.o 

C_DEPS += \
./Middlewares/USART_Handler/src/circ_buffers.d \
./Middlewares/USART_Handler/src/usart_handler.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/USART_Handler/src/%.o: ../Middlewares/USART_Handler/src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/Users/Argandas/Desktop/UPS Basic/Inc" -I"C:/Users/Argandas/Desktop/UPS Basic/console/inc" -I"C:/Users/Argandas/Desktop/UPS Basic/cmd_parser/inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/USART_Handler/inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/USB_CDC_Handler/inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Argandas/Desktop/UPS Basic/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/Users/Argandas/Desktop/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/Users/Argandas/Desktop/UPS Basic/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


