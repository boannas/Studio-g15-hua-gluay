################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Core/Startup/startup_stm32g474retx.s 

OBJS += \
./Core/Startup/startup_stm32g474retx.o 

S_DEPS += \
./Core/Startup/startup_stm32g474retx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Startup/%.o: ../Core/Startup/%.s Core/Startup/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/BasicMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/BayesFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/CommonTables" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/ComplexMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/ControllerFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/DistanceFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/FastMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/FilteringFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/InterpolationFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/MatrixFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/QuaternionMathFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/StatisticsFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/SupportFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/SVMFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/TransformFunctions" -I"C:/Users/porpo/Downloads/Studio-g15-hua-gluay-main (1)/Studio-g15-hua-gluay-main/Aunnyleah/Source/WindowFunctions" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g474retx.d ./Core/Startup/startup_stm32g474retx.o

.PHONY: clean-Core-2f-Startup

