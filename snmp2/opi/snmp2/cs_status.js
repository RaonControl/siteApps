importPackage(Packages.org.csstudio.opibuilder.scriptUtil);

var status = PVUtil.getString(pvs[0]);

if(status = "80 mainOn(0)") {
widget.setPropertyValue("on_label", "ON");
widget.setPropertyValue("on_state",1);
widget.setPropertyValue("on_color",ColorFontUtil.getColorFromRGB(0,255,0));

} else if (status = "80 mainInhibit(1)") {
widget.setPropertyValue("on_label", "Inhibit");
widget.setPropertyValue("on_color","Major");

} else if (status = "80 localControlOnly(2)") {
widget.setPropertyValue("on_label", "Local control Only");
widget.setPropertyValue("on_color","Minor");

} else if (status == "80 inputFailure(3)") {
widget.setPropertyValue("on_label", "Power fail");
widget.setPropertyValue("on_color","Major");

} else if (status == "80 outputFailure(4)") {
widget.setPropertyValue("on_label", "Output failure");
widget.setPropertyValue("on_color","Major");

} else if (status == "80 fantrayFailure(5)") {
widget.setPropertyValue("on_label", "Fantray failure");
widget.setPropertyValue("on_color","Major");

} else if (status == "80 sensorFailure(6)") {
widget.setPropertyValue("on_label", "Temp sensor failure");
widget.setPropertyValue("on_color","Major");

} else if (status == "80 vmeSysfail(7)") {
widget.setPropertyValue("on_label", "VME SYSFAIL");
widget.setPropertyValue("on_color","Major");

} else if (status == "plugAndPlayIncompatible(8)") {
widget.setPropertyValue("on_label", "Wrong p/s and rack connected");
widget.setPropertyValue("on_color","Major");
widget.setPropertyValue("font",ColorFontUtil.getFont("Cantarell",14,1));

} else if (status == "80 busReset(9)") {
widget.setPropertyValue("on_label", "BUS Reset");
widget.setPropertyValue("on_color","Invalid");

} else if (status == "80 supplyDerating(10)") {
widget.setPropertyValue("on_label", "1st P/S DEG");
widget.setPropertyValue("on_color","Invalid");

} else if (status == "80 supplyFailure(11)") {
widget.setPropertyValue("on_label", "1st P/S FAL");
widget.setPropertyValue("on_color","Major");

} else if (status == "80 supplyDerating2(12)") {
widget.setPropertyValue("on_label", "2nd P/S DEG");
widget.setPropertyValue("on_color","Invalid");

} else if (status == "80 supplyFailure2(13)") {
widget.setPropertyValue("on_label", "2nd P/S FAL");
widget.setPropertyValue("on_color","Major");

} else {
widget.setPropertyValue("on_label", "OFF");
widget.setPropertyValue("on_state",0);
widget.setPropertyValue("on_color",ColorFontUtil.getColorFromRGB(0,100,0));

}
