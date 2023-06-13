################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./app_common/app_debug/app_debug.obj" \
"./app_common/app_timer/app_timer_sys.obj" \
"./app_main/app_adc.obj" \
"./app_main/app_config.obj" \
"./app_main/app_derating.obj" \
"./app_main/app_pwm.obj" \
"./app_main/main.obj" \
"./f280049c_idf/device.obj" \
"./f280049c_idf/f28004x_adc.obj" \
"./f280049c_idf/f28004x_codestartbranch.obj" \
"./f280049c_idf/f28004x_cputimers.obj" \
"./f280049c_idf/f28004x_defaultisr.obj" \
"./f280049c_idf/f28004x_globalvariabledefs.obj" \
"./f280049c_idf/f28004x_gpio.obj" \
"./f280049c_idf/f28004x_piectrl.obj" \
"./f280049c_idf/f28004x_pievect.obj" \
"./f280049c_idf/f28004x_sysctrl.obj" \
"./f280049c_idf/f28004x_usdelay.obj" \
"../280049C_RAM_lnk.cmd" \
"C:/ti/c2000/C2000Ware_4_03_00_00/driverlib/f28004x/driverlib/ccs/Debug/driverlib.lib" \
$(GEN_CMDS__FLAG) \
-llibc.a \
-l"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib/rts2800_fpu32.lib" \
-l"C:/ti/c2000/C2000Ware_4_03_00_00/device_support/f28004x/headers/cmd/f28004x_headers_nonbios.cmd" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include app_common/app_debug/subdir_vars.mk
-include app_common/app_timer/subdir_vars.mk
-include app_main/subdir_vars.mk
-include f280049c_idf/subdir_vars.mk
-include subdir_rules.mk
-include app_common/app_debug/subdir_rules.mk
-include app_common/app_timer/subdir_rules.mk
-include app_main/subdir_rules.mk
-include f280049c_idf/subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(SV7A_DEPS)),)
-include $(SV7A_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
derating_fw.out \

EXE_OUTPUTS__QUOTED += \
"derating_fw.out" \


# All Target
all: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@$(MAKE) --no-print-directory -Onone "derating_fw.out"

# Tool invocations
derating_fw.out: $(OBJS) $(CMD_SRCS) $(LIB_SRCS) $(GEN_CMDS)
	@echo 'Building target: "$@"'
	@echo 'Invoking: C2000 Linker'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --advice:performance=all --define=_TI_EABI_ --define=_FLASH --define=_DEBUG --define=CLA_DEBUG=1 --define=F28x_DEVICE --define=CPU1 --define=LARGE_MODEL -g --diag_suppress=10063 --diag_suppress=173 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi -z -m"derating_fw.map" --heap_size=1024 --stack_size=0x350 --warn_sections -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/lib" -i"C:/ti/c2000/C2000Ware_4_03_00_00/device_support/f28004x/common/cmd" -i"C:/ti/c2000/C2000Ware_4_03_00_00/device_support/f28004x/headers/cmd" -i"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --reread_libs --diag_wrap=off --display_error_number --xml_link_info="derating_fw_linkInfo.xml" --entry_point=code_start --rom_model -o "derating_fw.out" $(ORDERED_OBJS)
	@echo 'Finished building target: "$@"'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)
	-$(RM) "app_common\app_debug\app_debug.obj" "app_common\app_timer\app_timer_sys.obj" "app_main\app_adc.obj" "app_main\app_config.obj" "app_main\app_derating.obj" "app_main\app_pwm.obj" "app_main\main.obj" "f280049c_idf\device.obj" "f280049c_idf\f28004x_adc.obj" "f280049c_idf\f28004x_codestartbranch.obj" "f280049c_idf\f28004x_cputimers.obj" "f280049c_idf\f28004x_defaultisr.obj" "f280049c_idf\f28004x_globalvariabledefs.obj" "f280049c_idf\f28004x_gpio.obj" "f280049c_idf\f28004x_piectrl.obj" "f280049c_idf\f28004x_pievect.obj" "f280049c_idf\f28004x_sysctrl.obj" "f280049c_idf\f28004x_usdelay.obj" 
	-$(RM) "app_common\app_debug\app_debug.d" "app_common\app_timer\app_timer_sys.d" "app_main\app_adc.d" "app_main\app_config.d" "app_main\app_derating.d" "app_main\app_pwm.d" "app_main\main.d" "f280049c_idf\device.d" "f280049c_idf\f28004x_adc.d" "f280049c_idf\f28004x_cputimers.d" "f280049c_idf\f28004x_defaultisr.d" "f280049c_idf\f28004x_globalvariabledefs.d" "f280049c_idf\f28004x_gpio.d" "f280049c_idf\f28004x_piectrl.d" "f280049c_idf\f28004x_pievect.d" "f280049c_idf\f28004x_sysctrl.d" 
	-$(RM) "f280049c_idf\f28004x_codestartbranch.d" "f280049c_idf\f28004x_usdelay.d" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

