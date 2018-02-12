################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/crc.c \
../Src/dma.c \
../Src/freertos.c \
../Src/gpio.c \
../Src/main.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_hal_timebase_TIM.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c \
../Src/usart.c \
../Src/usb_device.c \
../Src/usbd_cdc_if.c \
../Src/usbd_conf.c \
../Src/usbd_desc.c \
../Src/utils.c 

OBJS += \
./Src/crc.o \
./Src/dma.o \
./Src/freertos.o \
./Src/gpio.o \
./Src/main.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_hal_timebase_TIM.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o \
./Src/usart.o \
./Src/usb_device.o \
./Src/usbd_cdc_if.o \
./Src/usbd_conf.o \
./Src/usbd_desc.o \
./Src/utils.o 

C_DEPS += \
./Src/crc.d \
./Src/dma.d \
./Src/freertos.d \
./Src/gpio.d \
./Src/main.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_hal_timebase_TIM.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d \
./Src/usart.d \
./Src/usb_device.d \
./Src/usbd_cdc_if.d \
./Src/usbd_conf.d \
./Src/usbd_desc.d \
./Src/utils.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed=__attribute__((__packed__))' -DUSE_HAL_DRIVER -DSTM32F401xE -I"C:/git/stm32_cli/UPS Basic/Inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USB_HID_Keyboard_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/console/inc" -I"C:/git/stm32_cli/UPS Basic/cmd_parser/inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USART_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/USB_CDC_Handler/inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/git/stm32_cli/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/git/stm32_cli/UPS Basic/Middlewares/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/git/stm32_cli/UPS Basic/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/include" -I"C:/git/stm32_cli/UPS Basic/Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS" -I"C:/git/stm32_cli/UPS Basic/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


