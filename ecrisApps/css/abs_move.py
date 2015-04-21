from org.csstudio.opibuilder.scriptUtil import PVUtil
import time

name_abs_pos="text_abs_pos"

val_abs_pos=display.getWidget(name_abs_pos).getPropertyValue("text")

PVUtil.writePV("STEP:ANG:ABS", val_abs_pos)
time.sleep(0.5);

PVUtil.writePV("STEP:MOVA", "1")
