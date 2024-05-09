################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.c \
../Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.c 

OBJS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.o \
./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.o 

C_DEPS += \
./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.d \
./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/%.o Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/%.su Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/%.cyclo: ../Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/%.c Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_MATRIX_CHECK -DUSE_HAL_DRIVER -DSTM32G474xx -c -I../Core/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc -I../Drivers/STM32G4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/ARM_CMSIS/CMSIS/Core/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/PrivateInclude/ -I../Middlewares/Third_Party/ARM_CMSIS/Include/ -I../Middlewares/Third_Party/ARM_CMSIS/Include -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/BasicMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/BayesFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/CommonTables" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/ComplexMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/ControllerFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/DistanceFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/FastMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/FilteringFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/InterpolationFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/MatrixFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/QuaternionMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/StatisticsFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/SupportFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/SVMFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/TransformFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/WindowFunctions" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-FastMathFunctions

clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-FastMathFunctions:
	-$(RM) ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.cyclo ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.d ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.o ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctions.su ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.cyclo ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.d ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.o ./Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions/FastMathFunctionsF16.su

.PHONY: clean-Middlewares-2f-Third_Party-2f-ARM_CMSIS-2f-Source-2f-FastMathFunctions

