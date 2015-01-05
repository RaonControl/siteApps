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

raspGPIO_DIR += $(RAON_SITELIBS)/lib/$(T_A)

PROD_IOC = step
# step.dbd will be created and installed
DBD += step.dbd

# step.dbd will be made up from these files:
step_DBD += base.dbd

# Include dbd files from all support applications:
#step_DBD += xxx.dbd
step_DBD += devGPIO.dbd

# Add all the support libraries needed by this IOC
#step_LIBS += xxx
step_LIBS += raspGPIO
step_LIBS += wiringPi

# step_registerRecordDeviceDriver.cpp derives from step.dbd
step_SRCS += step_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
step_SRCS_DEFAULT += stepMain.cpp
step_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#step_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
step_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

ifneq ($(SNCSEQ),)
    step_DBD += seqStep.dbd
    step_SRCS += seqStep.stt
    step_LIBS += seq pv
endif

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

