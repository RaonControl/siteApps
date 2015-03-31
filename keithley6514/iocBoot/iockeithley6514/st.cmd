#!../../bin/linux-x86_64/keithley6514

## You may have to change keithley6514 to something else
## everywhere it appears in this file

< envPaths

epicsEnvSet "STREAM_PROTOCOL_PATH" "$(TOP)/db" 
epicsEnvSet "SYS" "$(SYS=ECR11)"
epicsEnvSet "SUBSYS" "$(SUBSYS=Diag)"
epicsEnvSet "DEV" "$(DEV=FC01)"

#epicsEnvSet "EPICS_CA_SERVER_PORT" "15065"

cd ${TOP}
## Register all support components
dbLoadDatabase "dbd/keithley6514.dbd"
keithley6514_registerRecordDeviceDriver pdbbase

drvAsynIPPortConfigure("L0", "192.168.1.140:4013", 0, 0, 0)

## Load record instances
dbLoadRecords("db/devkeithley6514.db","SYS=$(SYS),SUBSYS=$(SUBSYS),DEV=$(DEV), PORT=L0,A=0") 
dbLoadRecords("db/dbTimeStamp.db", "SYS=$(SYS),SUBSYS=$(SUBSYS),DEV=$(DEV)")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=jhleeHost"
