#!/bin/bash

while [ : ]; do  
#++
for i in {1200..3600..100};do
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_CrateStatus WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
echo "caput ---------------------------------------------------------"
caput WIENER:CRATE3_FanNominalSpeed_W.RVAL $i
# echo $i
sleep 300
done

#--
for i in {3500..1300..100};do
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_CrateStatus WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
echo "caput ---------------------------------------------------------"
caput WIENER:CRATE3_FanNominalSpeed_W.RVAL $i
# echo $i
sleep 300
done
done