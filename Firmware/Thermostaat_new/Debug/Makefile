################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS :=  \
../Headers \
../Headers/bitmaps \
../Headers/fonts


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../adc.c \
../display.c \
../ds1307.c \
../glcdFunctions.c \
../io.c \
../main.c \
../onewire.c \
../progressbar.c \
../tempsensor.c \
../timer.c \
../uart.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
adc.o \
display.o \
ds1307.o \
glcdFunctions.o \
io.o \
main.o \
onewire.o \
progressbar.o \
tempsensor.o \
timer.o \
uart.o


OBJS_AS_ARGS +=  \
adc.o \
display.o \
ds1307.o \
glcdFunctions.o \
io.o \
main.o \
onewire.o \
progressbar.o \
tempsensor.o \
timer.o \
uart.o


C_DEPS +=  \
adc.d \
display.d \
ds1307.d \
glcdFunctions.d \
io.d \
main.d \
onewire.d \
progressbar.d \
tempsensor.d \
timer.d \
uart.d


C_DEPS_AS_ARGS +=  \
adc.d \
display.d \
ds1307.d \
glcdFunctions.d \
io.d \
main.d \
onewire.d \
progressbar.d \
tempsensor.d \
timer.d \
uart.d


OUTPUT_FILE_PATH +=Thermostaat_new.elf

OUTPUT_FILE_PATH_AS_ARGS +=Thermostaat_new.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

# AVR32/GNU C Compiler























./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-gcc.exe$(QUOTE)  -funsigned-char -funsigned-bitfields -DF_CPU=20000000  -O1 -fpack-struct -fshort-enums -g2 -Wall -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)"  -mmcu=atmega644  -o"$@" "$<" 
	@echo Finished building: $<



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU C Linker
	$(QUOTE)C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="Thermostaat_new.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group  -mmcu=atmega644  
	@echo Finished building target: $@
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature  "Thermostaat_new.elf" "Thermostaat_new.hex"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "Thermostaat_new.elf" "Thermostaat_new.eep" || exit 0
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-objdump.exe" -h -S "Thermostaat_new.elf" > "Thermostaat_new.lss"
	"C:\Program Files (x86)\Atmel\Atmel Studio 6.0\extensions\Atmel\AVRGCC\3.3.2.31\AVRToolchain\bin\avr-size.exe" -C --mcu=atmega644  "Thermostaat_new.elf"
	




# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS)$(C_DEPS_AS_ARGS) $(EXECUTABLES) 
	rm -rf "Thermostaat_new.hex" "Thermostaat_new.lss" "Thermostaat_new.eep" "Thermostaat_new.map"
	