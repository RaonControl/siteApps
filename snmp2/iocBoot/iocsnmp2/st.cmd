#!../../bin/linux-x86_64/snmp2

## You may have to change snmp2 to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

## Register all support components
dbLoadDatabase "dbd/snmp2.dbd"
snmp2_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=mijoy0909Host")
#dbLoadRecords("db/snmp2.vdb","USER=mijoy0909Host")
#dbLoadRecords("db/snmp.vdb","USER=mijoy0909Host")
dbLoadRecords("db/snmp_set.vdb", "USER=mijoy0909Host")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
