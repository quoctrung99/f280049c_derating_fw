################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
app_main/%.obj: ../app_main/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/bin/cl2000" -v28 -ml -mt --cla_support=cla2 --float_support=fpu32 --tmu_support=tmu0 --vcu_support=vcu0 --include_path="F:/derating_f280049c_fw/app_common/app_timer/include" --include_path="C:/ti/c2000/C2000Ware_4_03_00_00/driverlib/f28004x/driverlib" --include_path="F:/derating_f280049c_fw" --include_path="F:/derating_f280049c_fw/app_common/app_debug/include" --include_path="F:/derating_f280049c_fw/app_main/include" --include_path="F:/derating_f280049c_fw/app_common/include" --include_path="C:/ti/ccs1230/ccs/tools/compiler/ti-cgt-c2000_22.6.0.LTS/include" --include_path="C:/ti/c2000/C2000Ware_4_03_00_00/device_support/f28004x/common/include" --include_path="C:/ti/c2000/C2000Ware_4_03_00_00/device_support/f28004x/headers/include" --advice:performance=all --define=_TI_EABI_ --define=_FLASH --define=_DEBUG --define=CLA_DEBUG=1 --define=F28x_DEVICE --define=CPU1 --define=LARGE_MODEL -g --diag_suppress=10063 --diag_suppress=173 --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="app_main/$(basename $(<F)).d_raw" --include_path="F:/derating_f280049c_fw/Debug/syscfg" --obj_directory="app_main" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


