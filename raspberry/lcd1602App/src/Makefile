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
USR_INCLUDES += -I/home/pi/wiringPi/devLib
wiringPi_DIR += /home/pi/wiringPi/wiringPi
wiringPiDev_DIR += /home/pi/wiringPi/devLib

raspLCD1602_DIR += $(RAON_SITELIBS)/lib/$(T_A)

PROD_IOC = lcd1602
# lcd1602.dbd will be created and installed
DBD += lcd1602.dbd

# lcd1602.dbd will be made up from these files:
lcd1602_DBD += base.dbd

# Include dbd files from all support applications:
#lcd1602_DBD += xxx.dbd
lcd1602_DBD += lcdoutRecord.dbd
lcd1602_DBD += devLCD1602.dbd

# Add all the support libraries needed by this IOC
#lcd1602_LIBS += xxx
lcd1602_LIBS += raspLCD1602
lcd1602_LIBS += wiringPi
lcd1602_LIBS += wiringPiDev

# lcd1602_registerRecordDeviceDriver.cpp derives from lcd1602.dbd
lcd1602_SRCS += lcd1602_registerRecordDeviceDriver.cpp

# Build the main IOC entry point on workstation OSs.
lcd1602_SRCS_DEFAULT += lcd1602Main.cpp
lcd1602_SRCS_vxWorks += -nil-

# Add support from base/src/vxWorks if needed
#lcd1602_OBJS_vxWorks += $(EPICS_BASE_BIN)/vxComLibrary

# Finally link to the EPICS Base libraries
lcd1602_LIBS += $(EPICS_BASE_IOC_LIBS)

#===========================

include $(TOP)/configure/RULES
#----------------------------------------
#  ADD RULES AFTER THIS LINE

