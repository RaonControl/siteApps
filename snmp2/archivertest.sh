#!/bin/bash

while [ : ]; do  
#++
for i in {1200..3000..100};do
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_PS_Status WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R WIENER:CRATE3_FanNominalSpeed_W APC:PDU2_Outlet8_R APC:PDU2_Outlet8_W 
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "caput ---------------------------------------------------------"
caput WIENER:CRATE3_FanNominalSpeed_W $i
caput APC:PDU2_Outlet8_W 1
# echo "snmpset -------------------------------------------------------"
# snmpset -v 3 -u admin -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 60
done

#--
for i in {2900..1300..100};do
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_PS_Status WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R WIENER:CRATE3_FanNominalSpeed_W APC:PDU2_Outlet8_R APC:PDU2_Outlet8_W 
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "caput ---------------------------------------------------------"
caput WIENER:CRATE3_FanNominalSpeed_W $i
caput APC:PDU2_Outlet8_W 2
# echo "snmpset -------------------------------------------------------"
# snmpset -v 3 -u admin -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 60
done
done