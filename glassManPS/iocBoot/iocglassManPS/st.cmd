#!../../bin/linux-x86_64/glassManPS

## You may have to change glassManPS to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

epicsEnvSet "STREAM_PROTOCOL_PATH" "../../proto"

## Register all support components
dbLoadDatabase "dbd/glassManPS.dbd"
glassManPS_registerRecordDeviceDriver pdbbase
drvAsynIPPortConfigure("port1", "10.1.5.80:4001", 0, 0, 0)

## Load record instances
#dbLoadRecords("db/xxx.db","user=scwookHost")

#Currently supported PS are et50p40, fj01n120, fj10n12, fj50n024, fj50p024
dbLoadRecords("db/glassManPS.db", "SYS=ECRIS,SUBSYS=Mag,DEV=PS001,PS=fj01n120,P=port1")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=scwookHost"
