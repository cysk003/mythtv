######################################################################
# Automatically generated by qmake (1.03a) Thu Aug 15 18:00:09 2002
######################################################################

TEMPLATE = lib
TARGET = avcodec
CONFIG += thread staticlib warn_off

include ( ../../settings.pro )
include ( ../../config.mak )

!exists( ../../config.mak ) {
    error(Please run the configure script first)
}

INCLUDEPATH = ../../

QMAKE_CFLAGS_RELEASE = $$OPTFLAGS -DHAVE_AV_CONFIG_H -I.. -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_GNU_SOURCE
QMAKE_CFLAGS_DEBUG = -g -DHAVE_AV_CONFIG_H -I.. -D_FILE_OFFSET_BITS=64 -D_LARGEFILE_SOURCE -D_GNU_SOURCE

# Input
SOURCES += common.c utils.c mem.c allcodecs.c mpegvideo.c h263.c jrevdct.c
SOURCES += jfdctfst.c mpegaudio.c ac3enc.c mjpeg.c resample.c dsputil.c
SOURCES += motion_est.c imgconvert.c imgresample.c msmpeg4.c mpeg12.c
SOURCES += h263dec.c svq1.c rv10.c mpegaudiodec.c pcm.c simple_idct.c
SOURCES += ratecontrol.c adpcm.c eval.c jfdctint.c oggvorbis.c

contains( CONFIG_AC3, yes ) {
    SOURCES += a52dec.c
    !contains( CONFIG_A52BIN, yes ) {
        SOURCES += liba52/bit_allocate.c liba52/bitstream.c liba52/downmix.c
        SOURCES += liba52/imdct.c liba52/parse.c
    }
}

#contains( CONFIG_MP3LAME, yes ) {
#    SOURCES += mp3lameaudio.c
#    LIBS += -lmp3lame
#}

contains( TARGET_GPROF, yes ) {
    QMAKE_CFLAGS_RELEASE += -p
    QMAKE_LFLAGS_RELEASE += -p
}

contains( TARGET_MMX, yes ) {
    SOURCES += i386/fdct_mmx.c i386/cputest.c i386/dsputil_mmx.c
    SOURCES += i386/mpegvideo_mmx.c i386/idct_mmx.c i386/motion_est_mmx.c
    SOURCES += i386/simple_idct_mmx.c
}

contains( TARGET_ARCH_ARMV4L, yes ) {
    SOURCES += armv4l/jrevdct_arm.S armv4l/dsputil_arm.c
}

contains( HAVE_MLIB, yes ) {
    OBJS += mlib/dsputil_mlib.c
    QMAKE_CFLAGS_RELEASE += $$MLIB_INC
}

contains( TARGET_ARCH_ALPHA, yes ) {
    OBJS += alpha/dsputil_alpha.c alpha/mpegvideo_alpha.c 
    OBJS += alpha/motion_est_alpha.c alpha/dsputil_alpha_asm.S
    QMAKE_CFLAGS_RELEASE += -Wa,-mpca56 --finline-limit=8000 -fforce-addr -freduce-all-givs
}

contains( TARGET_ARCH_POWERPC, yes ) {
    OBJS += ppc/dsputil_ppc.c
}

contains( TARGET_ARCH_ALTIVEC, yes ) {
    OBJS += ppc/dsputil_altivec.c
    QMAKE_CFLAGS_RELEASE += -faltivec
}
