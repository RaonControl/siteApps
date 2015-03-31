#!/bin/bash
#
# Shell  : raon_ioc.bash
# Author : Jeong Han Lee
# email  : jhlee@ibs.re.kr
# Date   : Tuesday, March 31 09:45:04 KST 2015
# version : 0.0.1
#
#   * Requirements
#
#     RAON EPICS environmental script must be exectued before this script
#     In current envrionemt, for EPICS 3.14.12.5, execute the following
#
#     $ . ~/epics/R3.14.12.5/setEpicsEnv.sh
#     $ cd ${RAON_SITEAPPS}
#     # bash scripts/raon_ioc.bash "keithley6514" 
#    
#     It can start the IOC within the SCREEN session, 
#     -- if the same ioc screen is running, attach to it
#     -- if no ioc screen is running, create and attach to it
#
#     one can check the screen via 
#     $ screen -ls
#
#
#  - 0.0.1  Tuesday, March 31 09:45:25 KST 2015
#           * created
#

this_script_name=`basename $0`
LOGDATE=`date +%Y.%m.%d.%H:%M`
host_name=${HOSTNAME}

# This tells bash that it should exit the script if any statement returns a non-true return value. 
#set -e
#
# This will exit your script if you try to use an uninitialised variable
#set -u

# default_version="3.14.12.5"

goApps() {
    cd ${RAON_SITEAPPS}
    cd $1
}

goIoc() {
    goApps $1
    cd iocBoot/ioc$1
}

ioc_name="$1"
 
case "$ioc_name" in
    "")
	echo "">&2
        echo "usage: $0 <IOC name>" >&2
        echo >&2
        echo "  IOC name : example " >&2
	echo ""
        echo "       $0 keithley6514 ">&2
        echo "       $0 snmp2 ">&2
        echo ""
        echo >&2
	exit 0
        ;;
    *)
	goIoc ${ioc_name}
	echo $PWD
	CHECKPLAT=$(eval screen -ls |grep ${ioc_name})
	if [ -z "$CHECKPLAT" ] ; then
#    echo "No ${ioc_name} IOC on $HOSTNAME, executing......"
	    screen -fn -S ${ioc_name} -L -c ${RAON_SITEAPPS}/scripts/ioc_screenrc -t ${ioc_name} ./st.cmd
	else
	    echo "${ioc_name} IOC is running o $HOSTNAME, attaching ...."
	    screen -x $ioc_name
	fi

	;;

esac




exit 0
