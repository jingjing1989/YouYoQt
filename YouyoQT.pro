QT       += core gui
QT  +=charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Test.cpp \
    home/Carousel.cpp \
    utility/CommonUtility.cpp \
    login/LineEditLabel.cpp \
    home/MainWindowHome.cpp \
    setting/MainWindowSetting.cpp \
    home/MyLeftBar.cpp \
    home/MyTableWidget.cpp \
    home/MyTitleBar.cpp \
    login/MyToolButton.cpp \
    setting/SettingDialog.cpp \
    setting/SystemSettingMainWindow.cpp \
    login/ToolButtonIconText.cpp \
    login/loginDialog.cpp \
    main.cpp 


HEADERS += \
    Test.h \
    home/Carousel.h \
    utility/CommonUtility.h \
    login/LineEditLabel.h \
    home/MainWindowHome.h \
    setting/MainWindowSetting.h \
    home/MyLeftBar.h \
    home/MyTableWidget.h \
    home/MyTitleBar.h \
    login/MyToolButton.h \
    setting/SettingDialog.h \
    setting/SystemSettingMainWindow.h \
    login/ToolButtonIconText.h \
    login/loginDialog.h 


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    Test.ui \
    home/Carousel.ui \
    login/LineEditPassword.ui \
    home/MainWindowHome.ui \
    setting/MainWindowSetting.ui \
    home/MyLeftBar.ui \
    home/MyTableWidget.ui \
    login/MyToolButton.ui \
    setting/SettingDialog.ui \
    setting/SystemSettingMainWindow.ui \
    login/loginDialog.ui

RESOURCES += \
    Res.qrc
RC_ICONS =logo.ico
