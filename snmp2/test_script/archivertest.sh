#!/bin/bash

x=1

while [ $x ]; do  
#++

for i in {1200..3000..100};do

echo ""
echo "COUNT : $x"
echo ""
x=$(( $x + 1 ))

stat=`caget APC:PDU2_Outlet8_R`
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP

echo "---------------------------------------------------------------"
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_PS_Status WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R WIENER:CRATE3_FanNominalSpeed_W APC:PDU2_Outlet8_R APC:PDU2_Outlet8_W 
echo "caput ---------------------------------------------------------"

case "$stat" in
"APC:PDU2_Outlet8_R             1")
caput APC:PDU2_Outlet8_W 2;;
"APC:PDU2_Outlet8_R             2")
caput APC:PDU2_Outlet8_W 1;;
*)
echo "error";;
esac

caput WIENER:CRATE3_FanNominalSpeed_W $i
sleep 30
done


#--
for i in {2900..1300..100};do

echo ""
echo "COUNT : $x"
echo ""
x=$(( $x + 1 ))

stat=`caget APC:PDU2_Outlet8_R`
echo "***************************************************************"
caget SNMPIOC:TIMESTAMP
echo "---------------------------------------------------------------"
echo "snmpget -------------------------------------------------------"
snmpget -v 1 -c public 10.1.5.123 WIENER-CRATE-MIB::sysMainSwitch.0  WIENER-CRATE-MIB::sysStatus.0  WIENER-CRATE-MIB::fanAirTemperature.0 WIENER-CRATE-MIB::fanNominalSpeed.0
snmpget -v 1 -c public 10.1.5.142 PowerNet-MIB::sPDUOutletCtl.8
echo "---------------------------------------------------------------"
echo "caget ---------------------------------------------------------"
caget WIENER:CRATE3_MainPower_R WIENER:CRATE3_PS_Status WIENER:CRATE3_FanairTemp WIENER:CRATE3_FanNominalSpeed_R WIENER:CRATE3_FanNominalSpeed_W APC:PDU2_Outlet8_R APC:PDU2_Outlet8_W 
echo "caput ---------------------------------------------------------"

case "$stat" in
"APC:PDU2_Outlet8_R             1")
caput APC:PDU2_Outlet8_W 2;;
"APC:PDU2_Outlet8_R             2")
caput APC:PDU2_Outlet8_W 1;;
*)
echo "error";;
esac

caput WIENER:CRATE3_FanNominalSpeed_W $i
sleep 30
done
done
done

