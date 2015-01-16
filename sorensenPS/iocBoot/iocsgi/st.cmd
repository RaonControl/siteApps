#!../../bin/linux-x86_64/sgi

## You may have to change sgi to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

epicsEnvSet "STREAM_PROTOCOL_PATH" "../../proto"

## Register all support components
dbLoadDatabase "dbd/sgi.dbd"
sgi_registerRecordDeviceDriver pdbbase

drvAsynIPPortConfigure("test", "10.1.5.80:4010", 0, 0, 0)

## Load record instances
#dbLoadRecords("db/xxx.db","user=scwookHost")
dbLoadRecords("db/sgi.db")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=scwookHost"
