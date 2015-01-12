#!../../bin/linux-arm/step

## You may have to change step to something else
## everywhere it appears in this file

< /home/pi/epics/R3.14.12.4/siteApps/raspSTEP/iocBoot/iocstep/envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "/home/pi/epics/R3.14.12.4/siteApps/raspSTEP/dbd/step.dbd"
step_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=piHost")
dbLoadRecords("/home/pi/epics/R3.14.12.4/siteApps/raspSTEP/db/step.db")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
seq seqStep
