#!/bin/bash

while [ : ]; do  
sp1=1100
while [ $sp1 -lt 3700 ] ; do
    # echo $sp1
    let sp1=sp1+100
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $sp1
sleep 600
done
sleep 600

sp2=3600
while [ $sp2 -gt 1100 ] ; do
    # echo $sp2
    let sp2=sp2-100
snmpset -v 3 -u wiener -l authPriv -a MD5 -A MySecret -x DES -X MySecret 10.1.5.123 WIENER-CRATE-MIB::fanNominalSpeed.0 i $sp2
sleep 600
done
sleep 600
done
