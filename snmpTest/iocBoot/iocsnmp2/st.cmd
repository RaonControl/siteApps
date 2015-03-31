#!../../bin/linux-x86_64/snmp2

## You may have to change snmp2 to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

#epicsEnvSet("MIBDIRS", "${EPICS_PATH}/siteLibs/snmpLib/mibs")

## Register all support components
dbLoadDatabase "dbd/snmp2.dbd"
snmp2_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=mijoy0909Host")
dbLoadRecords("db/xerox.vdb", "HOST=10.1.4.182, COM=public, V2C=SNMP_VERSION_2c, PR=Printer-MIB::")
#dbLoadRecords("db/kyocera.vdb", "HOST=10.1.4.184, COM=public, V1=SNMP_VERSION_1, PR=Printer-MIB::")

dbLoadRecords("db/timestamp.vdb", "S=SNMPIOC")

cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
