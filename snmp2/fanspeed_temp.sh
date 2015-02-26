#!/bin/bash

while [ : ]; do  
#++
for i in {1200..3600..100};do
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
echo "caget_FRIB ----------------------------------------------------"
caget WIENER:MainPower_FRIB
caget WIENER:FanAirTemp_FRIB
caget WIENER:FanNominalSpeed_FRIB
echo "caget_Async v2c -----------------------------------------------"
caget WIENER:MainPower_v2c
caget WIENER:FanairTemp_v2c
caget WIENER:FanNominalSpeed_v2c
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::fanAirTemperature.0
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0
echo "snmpset -------------------------------------------------------"
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 300
done

#--
for i in {3500..1300..100};do
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
echo "caget_FRIB ----------------------------------------------------"
caget WIENER:MainPower_FRIB
caget WIENER:FanAirTemp_FRIB
caget WIENER:FanNominalSpeed_FRIB
echo "caget_Async v2c -----------------------------------------------"
caget WIENER:MainPower_v2c
caget WIENER:FanairTemp_v2c
caget WIENER:FanNominalSpeed_v2c
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::fanAirTemperature.0
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0
echo "snmpset -------------------------------------------------------"
# caget mijoy0909Host:MainPower
# caget mijoy0909Host:CrateStatus
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 300
done
done