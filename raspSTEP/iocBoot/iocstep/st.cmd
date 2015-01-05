#!../../bin/linux-arm/step

## You may have to change step to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/step.dbd"
step_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=piHost")
dbLoadRecords("db/step.db")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
seq seqStep
