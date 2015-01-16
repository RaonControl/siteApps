#!../../bin/linux-x86_64/motor

## You may have to change motor to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/motor.dbd"
motor_registerRecordDeviceDriver pdbbase

drvAsynIPPortConfigure("test","10.5.1.181:22222",0,0,1)

phytronCreateController ("phyMotionPort", "test", 100, 100, 1000)

## Load record instances
#dbLoadRecords("db/xxx.db","user=scwookHost")

dbLoadTemplate "iocBoot/iocmotor/motor.substitutions.phytron"

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=scwookHost"
