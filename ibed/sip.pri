#-------------------------------------------------
# pjsip defines
#-------------------------------------------------

contains(TARGET_CPU, x86) {
    DEFINES += TARGET_X86

    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include

    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsua2.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libresample.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libspeex.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpj.a

    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libcrypto.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libssl.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libm.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libuuid.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/librt.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libpthread.so

    LIBS += /usr/lib/libasound.so

} else:contains(TARGET_CPU, imx) {
    DEFINES += PJ_AUTOCONF
    DEFINES += TARGET_IMX

    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjsua2.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libresample.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libspeex.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/arm-alsa/lib/libpj.a


    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include
    INCLUDEPATH += /home/hy/Software/arm-alsa/include
    LIBS += /home/hy/Software/arm-alsa/lib/libasound.so

} else {
    TARGET_CPU = x86
    DEFINES += TARGET_X86

    INCLUDEPATH += /home/hy/Software/sip/include
    DEPENDPATH += /home/hy/Software/sip/include

    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsua2.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsua.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip-ua.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip-simple.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjsip.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-codec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-videodev.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia-audiodev.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjmedia.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjnath.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpjlib-util.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libsrtp.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libresample.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libgsmcodec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libspeex.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libilbccodec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libg7221codec.a
    LIBS += /home/hy/Software/sip/desktop-alsa/lib/libpj.a

    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libcrypto.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libssl.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libm.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libuuid.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/librt.so
    LIBS += -L/home/hy/Software/sip/desktop-alsa//lib/libpthread.so

    LIBS += /usr/lib/libasound.so
}






