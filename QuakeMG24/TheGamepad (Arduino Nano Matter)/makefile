################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/ff/subdir.mk
-include src/subdir.mk
-include gecko_sdk_4.4.3/platform/service/system/src/subdir.mk
-include gecko_sdk_4.4.3/platform/service/device_init/src/subdir.mk
-include gecko_sdk_4.4.3/platform/emlib/src/subdir.mk
-include gecko_sdk_4.4.3/platform/common/toolchain/src/subdir.mk
-include gecko_sdk_4.4.3/platform/common/src/subdir.mk
-include gecko_sdk_4.4.3/platform/Device/SiliconLabs/MGM24/Source/subdir.mk
-include autogen/subdir.mk
-include Quake/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := QuakeMG24
BUILD_ARTIFACT_EXTENSION := axf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: QuakeMG24.axf

# Tool invocations
QuakeMG24.axf: $(OBJS) $(USER_OBJS) makefile objects.mk $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GNU ARM C Linker'
	arm-none-eabi-gcc -g -gdwarf-2 -mcpu=cortex-m33 -mthumb -T "C:\Users\niwrachi\Documents\GitHub\SDLQuake\SDLQuake\QuakeMG24\linkerfile.ld" -Wl,--no-warn-rwx-segments -Wl,--wrap=malloc -Wl,--wrap=realloc -Wl,--wrap=calloc -Wl,--wrap=free -Xlinker --gc-sections -Xlinker -Map="QuakeMG24.map" -mfpu=fpv5-sp-d16 -mfloat-abi=hard --specs=nano.specs -o QuakeMG24.axf -Wl,--start-group "./src/ff/ff.o" "./src/ff/mmc_spi.o" "./src/audio.o" "./src/display.o" "./src/dynMemWrapper.o" "./src/extMemory.o" "./src/font8x8.o" "./src/graphics.o" "./src/interleavedSpiFlash.o" "./src/keyboard.o" "./src/main.o" "./src/printf.o" "./src/sharedUsart.o" "./gecko_sdk_4.4.3/platform/service/system/src/sl_system_init.o" "./gecko_sdk_4.4.3/platform/service/system/src/sl_system_process_action.o" "./gecko_sdk_4.4.3/platform/service/device_init/src/sl_device_init_dcdc_s2.o" "./gecko_sdk_4.4.3/platform/service/device_init/src/sl_device_init_emu_s2.o" "./gecko_sdk_4.4.3/platform/service/device_init/src/sl_device_init_hfxo_mgm24.o" "./gecko_sdk_4.4.3/platform/service/device_init/src/sl_device_init_nvic.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_cmu.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_core.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_emu.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_gpio.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_msc.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_system.o" "./gecko_sdk_4.4.3/platform/common/toolchain/src/sl_memory.o" "./gecko_sdk_4.4.3/platform/common/src/sl_assert.o" "./gecko_sdk_4.4.3/platform/common/src/sl_syscalls.o" "./gecko_sdk_4.4.3/platform/Device/SiliconLabs/MGM24/Source/startup_mgm24.o" "./gecko_sdk_4.4.3/platform/Device/SiliconLabs/MGM24/Source/system_mgm24.o" "./autogen/sl_device_init_clocks.o" "./autogen/sl_event_handler.o" "./Quake/cd_null.o" "./Quake/chase.o" "./Quake/cl_demo.o" "./Quake/cl_input.o" "./Quake/cl_main.o" "./Quake/cl_parse.o" "./Quake/cl_tent.o" "./Quake/cmd.o" "./Quake/common.o" "./Quake/console.o" "./Quake/cvar.o" "./Quake/d_edge.o" "./Quake/d_fill.o" "./Quake/d_init.o" "./Quake/d_modech.o" "./Quake/d_part.o" "./Quake/d_polyse.o" "./Quake/d_scan.o" "./Quake/d_sky.o" "./Quake/d_sprite.o" "./Quake/d_surf.o" "./Quake/d_vars.o" "./Quake/d_zpoint.o" "./Quake/debug.o" "./Quake/draw.o" "./Quake/extMemoryWin32.o" "./Quake/field_getters_setters.o" "./Quake/field_specific_getters_setters.o" "./Quake/host.o" "./Quake/host_cmd.o" "./Quake/internalFlash.o" "./Quake/keys.o" "./Quake/mathlib.o" "./Quake/menu.o" "./Quake/model.o" "./Quake/net_loop.o" "./Quake/net_main.o" "./Quake/net_none.o" "./Quake/net_vcr.o" "./Quake/nonintel.o" "./Quake/pr_cmds.o" "./Quake/pr_edict.o" "./Quake/pr_exec.o" "./Quake/quakeProgs.o" "./Quake/r_aclip.o" "./Quake/r_alias.o" "./Quake/r_bsp.o" "./Quake/r_draw.o" "./Quake/r_edge.o" "./Quake/r_efrag.o" "./Quake/r_light.o" "./Quake/r_main.o" "./Quake/r_misc.o" "./Quake/r_part.o" "./Quake/r_sky.o" "./Quake/r_sprite.o" "./Quake/r_surf.o" "./Quake/r_vars.o" "./Quake/sbar.o" "./Quake/screen.o" "./Quake/snd_dma.o" "./Quake/snd_mem.o" "./Quake/snd_mix.o" "./Quake/snd_sdl.o" "./Quake/sv_main.o" "./Quake/sv_move.o" "./Quake/sv_phys.o" "./Quake/sv_user.o" "./Quake/tabmath.o" "./Quake/tempBuffer.o" "./Quake/vid_sdl.o" "./Quake/view.o" "./Quake/wad.o" "./Quake/world.o" "./Quake/z_zone.o" -lgcc -lc -lm -lnosys "./gecko_sdk_4.4.3/platform/service/device_init/src/sl_device_init_dpll_s2.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_eusart.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_ldma.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_prs.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_timer.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_usart.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_vdac.o" "./gecko_sdk_4.4.3/platform/emlib/src/em_iadc.o" -Wl,--end-group -Wl,--start-group -lgcc -lc -lnosys -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

	@echo 'Building out file: QuakeMG24.out'
	arm-none-eabi-objcopy "QuakeMG24.axf" "QuakeMG24.out"
	@echo ' '

	@echo 'Building hex file: QuakeMG24.hex'
	arm-none-eabi-objcopy -O ihex "QuakeMG24.axf" "QuakeMG24.hex"
	@echo ' '

	@echo 'Building bin file: QuakeMG24.bin'
	arm-none-eabi-objcopy -O binary "QuakeMG24.axf" "QuakeMG24.bin"
	@echo ' '

	@echo 'Building s37 file: QuakeMG24.s37'
	arm-none-eabi-objcopy -O srec "QuakeMG24.axf" "QuakeMG24.s37"
	@echo ' '

	@echo 'Running size tool'
	arm-none-eabi-size "QuakeMG24.axf" -A
	@echo ' '

# Other Targets
clean:
	-@$(foreach FILE, $(EXECUTABLES), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(OBJS), $(shell $(RM) $(FILE)) )
	-@$(foreach FILE, $(C_DEPS), $(shell $(RM) $(FILE)) )
	-$(RM) QuakeMG24.axf
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
