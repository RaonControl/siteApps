#!../../bin/linux-x86_64/rtp

## You may have to change rtp to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/rtp.dbd"
rtp_registerRecordDeviceDriver pdbbase

#drvAsynIPPortConfigure("portName","hostInfo(e.g. IP:port protocol", priority, noAutoConnect, noProcessEos)
#drvAsynIPPortConfigure("RTPDevice","192.168.10.100:6001 TCP", 0, 0, 0)

## Load record instances
#dbLoadRecords("db/xxx.db","user=sileeHost")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=sileeHost"
