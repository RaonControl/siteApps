#!../../bin/linux-x86_64/lsplc

## You may have to change lsplc to something else
## everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/lsplc.dbd"
lsplc_registerRecordDeviceDriver pdbbase

drvAsynIPPortConfigure("StepMTst","10.1.5.206:502",0,0,1)
modbusInterposeConfig("StepMTst",0,5000,0)

# The LSPLC - XGT - modbusTCP, Function code
# Read 32 bits, Discret Input.  Function code=2.   

#drvModbusAsynConfigure("1", "2",3 ,4,"octal value", 6, 7 ,8,9)
#-> PLC PXXXXX -> Hexa value, octal value convert to Hexa, refer LS-PLC XGK-EFMT Memory Address
# Address = 1XXXX, Response Length = 2000 Coils(2000bits)
drvModbusAsynConfigure("Step_Motor_CIn_Bit",   "StepMTst", 0, 1,  00020, 0007,    0,  100, "Modicon")

# Write 1 bit.  Function code=5.
# Address = 0XXXX, Response Length = 1 Coil(1bits)
#drvModbusAsynConfigure("Step_Motor_BOut",  "StepMTst", 0, 5,  00300, 0007,    0,  1, "Modicon")
#drvModbusAsynConfigure("Step_Motor_BOut",  "StepMTst", 0, 5,  0x0780, 0007,    0,  1, "Modicon")
drvModbusAsynConfigure("Step_Motor_BOut",  "StepMTst", 0, 5,  0x0100,  100,    0,  1, "Modicon")





# Read 8 words (128 bits). Read Input Registers.  Function code=4.
# Address = 3XXXX, Response Length = 125 Registers(1600bits)
# drvModbusAsynConfigure("Step_Motor_WIn",  "StepMTst", 0, 4, 020500, 010,    0, 100, "Modicon")









# Write 8 words (128 bits).  Function code=6.
# Address = 4XXXX, Response Length = 1 Register (1Register, 8bits)
#drvModbusAsynConfigure("Step_Motor_WOut", "StepMTst", 0, 6, 040500, 010,    0,  1, "Modicon")
#drvModbusAsynConfigure("Step_Motor_WOut", "StepMTst", 0, 6, 0x1F40, 010,    0,  1, "Modicon")
# 0 -> P0800
##drvModbusAsynConfigure("Step_Motor_WOut", "StepMTst", 0, 6, 10, 010,    0,  1, "Modicon")



# drvModbusAsynConfigure("portName", "tcpPortName", slaveAddress, modbusFunction, modbusStartAddress, modbusLength, dataType, pollMsec, "plcType")
## drvModbusAsynConfigure("A0_Out_Word", "sim1", 0, 16, 100, 10, 7, 1, "Simulator")

# Write Analog Out (UNINT). Function code= 16.

drvModbusAsynConfigure("Step_Motor_AOut", "StepMTst", 0, 16, 0, 100,   7,  1, "Modicon")

# Write Analog Input (UNINT). Function code= 16.

drvModbusAsynConfigure("Step_Motor_AIn", "StepMTst", 0, 16, 0, 100,   7,  1, "Modicon")



# Write Analog Out (Float).

drvModbusAsynConfigure("Step_Motor_FOut", "StepMTst", 0, 16, 100, 100,   7,  1, "Modicon")

# Write Analog Input (Float).

drvModbusAsynConfigure("Step_Motor_FIn", "StepMTst", 0, 16, 100, 100,   7,  1, "Modicon")



 

# Enable ASYN_TRACEIO_HEX on modbus server
asynSetTraceIOMask("Step_Motor_CIn_Bit",0,4)

# Dump up to 512 bytes in asynTrace
asynSetTraceIOTruncateSize("Step_Motor_CIn_Bit",0,512)

cd "${TOP}/iocBoot/${IOC}"
dbLoadTemplate("StepMTst_pre.substitutions")

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=ctrluserHost"
