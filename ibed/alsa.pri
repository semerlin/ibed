#-------------------------------------------------
# alsa defines
#-------------------------------------------------

contains(TARGET_CPU, imx) {
    DEFINES += TARGET_IMX

    INCLUDEPATH += /home/hy/Software/arm-alsa/include
    LIBS += /home/hy/Software/arm-alsa/lib/libasound.so
} else:contains(TARGET_CPU, x86) {
    DEFINES += TARGET_X86
    LIBS += /usr/lib/libasound.so
} else {
    TARGET_CPU = x86
    DEFINES += TARGET_X86
    LIBS += /usr/lib/libasound.so
}



