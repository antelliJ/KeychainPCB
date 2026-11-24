################################################################################
# MRS Version: 3.0.0
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Debug/debug.c 

C_DEPS += \
./Debug/debug.d 

OBJS += \
./Debug/debug.o 

DIR_OBJS += \
./Debug/*.o \

DIR_DEPS += \
./Debug/*.d \

DIR_EXPANDS += \
./Debug/*.234r.expand \


# Each subdirectory must supply rules for building sources it contributes
Debug/%.o: ../Debug/%.c $(FLAGS_C_FILE)
	@	riscv-none-embed-gcc -march=rv32ecxw -mabi=ilp32e -msmall-data-limit=0 -msave-restore -fmax-errors=20 -Os -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -fno-common -Wunused -Wuninitialized -g -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Debug" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Core" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/User" -I"c:/Users/josev/OneDrive/Documents/KiCad/projects/HalfLifePCB/Keychain/Firmware/Charlieplex-test/Peripheral/inc" -std=gnu99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -c -o "$@" "$<"

