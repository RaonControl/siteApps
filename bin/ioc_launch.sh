#!/bin/sh

ioc_name="epics"

. /home/pi/epics/R3.14.12.5/setEpicsEnv.sh 

CHECKPLAT=$(eval screen -ls |grep ${ioc_name})

if [ -z "$CHECKPLAT" ] ; then
    screen -dm -S ${ioc_name} -c ${RAON_SITEAPPS}/bin/ioc_screenrc -t ${ioc_name} sudo ${RAON_SITEAPPS}/raspberry/bin/linux-arm/md5dh14 ${RAON_SITEAPPS}/raspberry/iocBoot/iocRaspberryPi/st.cmd.md5dh14.boot
#else
#
# If everything is fine, we cannot see the exec possibility of this below line command :
#
#    screen -x ${ioc_name}

fi

exit 0
