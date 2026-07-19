################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../App/bsp/gpio/bsp_gpio.c 

OBJS += \
./App/bsp/gpio/bsp_gpio.o 

C_DEPS += \
./App/bsp/gpio/bsp_gpio.d 


# Each subdirectory must supply rules for building sources it contributes
App/bsp/gpio/%.o App/bsp/gpio/%.su App/bsp/gpio/%.cyclo: ../App/bsp/gpio/%.c App/bsp/gpio/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I"D:/GBdevelop/Workspace/stm32_ws/f411ceu6/f411ceu6_petbot_servo/App" -I"D:/GBdevelop/Workspace/stm32_ws/f411ceu6/f411ceu6_petbot_servo/App/include" -I"D:/GBdevelop/Workspace/stm32_ws/f411ceu6/f411ceu6_petbot_servo/App/bsp" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-App-2f-bsp-2f-gpio

clean-App-2f-bsp-2f-gpio:
	-$(RM) ./App/bsp/gpio/bsp_gpio.cyclo ./App/bsp/gpio/bsp_gpio.d ./App/bsp/gpio/bsp_gpio.o ./App/bsp/gpio/bsp_gpio.su

.PHONY: clean-App-2f-bsp-2f-gpio

