################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/%.o Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/%.su Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/%.cyclo: ../Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_MATRIX_CHECK -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/Include -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/BasicMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/BayesFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/CommonTables" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/ComplexMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/ControllerFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/DistanceFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/FastMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/FilteringFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/InterpolationFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/MatrixFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/QuaternionMathFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/StatisticsFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/SupportFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/SVMFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/TransformFunctions" -I"C:/Users/napat/Documents/GitHub/Studio-g15-hua-gluay/Aunnyleah/Source/WindowFunctions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-ControllerFunctions

clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-ControllerFunctions:
	-$(RM) ./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.cyclo ./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.d ./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.o ./Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions/ControllerFunctions.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-ControllerFunctions

