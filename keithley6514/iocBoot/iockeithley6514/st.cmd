#!../../bin/linux-x86_64/keithley6514

## You may have to change keithley6514 to something else
## everywhere it appears in this file

< envPaths

epicsEnvSet "STREAM_PROTOCOL_PATH" "$(TOP)/db" 
epicsEnvSet "SYS" "$(SYS=ECR11)"
epicsEnvSet "SUBSYS" "$(SUBSYS=Diag)"
epicsEnvSet "DEV" "$(DEV=FC01)"
epicsEnvSet "TTY" "$(TTY=/dev/ttyUSB0)"

cd ${TOP}
## Register all support components
dbLoadDatabase "dbd/keithley6514.dbd"
keithley6514_registerRecordDeviceDriver pdbbase

# drvAsynSerialPortConfigure("portName","ttyName",priority,noAutoConnect,noEos)
# asynSetOption("portName",addr,"key","value")

# priority      - Priority at which the asyn I/O thread will run. If this is zero or missing then epicsThreadPriorityMedium is used.
# noAutoConnect - Zero or missing indicates that portThread should automatically connect. Non-zero if explicit connect command must be issued.
# noEos         - Zero or missing indicates that the input routines should search for the end-of-string character(s), if any. Non-zero inhibits end-of-string search.
# addr          - This argument is ignored since serial devices are configured with multiDevice=0.

drvAsynSerialPortConfigure("L0","$(TTY)",0,0,0)
asynSetOption("L0", -1, "baud", "57600") 
asynSetOption("L0", -1, "bits", "8") 
asynSetOption("L0", -1, "parity", "none") 
asynSetOption("L0", -1, "stop", "1") 
#
# Ignore DTR / DCD : Y
#
asynSetOption("L0", -1, "clocal", "Y") 
#
# Ignore CTS / RTS : N - 6514 doesn't support HW handshaking
#
asynSetOption("L0", -1, "crtscts", "N") 
#asynOctetSetInputEos("L0", -1, "\n") 
#asynOctetSetOutputEos("L0", -1, "\n") 
#asynSetTraceIOMask("L0",-1,0x2) 
#asynSetTraceMask("L0",-1,0x9) 


## Load record instances
#dbLoadRecords("db/xxx.db","user=jhleeHost")
dbLoadRecords("db/devkeithley6514.db","SYS=$(SYS),SUBSYS=$(SUBSYS),DEV=$(DEV), PORT=L0,A=0") 

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=jhleeHost"
