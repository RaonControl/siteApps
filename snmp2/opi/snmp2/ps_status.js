importPackage(Packages.org.csstudio.opibuilder.scriptUtil);

var status = PVUtil.getDouble(pvs[0]);

if(status = "1") {
widget.setPropertyValue("on_label", "ON");
widget.setPropertyValue("on_state",1);
widget.setPropertyValue("on_color",ColorFontUtil.getColorFromRGB(0,255,0));

} else {
widget.setPropertyValue("on_label", "OFF");
widget.setPropertyValue("on_color",ColorFontUtil.getColorFromRGB(0,100,0));
}
