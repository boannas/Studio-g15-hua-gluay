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
	arm-none-eabi-gcc -mcpu=cortex-m4 -g3 -DDEBUG -c -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/BasicMathFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/BayesFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/CommonTables" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/ComplexMathFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/ControllerFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/DistanceFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/FastMathFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/FilteringFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/InterpolationFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/MatrixFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/QuaternionMathFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/StatisticsFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/SupportFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/SVMFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/TransformFunctions" -I"C:/Users/napat/Documents/GitHub/FRA222-233_Group5/FRA222_LAB2_6520/FUFU/Source/WindowFunctions" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@" "$<"

clean: clean-Core-2f-Startup

clean-Core-2f-Startup:
	-$(RM) ./Core/Startup/startup_stm32g474retx.d ./Core/Startup/startup_stm32g474retx.o

.PHONY: clean-Core-2f-Startup

