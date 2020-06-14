################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
%.obj: ../%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/darkerknight/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/darkerknight/workspace_v10/test101" --include_path="/home/darkerknight/workspace_v10/test101/Debug" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="/home/darkerknight/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="$(basename $(<F)).d_raw" --include_path="/home/darkerknight/workspace_v10/test101/Debug/syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '

build-1356646175: ../test101.syscfg
	@echo 'Building file: "$<"'
	@echo 'Invoking: SysConfig'
	"/home/darkerknight/ti/ccs1000/ccs/utils/sysconfig_1.4.0/sysconfig_cli.sh" -s "/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/.metadata/product.json" -o "syscfg" "$<"
	@echo 'Finished building: "$<"'
	@echo ' '

syscfg/ti_drivers_config.c: build-1356646175 ../test101.syscfg
syscfg/ti_drivers_config.h: build-1356646175
syscfg/syscfg_c.rov.xs: build-1356646175
syscfg/: build-1356646175

syscfg/%.obj: ./syscfg/%.c $(GEN_OPTS) | $(GEN_FILES) $(GEN_MISC_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: ARM Compiler'
	"/home/darkerknight/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/bin/armcl" -mv7M4 --code_state=16 --float_support=FPv4SPD16 -me --include_path="/home/darkerknight/workspace_v10/test101" --include_path="/home/darkerknight/workspace_v10/test101/Debug" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source/third_party/CMSIS/Include" --include_path="/home/darkerknight/ti/simplelink_msp432p4_sdk_3_40_01_02/source/ti/posix/ccs" --include_path="/home/darkerknight/ti/ccs1000/ccs/tools/compiler/ti-cgt-arm_20.2.0.LTS/include" --advice:power=none -g --diag_warning=225 --diag_warning=255 --diag_wrap=off --display_error_number --gen_func_subsections=on --preproc_with_compile --preproc_dependency="syscfg/$(basename $(<F)).d_raw" --include_path="/home/darkerknight/workspace_v10/test101/Debug/syscfg" --obj_directory="syscfg" $(GEN_OPTS__FLAG) "$(shell echo $<)"
	@echo 'Finished building: "$<"'
	@echo ' '


