from org.csstudio.opibuilder.scriptUtil import PVUtil

name_user_pos="text_user_pos1"

val_user_pos=display.getWidget(name_user_pos).getPropertyValue("text")

PVUtil.writePV("STEP:ABS", val_user_pos)
PVUtil.writePV("STEP:MOVA", "1")
