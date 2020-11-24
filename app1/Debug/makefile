################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32F4xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
app1.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
app1.list \

OBJCOPY_HEX += \
app1.hex \

OBJCOPY_BIN += \
app1.bin \


# All Target
all: app1.elf secondary-outputs

# Tool invocations
app1.elf: $(OBJS) $(USER_OBJS) C:\Users\pramo\STM32CubeIDE\workspace_1.3.0\app1\STM32F429ZITX_FLASH.ld
	arm-none-eabi-gcc -o "app1.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\pramo\STM32CubeIDE\workspace_1.3.0\app1\STM32F429ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="app1.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

app1.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "app1.list"
	@echo 'Finished building: $@'
	@echo ' '

app1.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "app1.hex"
	@echo 'Finished building: $@'
	@echo ' '

app1.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "app1.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
