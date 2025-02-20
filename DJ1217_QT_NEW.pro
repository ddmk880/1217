
QT +=core gui network
QT +=sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#包含控制台
#CONFIG += c++11 console
CONFIG += c++11
CONFIG -= app_bundle
RC_ICONS = myApex.ico
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
TARGET = DJ1217_QT_TEMP
TEMPLATE = app


greaterThan(QT_MAJOR_VERSION,4){
        TARGET_ARCH=$${QT_ARCH}
}else{
        TARGET_ARCH=$${QMAKE_HOST.arch}
}

contains(TARGET_ARCH, x86_64){
  CONFIG(debug,debug|release){
  #x64_debug
  message("x64_debug")
  DEPENDPATH += $$PWD/QXlsx/bin64
  DEPENDPATH += $$PWD/lib/x64_debug
  LIBS += -L$$PWD/QXlsx/bin64/ -lQXlsxd
  LIBS += $$PWD/lib/x64_debug/busapi32.lib
  LIBS += $$PWD/lib/x64_debug/PA_PCIe_3401.lib
  LIBS += $$PWD/lib/x64_debug/PA_PCIe_1501.lib
  LIBS += $$PWD/lib/x64_debug/PA_PCIe_1804.lib
  LIBS += $$PWD/lib/x64_debug/zlgcan.lib
  INCLUDEPATH += \
   $$PWD/include \
   $$PWD/include/QXlsx \
   $$PWD/components
  }else{
  #x64_release
  message("x64_release")
  DEPENDPATH += $$PWD/QXlsx/bin64
  DEPENDPATH += $$PWD/lib/x64_release
  LIBS += -L$$PWD/QXlsx/bin64/ -lQXlsxd
  LIBS += $$PWD/lib/x64_release/busapi32.lib
  LIBS += $$PWD/lib/x64_release/PA_PCIe_3401.lib
  LIBS += $$PWD/lib/x64_release/PA_PCIe_1501.lib
  LIBS += $$PWD/lib/x64_release/PA_PCIe_1804.lib
  LIBS += $$PWD/lib/x64_release/zlgcan.lib
  INCLUDEPATH += \
   $$PWD/include \
   $$PWD/include/QXlsx \
   $$PWD/components
  }
}else{
  CONFIG(debug,debug|release){
  #x86_debug
  message("x86_debug")

  }else{
  #x86_release
  message("x86_release")

  }
}

DEFINES += ENV_DEV

SOURCES += \
    Crc.cpp \
    DatabaseView.cpp \
    HardwareCtrl/CardCtrl_1553B.cpp \
    HardwareCtrl/CardCtrl_AD_OC.cpp \
    HardwareCtrl/CardCtrl_CAN.cpp \
    HardwareCtrl/CardCtrl_NET.cpp \
    HardwareCtrl/CardCtrl_RT1553B.cpp \
    HardwareCtrl/CardCtrl_RapidIO.cpp \
    HardwareCtrl/DeviceCtrl_signal.cpp \
    MonitorView.cpp \
    SubView_Page/CN_SignalContrl.cpp \
    SubView_Page/Translate_Mess.cpp \
    SubView_Page/auto_udp.cpp \
    SubView_Page/commonthreadworker.cpp \
    SubView_Page/ipdialog.cpp \
    SubView_Page/m_games.cpp \
    SubView_Page/mylabel.cpp \
    SubView_Page/networker.cpp \
    SubView_Page/signal_1466.cpp \
    SubView_Page/sub1553_Overheadtask.cpp \
    SubView_Page/sub1553_busclass.cpp \
    SubView_Page/sub1553_buspower.cpp \
    SubView_Page/sub1553_gkcontrol.cpp \
    SubView_Page/sub1553_gkcontrol2.cpp \
    SubView_Page/sub1553_gkmaygsl.cpp \
    SubView_Page/sub1553_gkmayrffront.cpp \
    SubView_Page/sub1553_gksxkucontrol.cpp \
    SubView_Page/sub1553_modecontrl.cpp \
    SubView_Page/sub1553_tccontrol.cpp \
    SubView_Page/sub1553_tccontrol2.cpp \
    SubView_Page/sub1553_tccontrol_l.cpp \
    SubView_Page/sub1553_tccontrol_spi.cpp \
    SubView_Page/sub1553_tccontrol_sxku.cpp \
    SubView_Page/sub1553_tcmayrffront.cpp \
    SubView_Page/subboard_bc.cpp \
    SubView_Page/subboard_rt.cpp \
    SubView_Page/subrs422_rec.cpp \
    SubView_Page/subsrio_overnote.cpp \
    SubView_Page/subtrillion_overnote.cpp \
    SubView_Page/subyc_ad.cpp \
    SubView_Page/subyc_canc81.cpp \
    SubView_Page/subyc_packspeed.cpp \
    SubView_Page/subyc_slowspeed.cpp \
    SubView_Page/yxq_contrl.cpp \
    YcView.cpp \
    components/layouts/qtmaterialsnackbarlayout.cpp \
    components/lib/qtmaterialcheckable.cpp \
    components/lib/qtmaterialcheckable_internal.cpp \
    components/lib/qtmaterialoverlaywidget.cpp \
    components/lib/qtmaterialripple.cpp \
    components/lib/qtmaterialrippleoverlay.cpp \
    components/lib/qtmaterialstatetransition.cpp \
    components/lib/qtmaterialstyle.cpp \
    components/lib/qtmaterialtheme.cpp \
    components/qtmaterialappbar.cpp \
    components/qtmaterialautocomplete.cpp \
    components/qtmaterialautocomplete_internal.cpp \
    components/qtmaterialavatar.cpp \
    components/qtmaterialbadge.cpp \
    components/qtmaterialcheckbox.cpp \
    components/qtmaterialcircularprogress.cpp \
    components/qtmaterialcircularprogress_internal.cpp \
    components/qtmaterialdialog.cpp \
    components/qtmaterialdialog_internal.cpp \
    components/qtmaterialdrawer.cpp \
    components/qtmaterialdrawer_internal.cpp \
    components/qtmaterialfab.cpp \
    components/qtmaterialflatbutton.cpp \
    components/qtmaterialflatbutton_internal.cpp \
    components/qtmaterialiconbutton.cpp \
    components/qtmateriallist.cpp \
    components/qtmateriallistitem.cpp \
    components/qtmaterialmenu.cpp \
    components/qtmaterialmenu_internal.cpp \
    components/qtmaterialpaper.cpp \
    components/qtmaterialprogress.cpp \
    components/qtmaterialprogress_internal.cpp \
    components/qtmaterialradiobutton.cpp \
    components/qtmaterialraisedbutton.cpp \
    components/qtmaterialscrollbar.cpp \
    components/qtmaterialscrollbar_internal.cpp \
    components/qtmaterialslider.cpp \
    components/qtmaterialslider_internal.cpp \
    components/qtmaterialsnackbar.cpp \
    components/qtmaterialsnackbar_internal.cpp \
    components/qtmaterialtable.cpp \
    components/qtmaterialtabs.cpp \
    components/qtmaterialtabs_internal.cpp \
    components/qtmaterialtextfield.cpp \
    components/qtmaterialtextfield_internal.cpp \
    components/qtmaterialtoggle.cpp \
    components/qtmaterialtoggle_internal.cpp \
    TaskView.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp

HEADERS += \
    Crc.h \
    DatabaseView.h \
    Globel_Define.h \
    HardwareCtrl/CardCtrl_1553B.h \
    HardwareCtrl/CardCtrl_AD_OC.h \
    HardwareCtrl/CardCtrl_CAN.h \
    HardwareCtrl/CardCtrl_NET.h \
    HardwareCtrl/CardCtrl_RT1553B.h \
    HardwareCtrl/CardCtrl_RapidIO.h \
    HardwareCtrl/DeviceCtrl_signal.h \
    MonitorView.h \
    SubView_Page/CN_SignalContrl.h \
    SubView_Page/Translate_Mess.h \
    SubView_Page/auto_udp.h \
    SubView_Page/commonthreadworker.h \
    SubView_Page/ipdialog.h \
    SubView_Page/m_games.h \
    SubView_Page/mylabel.h \
    SubView_Page/networker.h \
    SubView_Page/signal_1466.h \
    SubView_Page/sub1553_Overheadtask.h \
    SubView_Page/sub1553_busclass.h \
    SubView_Page/sub1553_buspower.h \
    SubView_Page/sub1553_gkcontrol.h \
    SubView_Page/sub1553_gkcontrol2.h \
    SubView_Page/sub1553_gkmaygsl.h \
    SubView_Page/sub1553_gkmayrffront.h \
    SubView_Page/sub1553_gksxkucontrol.h \
    SubView_Page/sub1553_modecontrl.h \
    SubView_Page/sub1553_tccontrol.h \
    SubView_Page/sub1553_tccontrol2.h \
    SubView_Page/sub1553_tccontrol_l.h \
    SubView_Page/sub1553_tccontrol_spi.h \
    SubView_Page/sub1553_tccontrol_sxku.h \
    SubView_Page/sub1553_tcmayrffront.h \
    SubView_Page/subboard_bc.h \
    SubView_Page/subboard_rt.h \
    SubView_Page/subrs422_rec.h \
    SubView_Page/subsrio_overnote.h \
    SubView_Page/subtrillion_overnote.h \
    SubView_Page/subyc_ad.h \
    SubView_Page/subyc_canc81.h \
    SubView_Page/subyc_packspeed.h \
    SubView_Page/subyc_slowspeed.h \
    SubView_Page/yxq_contrl.h \
    TaskView.h \
    YcView.h \
    components/lib/qtmaterialcheckable.h \
    components/lib/qtmaterialcheckable_internal.h \
    components/lib/qtmaterialcheckable_p.h \
    components/lib/qtmaterialoverlaywidget.h \
    components/lib/qtmaterialripple.h \
    components/lib/qtmaterialrippleoverlay.h \
    components/lib/qtmaterialstatetransition.h \
    components/lib/qtmaterialstatetransitionevent.h \
    components/lib/qtmaterialstyle.h \
    components/lib/qtmaterialstyle_p.h \
    components/lib/qtmaterialtheme.h \
    components/lib/qtmaterialtheme_p.h \
    components/qtmaterialappbar.h \
    components/qtmaterialappbar_p.h \
    components/qtmaterialautocomplete.h \
    components/qtmaterialautocomplete_internal.h \
    components/qtmaterialautocomplete_p.h \
    components/qtmaterialavatar.h \
    components/qtmaterialavatar_p.h \
    components/qtmaterialbadge.h \
    components/qtmaterialbadge_p.h \
    components/qtmaterialcheckbox.h \
    components/qtmaterialcheckbox_p.h \
    components/qtmaterialcircularprogress.h \
    components/qtmaterialcircularprogress_internal.h \
    components/qtmaterialcircularprogress_p.h \
    components/qtmaterialdialog.h \
    components/qtmaterialdialog_internal.h \
    components/qtmaterialdialog_p.h \
    components/qtmaterialdrawer.h \
    components/qtmaterialdrawer_internal.h \
    components/qtmaterialdrawer_p.h \
    components/qtmaterialfab.h \
    components/qtmaterialfab_p.h \
    components/qtmaterialflatbutton.h \
    components/qtmaterialflatbutton_internal.h \
    components/qtmaterialflatbutton_p.h \
    components/qtmaterialiconbutton.h \
    components/qtmaterialiconbutton_p.h \
    components/qtmateriallist.h \
    components/qtmateriallist_p.h \
    components/qtmateriallistitem.h \
    components/qtmateriallistitem_p.h \
    components/qtmaterialmenu.h \
    components/qtmaterialmenu_internal.h \
    components/qtmaterialmenu_p.h \
    components/qtmaterialpaper.h \
    components/qtmaterialpaper_p.h \
    components/qtmaterialprogress.h \
    components/qtmaterialprogress_internal.h \
    components/qtmaterialprogress_p.h \
    components/qtmaterialradiobutton.h \
    components/qtmaterialradiobutton_p.h \
    components/qtmaterialraisedbutton.h \
    components/qtmaterialraisedbutton_p.h \
    components/qtmaterialscrollbar.h \
    components/qtmaterialscrollbar_internal.h \
    components/qtmaterialscrollbar_p.h \
    components/qtmaterialslider.h \
    components/qtmaterialslider_internal.h \
    components/qtmaterialslider_p.h \
    components/qtmaterialsnackbar.h \
    components/qtmaterialsnackbar_internal.h \
    components/qtmaterialsnackbar_p.h \
    components/qtmaterialtable.h \
    components/qtmaterialtable_p.h \
    components/qtmaterialtabs.h \
    components/qtmaterialtabs_internal.h \
    components/qtmaterialtabs_p.h \
    components/qtmaterialtextfield.h \
    components/qtmaterialtextfield_internal.h \
    components/qtmaterialtextfield_p.h \
    components/qtmaterialtoggle.h \
    components/qtmaterialtoggle_internal.h \
    components/qtmaterialtoggle_p.h \
    mainwindow.h \
    qcustomplot.h

FORMS += \
    DatabaseView.ui \
    MonitorView.ui \
    SubView_Page/Translate_Mess.ui \
    SubView_Page/auto_udp.ui \
    SubView_Page/ipdialog.ui \
    SubView_Page/m_games.ui \
    SubView_Page/signal_1466.ui \
    SubView_Page/sub1553_Overheadtask.ui \
    SubView_Page/sub1553_busclass.ui \
    SubView_Page/sub1553_buspower.ui \
    SubView_Page/sub1553_gkcontrol.ui \
    SubView_Page/sub1553_gkcontrol2.ui \
    SubView_Page/sub1553_gkmaygsl.ui \
    SubView_Page/sub1553_gkmayrffront.ui \
    SubView_Page/sub1553_gksxkucontrol.ui \
    SubView_Page/sub1553_modecontrl.ui \
    SubView_Page/sub1553_tccontrol.ui \
    SubView_Page/sub1553_tccontrol2.ui \
    SubView_Page/sub1553_tccontrol_l.ui \
    SubView_Page/sub1553_tccontrol_spi.ui \
    SubView_Page/sub1553_tccontrol_sxku.ui \
    SubView_Page/sub1553_tcmayrffront.ui \
    SubView_Page/subboard_bc.ui \
    SubView_Page/subboard_rt.ui \
    SubView_Page/subrs422_rec.ui \
    SubView_Page/subsrio_overnote.ui \
    SubView_Page/subtrillion_overnote.ui \
    SubView_Page/subyc_ad.ui \
    SubView_Page/subyc_canc81.ui \
    SubView_Page/subyc_packspeed.ui \
    SubView_Page/subyc_slowspeed.ui \
    SubView_Page/yxq_contrl.ui \
    TaskView.ui \
    YcView.ui \
    mainwindow.ui

QMAKE_CXXFLAGS += -Wno-unused-parameter
QMAKE_CXXFLAGS += -Wno-unused-variable

RESOURCES += \
    pic.qrc \
    qss.qrc
