#!../../bin/linux-x86_64/snmpTest

## You may have to change snmpTest to something else
## everywhere it appears in this file

< envPaths

cd "${TOP}"

## Register all support components
dbLoadDatabase "dbd/snmpTest.dbd"
snmpTest_registerRecordDeviceDriver pdbbase

## Load record instances
#dbLoadRecords("db/xxx.db","user=mijoy0909Host")
dbLoadRecords("db/xerox.vdb", "HOST=10.1.4.182, COM=public, V2C=SNMP_VERSION_2c, PR=Printer-MIB::")
dbLoadRecords("db/timestamp.vdb", "S=SNMPIOC")
dbLoadRecords "db/alive.db", "P=aliveEx:,RHOST=10.1.4.191"

cd "${TOP}/iocBoot/${IOC}"
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
