from org.csstudio.opibuilder.scriptUtil import PVUtil
import time

name_rel_pos="text_rel_pos"

val_rel_pos=float(display.getWidget(name_rel_pos).getPropertyValue("text"))

PVUtil.writePV("STEP:ANG:REL", val_rel_pos)
time.sleep(0.5)

PVUtil.writePV("STEP:MOVR", "1")
