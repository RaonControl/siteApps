#!../../bin/linux-x86_64/snmp2

## You may have to change snmp2 to something else
## everywhere it appears in this file

< envPaths

cd ${TOP}

#epicsEnvSet("MIBDIRS", "+$(TOP)/mibs")

## Register all support components
dbLoadDatabase "dbd/snmp2.dbd"
snmp2_registerRecordDeviceDriver pdbbase

#drvSNMPConnInit("10.1.5.142", "qwertyuiop12345", "qwertyuiop12345");
#drvSNMPConnInit("SNMP_VERSION_2c", "10.1.5.142", "public", NULL, NULL);


## Load record instances
#dbLoadRecords("db/xxx.db","user=mijoy0909Host")
dbLoadRecords("db/pdu.vdb", "A=APC, P=PDU2, PO=PowerNet-MIB::")
#dbLoadRecords("db/wiener.vdb", "W=WIENER, WI=WIENER-CRATE-MIB::")


cd ${TOP}/iocBoot/${IOC}
iocInit

## Start any sequence programs
#seq sncxxx,"user=mijoy0909Host"
