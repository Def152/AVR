################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../main.c \
../mb.c \
../mbcrc.c \
../mbfunccoils.c \
../mbfuncdiag.c \
../mbfuncdisc.c \
../mbfuncholding.c \
../mbfuncinput.c \
../mbfuncother.c \
../mbrtu.c \
../mbutils.c \
../portevent.c \
../portserial.c \
../porttimer.c 

OBJS += \
./main.o \
./mb.o \
./mbcrc.o \
./mbfunccoils.o \
./mbfuncdiag.o \
./mbfuncdisc.o \
./mbfuncholding.o \
./mbfuncinput.o \
./mbfuncother.o \
./mbrtu.o \
./mbutils.o \
./portevent.o \
./portserial.o \
./porttimer.o 

C_DEPS += \
./main.d \
./mb.d \
./mbcrc.d \
./mbfunccoils.d \
./mbfuncdiag.d \
./mbfuncdisc.d \
./mbfuncholding.d \
./mbfuncinput.d \
./mbfuncother.d \
./mbrtu.d \
./mbutils.d \
./portevent.d \
./portserial.d \
./porttimer.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega88p -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


