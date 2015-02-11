TOP=../..

include $(TOP)/configure/CONFIG
#----------------------------------------
#  ADD MACRO DEFINITIONS AFTER THIS LINE
#=============================

USR_DBDFLAGS  += -I/home/scwook/epics/R3.14.12.4/epicsLibs/motorApps/motorR6-9/dbd

motor_DIR += /home/scwook/epics/R3.14.12.4/epicsLibs/motorApps/motorR6-9/lib/$(T_A)
phytronAxisMotor_DIR += /home/scwook/epics/R3.14.12.4/epicsLibs/motorApps/motorR6-9/lib/$(T_A)

#=============================
# Build the IOC application

PROD_IOC = motor
# motor.dbd will be created and installed
DBD += motor.dbd

# motor.dbd will be made up from these files:
motor_DBD += base.dbd

# Include dbd files from all support applications:
#motor_DBD += xxx.dbd
motor_DBD += asyn.dbd
motor_DBD += motorSupport.dbd
motor_DBD += drvAsynIPPort.dbd
motor_DBD += phytron.dbd

# Add all the support libraries needed by this IOC
#motor_LIBS += xxx
motor_LIBS += asyn
motor_LIBS += motor
motor_LIBS += phytronAxisMotor

# motor_registerRecordDeviceDriver.cpp derives from motor.dbd
motor_SRCS += motor_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
motor_SRCS_DEFAULT += motorMain.cpp
motor_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#motor_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
motor_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

