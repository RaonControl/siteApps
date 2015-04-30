TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

#=============================
# Build the IOC application

USR_INCLUDES  += -I$(RAON_SITELIBS)/include
USR_DBDFLAGS  += -I$(RAON_SITELIBS)/dbd
USR_INCLUDES  += -I$(EPICS_EXTENSIONS)/include

USR_INCLUDES += -I/home/pi/wiringPi/wiringPi
wiringPi_DIR += /home/pi/wiringPi/wiringPi /home/pi/wiringPi/devLib

PROD_IOC = env
# env.dbd will be created and installed
DBD += env.dbd

# env.dbd will be made up from these files:
env_DBD += base.dbd

# Include dbd files from all support applications:
#env_DBD += xxx.dbd
env_DBD += devDS1820.dbd
env_DBD += stream.dbd
env_DBD += drvAsynSerialPort.dbd

# Add all the support libraries needed by this IOC
#env_LIBS += xxx
env_LIBS += wiringPi
env_LIBS += raspDS1820
env_LIBS += stream
env_LIBS += asyn

# env_registerRecordDeviceDriver.cpp derives from env.dbd
env_SRCS += env_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
env_SRCS_DEFAULT += envMain.cpp
env_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#env_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
env_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

