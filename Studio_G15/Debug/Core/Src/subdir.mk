################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/BaseSystem.c \
../Core/Src/Encoder_AMT.c \
../Core/Src/ModBusRTU.c \
../Core/Src/Motor.c \
../Core/Src/PID_controller.c \
../Core/Src/PS2.c \
../Core/Src/Trapezoidal.c \
../Core/Src/kalman.c \
../Core/Src/main.c \
../Core/Src/stm32g4xx_hal_msp.c \
../Core/Src/stm32g4xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g4xx.c 

OBJS += \
./Core/Src/BaseSystem.o \
./Core/Src/Encoder_AMT.o \
./Core/Src/ModBusRTU.o \
./Core/Src/Motor.o \
./Core/Src/PID_controller.o \
./Core/Src/PS2.o \
./Core/Src/Trapezoidal.o \
./Core/Src/kalman.o \
./Core/Src/main.o \
./Core/Src/stm32g4xx_hal_msp.o \
./Core/Src/stm32g4xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g4xx.o 

C_DEPS += \
./Core/Src/BaseSystem.d \
./Core/Src/Encoder_AMT.d \
./Core/Src/ModBusRTU.d \
./Core/Src/Motor.d \
./Core/Src/PID_controller.d \
./Core/Src/PS2.d \
./Core/Src/Trapezoidal.d \
./Core/Src/kalman.d \
./Core/Src/main.d \
./Core/Src/stm32g4xx_hal_msp.d \
./Core/Src/stm32g4xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_MATRIX_CHECK -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/Include -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/BasicMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/BayesFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/CommonTables" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/ComplexMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/DistanceFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/FilteringFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/InterpolationFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/MatrixFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/QuaternionMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/SupportFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/SVMFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/TransformFunctions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/BaseSystem.cyclo ./Core/Src/BaseSystem.d ./Core/Src/BaseSystem.o ./Core/Src/BaseSystem.su ./Core/Src/Encoder_AMT.cyclo ./Core/Src/Encoder_AMT.d ./Core/Src/Encoder_AMT.o ./Core/Src/Encoder_AMT.su ./Core/Src/ModBusRTU.cyclo ./Core/Src/ModBusRTU.d ./Core/Src/ModBusRTU.o ./Core/Src/ModBusRTU.su ./Core/Src/Motor.cyclo ./Core/Src/Motor.d ./Core/Src/Motor.o ./Core/Src/Motor.su ./Core/Src/PID_controller.cyclo ./Core/Src/PID_controller.d ./Core/Src/PID_controller.o ./Core/Src/PID_controller.su ./Core/Src/PS2.cyclo ./Core/Src/PS2.d ./Core/Src/PS2.o ./Core/Src/PS2.su ./Core/Src/Trapezoidal.cyclo ./Core/Src/Trapezoidal.d ./Core/Src/Trapezoidal.o ./Core/Src/Trapezoidal.su ./Core/Src/kalman.cyclo ./Core/Src/kalman.d ./Core/Src/kalman.o ./Core/Src/kalman.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32g4xx_hal_msp.cyclo ./Core/Src/stm32g4xx_hal_msp.d ./Core/Src/stm32g4xx_hal_msp.o ./Core/Src/stm32g4xx_hal_msp.su ./Core/Src/stm32g4xx_it.cyclo ./Core/Src/stm32g4xx_it.d ./Core/Src/stm32g4xx_it.o ./Core/Src/stm32g4xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32g4xx.cyclo ./Core/Src/system_stm32g4xx.d ./Core/Src/system_stm32g4xx.o ./Core/Src/system_stm32g4xx.su

.PHONY: clean-Core-2f-Src

