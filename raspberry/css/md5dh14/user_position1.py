from org.csstudio.opibuilder.scriptUtil import PVUtil

name_current_pulse="label_cur_pulse"
name_user_pos="text_user_pos1"

val_current_pulse=display.getWidget(name_current_pulse).getPropertyValue("text")

display.getWidget(name_user_pos).setPropertyValue("text", val_current_pulse)
