#!/bin/bash

while [ : ]; do  
#++
for i in {1200..3600..100};do
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
caget mijoy0909Host:MainPower
# caget mijoy0909Host:CrateStatus
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 600
done

#--
for i in {3500..1300..100};do
echo "***************************************************************"
echo `date`  
echo "---------------------------------------------------------------"
caget mijoy0909Host:MainPower
# caget mijoy0909Host:CrateStatus
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $i
# echo $i
sleep 600
done
done