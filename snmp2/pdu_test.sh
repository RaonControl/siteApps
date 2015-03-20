#!/bin/bash

while [ : ]; do  

#on
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget APC:PDU2_Outlet8_R
caget APC:PDU2_Outlet8_W
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "caput ---------------------------------------------------------"
caput APC:PDU2_Outlet8_W 1
sleep 10


#off
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget APC:PDU2_Outlet8_R
caget APC:PDU2_Outlet8_W
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "caput ---------------------------------------------------------"
caput APC:PDU2_Outlet8_W 2
sleep 10
done

