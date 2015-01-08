from org.csstudio.opibuilder.scriptUtil import PVUtil

name_abs_pos="text_abs_pos"

val_abs_pos=display.getWidget(name_abs_pos).getPropertyValue("text")

PVUtil.writePV("STEP:ANG:ABS", val_abs_pos)
PVUtil.writePV("STEP:MOVA", "1")
