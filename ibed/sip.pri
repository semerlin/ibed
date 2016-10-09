#-------------------------------------------------
# pjsip defines
#-------------------------------------------------

contains(TARGET_CPU, x86) {
    DEFINES += TARGET_X86

    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include

    LIBS += /home/hy/Software/sip/desktop/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia.a
#    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpj.a
    LIBS += /home/hy/Software/sip/desktop/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libspeex.a
    LIBS += /home/hy/Software/sip/desktop/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libportaudio.a
    LIBS += /home/hy/Software/sip/desktop/lib/libresample.a
    LIBS += /home/hy/Software/sip/desktop/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/desktop/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libmilenage.a

    LIBS += -L/home/hy/Software/sip/desktop/lib/libcrypto.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libssl.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libm.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libuuid.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libnsl.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/librt.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libpthread.so

    LIBS += /usr/lib/libasound.so

} else:contains(TARGET_CPU, imx) {
    DEFINES += TARGET_IMX

    LIBS += /home/hy/Software/sip/arm/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjmedia.a
#    LIBS += /home/hy/Software/sip/arm/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/arm/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/arm/lib/libpj.a
    LIBS += /home/hy/Software/sip/arm/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/arm/lib/libspeex.a
    LIBS += /home/hy/Software/sip/arm/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/arm/lib/libportaudio.a
    LIBS += /home/hy/Software/sip/arm/lib/libresample.a
    LIBS += /home/hy/Software/sip/arm/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/arm/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/arm/lib/libmilenage.a

    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include
    INCLUDEPATH += /home/hy/Software/arm-alsa/include
    LIBS += /home/hy/Software/arm-alsa/lib/libasound.so
} else {
    TARGET_CPU = x86
    DEFINES += TARGET_X86

    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include

    LIBS += /home/hy/Software/sip/desktop/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia.a
#    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/desktop/lib/libpj.a
    LIBS += /home/hy/Software/sip/desktop/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libspeex.a
    LIBS += /home/hy/Software/sip/desktop/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libportaudio.a
    LIBS += /home/hy/Software/sip/desktop/lib/libresample.a
    LIBS += /home/hy/Software/sip/desktop/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/desktop/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/desktop/lib/libmilenage.a

    LIBS += -L/home/hy/Software/sip/desktop/lib/libcrypto.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libssl.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libm.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libuuid.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libnsl.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/librt.so
    LIBS += -L/home/hy/Software/sip/desktop/lib/libpthread.so

    LIBS += /usr/lib/libasound.so
}






