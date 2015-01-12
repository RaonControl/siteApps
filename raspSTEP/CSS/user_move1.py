from org.csstudio.opibuilder.scriptUtil import PVUtil
import time

name_user_pos="text_user_pos1"

val_user_pos=display.getWidget(name_user_pos).getPropertyValue("text")

PVUtil.writePV("STEP:ANG:ABS", val_user_pos)
time.sleep(0.5)

PVUtil.writePV("STEP:MOVA", "1")
