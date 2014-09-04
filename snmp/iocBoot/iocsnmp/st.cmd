#!../../bin/linux-x86_64/snmp

## You may have to change snmp to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}


##devSnmpSetSnmpVersion("10.1.5.122","SNMP_VERSION_1")
##devSnmpSetSnmpVersion("10.1.5.142","SNMP_VERSION_2")


epicsEnvSet("W", "WIENER-CRATE-MIB::")
epicsEnvSet("P", "PowerNet-MIB::")
epicsEnvSet("XK", "Printer-MIB::")
epicsEnvSet("C", "admin")
epicsEnvSet("p", "public")
epicsEnvSet("WIENER", "10.1.5.122")
epicsEnvSet("PDU", "10.1.5.142")
epicsEnvSet("XEROX", "10.1.4.182")
epicsEnvSet("KYOCERA", "10.1.4.184")



## Register all support components
dbLoadDatabase "dbd/snmp.dbd"
snmp_registerRecordDeviceDriver pdbbase

## Load record instances
dbLoadRecords("db/snmp.vdb","USER=mijoy0909Host")





cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
