################################################################################
# MRS Version: 3.0.0
# Automatically-generated file. Do not edit!
################################################################################
-include ../makefile.init

RM := rm -rf
FLAGS_C :=  -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Debug" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Core" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/User" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Peripheral/inc" -std=gnu99
FLAGS_C_FILE := .compile_c_flags

FLAGS_CPP :=  -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -std=gnu++11 -fabi-version=0
FLAGS_CPP_FILE := .compile_cpp_flags

FLAGS_ASM :=  -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -x assembler-with-cpp -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Startup"
FLAGS_ASM_FILE := .compile_asm_flags

FLAGS_LD:=  -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:\Users\josev\OneDrive\Documents\KiCad\projects\HalfLifePCB\Keychain\Firmware\Charlieplex-test\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Charlieplex-test.map" --specs=nano.specs --specs=nosys.specs -lprintf
FLAGS_LD_FILE := .ld_flags

$(FLAGS_C_FILE): FORCE
	@echo '$(FLAGS_C)' | cmp -s - $@ || echo '$(FLAGS_C)' > $@
$(FLAGS_CPP_FILE): FORCE
	@echo '$(FLAGS_CPP)' | cmp -s - $@ || echo '$(FLAGS_CPP)' > $@
$(FLAGS_ASM_FILE): FORCE
	@echo '$(FLAGS_ASM)' | cmp -s - $@ || echo '$(FLAGS_ASM)' > $@
$(FLAGS_LD_FILE): FORCE
	@echo '$(FLAGS_LD)' | cmp -s - $@ || echo '$(FLAGS_LD)' > $@
.PHONY: FORCE
FORCE:

# All of the sources participating in the build are defined here
-include sources.mk
-include User/subdir.mk
-include Startup/subdir.mk
-include Peripheral/src/subdir.mk
-include Debug/subdir.mk
-include Core/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

SOURCES_LIST := .sources_list
$(SOURCES_LIST): FORCE
	@echo '$(C_SRCS) $(CPP_SRCS) $(S_UPPER_SRCS)' | tr ' ' '\n' | sort > $@.tmp
	@cmp -s $@.tmp $@ || mv $@.tmp $@
	@rm -f $@.tmp

LD_SCRIPTS := c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Ld/Link.ld

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Charlieplex-test.hex \

SECONDARY_LIST += \
Charlieplex-test.lst \

SECONDARY_SIZE += \
Charlieplex-test.siz \


# All Target
all: 
	$(MAKE) --no-print-directory main-build 

main-build: Charlieplex-test.elf secondary-outputs

# Tool invocations
Charlieplex-test.elf: $(OBJS) $(USER_OBJS_ESCAPE) $(SOURCES_LIST) $(FLAGS_LD_FILE) $(LD_SCRIPTS)
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -T "c:\Users\josev\OneDrive\Documents\KiCad\projects\HalfLifePCB\Keychain\Firmware\Charlieplex-test\Ld\Link.ld" -nostartfiles -Xlinker --gc-sections -Wl,-Map,"Charlieplex-test.map" --specs=nano.specs --specs=nosys.specs -o "Charlieplex-test.elf" $(OBJS) $(LIBS) -lprintf
Charlieplex-test.hex: Charlieplex-test.elf
	@	riscv-none-embed-objcopy -O ihex "Charlieplex-test.elf" "Charlieplex-test.hex"
Charlieplex-test.lst: Charlieplex-test.elf
	@	riscv-none-embed-objdump --all-headers --demangle --disassemble -M xw "Charlieplex-test.elf" > "Charlieplex-test.lst"
Charlieplex-test.siz: Charlieplex-test.elf
	riscv-none-embed-size --format=berkeley "Charlieplex-test.elf"

# Other Targets
clean:
	-$(RM) $(DIR_OBJS) $(SECONDARY_FLASH)$(SECONDARY_LIST)$(SECONDARY_SIZE) Charlieplex-test.elf
	-$(RM) $(DIR_EXPANDS) $(CALLGRAPH_DOT)
	-$(RM) $(DIR_DEPS)
	-$(RM) $(FLAGS_C_FILE) $(FLAGS_CPP_FILE) $(FLAGS_ASM_FILE) $(FLAGS_LD_FILE) $(SOURCES_LIST)
secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents

-include ../makefile.targets