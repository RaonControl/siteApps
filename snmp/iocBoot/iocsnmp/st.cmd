#!../../bin/linux-x86_64/snmp

## You may have to change snmp to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}


##devSnmpSetSnmpVersion("10.1.5.122","SNMP_VERSION_1")
##devSnmpSetSnmpVersion("10.1.5.142","SNMP_VERSION_2")
devSnmpSetSnmpVersion("10.1.4.184","SNMP_VERSION_1")
devSnmpSetSnmpVersion("10.1.4.182","SNMP_VERSION_1")


epicsEnvSet("W", "WIENER-CRATE-MIB::")
epicsEnvSet("PO", "PowerNet-MIB::")
epicsEnvSet("PR", "Printer-MIB::")
epicsEnvSet("JM", "Job-Monitoring-MIB::")
epicsEnvSet("SMI", "SNMPv2-SMI::")
epicsEnvSet("RFC", "RFC1213-MIB::")
epicsEnvSet("XM", "XEROX-SERVICE-MONITORING-MIB::")
epicsEnvSet("CM1", "admin")
epicsEnvSet("CM2", "public")
epicsEnvSet("WIENER", "10.1.5.122")
epicsEnvSet("PDU", "10.1.5.141")
epicsEnvSet("XEROX", "10.1.4.182")
epicsEnvSet("KYOCERA", "10.1.4.184")



## Register all support components
dbLoadDatabase "dbd/snmp.dbd"
snmp_registerRecordDeviceDriver pdbbase

## Load record instances
dbLoadRecords("db/printer.vdb","USER=mijoy0909Host")





cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
