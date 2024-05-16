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
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/BasicMathFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/BayesFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/CommonTables" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/ComplexMathFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/ControllerFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/DistanceFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/FastMathFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/FilteringFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/InterpolationFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/MatrixFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/QuaternionMathFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/StatisticsFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/SupportFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/SVMFunctions" -I"C:/Users/porpo/OneDrive/Documents/GitHub/Newlife/Studio-g15-hua-gluay/Studio_G15/Middlewares/Third_Party/ARM_CMSIS/Source/TransformFunctions" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g474retx.d ./Core/Startup/startup_stm32g474retx.o

.PHONY: clean-Core-2f-Startup

