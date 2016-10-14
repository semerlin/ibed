#-------------------------------------------------
# global defines and parameters
#-------------------------------------------------

# platform control, imx/x86, default is x86
contains(TARGET_CPU, imx) {
    DEFINES += TARGET_IMX
} else:contains(TARGET_CPU, x86) {
    DEFINES += TARGET_X86
} else {
    TARGET_CPU = x86
    DEFINES += TARGET_X86
}

