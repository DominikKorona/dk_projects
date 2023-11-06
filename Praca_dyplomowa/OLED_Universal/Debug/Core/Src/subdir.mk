################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Arial8.c \
../Core/Src/Arial_new.c \
../Core/Src/Font.c \
../Core/Src/font_arial_14pt.c \
../Core/Src/main.c \
../Core/Src/oled_fonts.c \
../Core/Src/oled_functions.c \
../Core/Src/oled_gram.c \
../Core/Src/oled_init.c \
../Core/Src/stm32f4xx_hal_msp.c \
../Core/Src/stm32f4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f4xx.c 

OBJS += \
./Core/Src/Arial8.o \
./Core/Src/Arial_new.o \
./Core/Src/Font.o \
./Core/Src/font_arial_14pt.o \
./Core/Src/main.o \
./Core/Src/oled_fonts.o \
./Core/Src/oled_functions.o \
./Core/Src/oled_gram.o \
./Core/Src/oled_init.o \
./Core/Src/stm32f4xx_hal_msp.o \
./Core/Src/stm32f4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f4xx.o 

C_DEPS += \
./Core/Src/Arial8.d \
./Core/Src/Arial_new.d \
./Core/Src/Font.d \
./Core/Src/font_arial_14pt.d \
./Core/Src/main.d \
./Core/Src/oled_fonts.d \
./Core/Src/oled_functions.d \
./Core/Src/oled_gram.d \
./Core/Src/oled_init.d \
./Core/Src/stm32f4xx_hal_msp.d \
./Core/Src/stm32f4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F411xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/Arial8.d ./Core/Src/Arial8.o ./Core/Src/Arial8.su ./Core/Src/Arial_new.d ./Core/Src/Arial_new.o ./Core/Src/Arial_new.su ./Core/Src/Font.d ./Core/Src/Font.o ./Core/Src/Font.su ./Core/Src/font_arial_14pt.d ./Core/Src/font_arial_14pt.o ./Core/Src/font_arial_14pt.su ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/oled_fonts.d ./Core/Src/oled_fonts.o ./Core/Src/oled_fonts.su ./Core/Src/oled_functions.d ./Core/Src/oled_functions.o ./Core/Src/oled_functions.su ./Core/Src/oled_gram.d ./Core/Src/oled_gram.o ./Core/Src/oled_gram.su ./Core/Src/oled_init.d ./Core/Src/oled_init.o ./Core/Src/oled_init.su ./Core/Src/stm32f4xx_hal_msp.d ./Core/Src/stm32f4xx_hal_msp.o ./Core/Src/stm32f4xx_hal_msp.su ./Core/Src/stm32f4xx_it.d ./Core/Src/stm32f4xx_it.o ./Core/Src/stm32f4xx_it.su ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32f4xx.d ./Core/Src/system_stm32f4xx.o ./Core/Src/system_stm32f4xx.su

.PHONY: clean-Core-2f-Src

