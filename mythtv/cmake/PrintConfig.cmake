#
# Copyright (C) 2022-2023 David Hampton
#
# See the file LICENSE_FSF for licensing information.
#

function(message_trgt _label _target)
  if(TARGET ${_target})
    set(_string yes)
  else()
    set(_string no)
  endif()
  if(${ARGC} GREATER 2)
    message("${_label}  ${_string} [${ARGV2}]")
  else()
    message("${_label}  ${_string}")
  endif()
endfunction()

function(message_trg2 _label _target _extra)
  if(TARGET ${_target})
    set(_string yes)
  else()
    set(_string no)
  endif()
  message("${_label}  ${_string} ${_extra}")
endfunction()

function(message_trg4 _label1 _target1 _label2 _target2)
  if(NOT TARGET ${_target1})
    message("${_label1}  no")
    return()
  endif()
  if(TARGET ${_target2})
    set(_string2 yes)
  else()
    set(_string12 no)
  endif()
  message("${_label1}  yes (${_label2} ${_string2})")
endfunction()

function(message_vrbl _label _vname)
  if("${${_vname}}" STREQUAL "" OR "${${_vname}}" MATCHES
                                   "(OFF|FALSE|NOTFOUND)")
    set(_string no)
  else()
    set(_string yes)
  endif()
  message("${_label}  ${_string}")
endfunction()

if(NOT "${quiet}" STREQUAL "yes")
  message("")
  message("#### MythTV CONFIGURATION ####")
  message("# Basic Settings")
  message("Qt minimum version        ${QT${QT_VERSION_MAJOR}_MIN_VERSION_STR}")
  message("Qt installed version      ${Qt${QT_VERSION_MAJOR}_VERSION}")
  message("Compile type              ${CMAKE_BUILD_TYPE}")
  message("Compiler                  ${CMAKE_CXX_COMPILER}")
  message_vrbl("Ccache                  " CCACHE_FOUND)
  message_vrbl("DistCC                  " DISTCC_FOUND)
  message("install prefix            ${CMAKE_INSTALL_PREFIX}")
  message("runtime prefix            ${MYTH_RUN_PREFIX}")
  message("")
  # ~~~
  # if( CPU_OVERRIDE AND test x"$cpu" != x"generic")
  #   message( "CPU override # $arch $subarch ($cpu)")
  # elif( test x"$processor" != x"" )
  #   message( "CPU # $arch $subarch ($processor)")
  # else()
  #   message( "CPU                       $arch $subarch")
  # endif()
  # ~~~

  if(X86)
    message("standalone assembly       ${x86asm-no}")
    message("x86 assembler             ${x86asmexe}")
    message("MMX enabled               ${mmx-no}")
    message("MMXEXT enabled            ${mmxext-no}")
    message("3DNow! enabled            ${amd3dnow-no}")
    message("3DNow! extended enabled   ${amd3dnowext-no}")
    message("SSE enabled               ${sse-no}")
    message("SSSE3 enabled             ${ssse3-no}")
    message("AESNI enabled             ${aesni-no}")
    message("AVX enabled               ${avx-no}")
    message("AVX2 enabled              ${avx2-no}")
    message("XOP enabled               ${xop-no}")
    message("FMA3 enabled              ${fma3-no}")
    message("FMA4 enabled              ${fma4-no}")
    message("i686 features enabled     ${i686-no}")
  elseif(AARCH64)
    message(
      "NEON enabled              ${neon-no} (Intrinsics ${intrinsics_neon-no})")
    message("VFP enabled               ${vfp-no}")
  elseif(ARM)
    message("ARMv5TE enabled           ${armv5te-no}")
    message("ARMv6 enabled             ${armv6-no}")
    message("ARMv6T2 enabled           ${armv6t2-no}")
    message("VFP enabled               ${vfp-no}")
    message(
      "NEON enabled              ${neon-no} (Intrinsics ${intrinsics_neon-no})")
    message("THUMB enabled             ${thumb-no}")
  elseif(MIPS)
    message("MIPS FPU enabled          ${mipsfpu-no}")
    message("MIPS DSP R1 enabled       ${mipsdsp-no}")
    message("MIPS DSP R2 enabled       ${mipsdspr2-no}")
    message("MIPS MSA enabled          ${msa-no}")
    message("LOONGSON MMI enabled      ${mmi-no}")
  elseif(PPC)
    message("AltiVec enabled           ${altivec-no}")
    message("VSX enabled               ${vsx-no}")
    message("POWER8 enabled            ${power8-no}")
    message("PPC 4xx optimizations     ${ppc4xx-no}")
    message("dcbzl available           ${dcbzl-no}")
  endif()
endif()

message("")
if(USING_FRONTEND)
  message("# Input Support")
  message_trgt("Joystick menu           " joystick)
  message_trgt("lirc support            " lirc)
  message_trgt("libCEC device support   " PkgConfig::LibCEC
               ${LibCEC_INCLUDE_DIRS})
  if(APPLE)
    message("Apple Remote              yes")
  endif()
endif()

if(ENABLE_BACKEND)
  message_trgt("Video4Linux support     " PkgConfig::V4L2)
  message_vrbl("FireWire support        " ENABLE_FIREWIRE)
  message_trgt("DVB support             " mythtv_dvb ${DVB_PATH})
  message_vrbl("DVB-S2 support          " HAVE_FE_CAN_2G_MODULATION)
  message_trgt("HDHomeRun support       " HDHomerun::HDHomerun)
  message_trgt("Sat>IP support          " mythtv_satip)
  message_trgt("V@Box TV Gateway support" mythtv_vbox)
  message_trgt("Ceton support           " mythtv_ceton)
  message_trgt("DVEO ASI support        " mythtv_asi)
  message("")
endif()

if(ENABLE_FRONTEND)
  message("# Sound Output Support")
  message_trgt("PulseAudio support      " PkgConfig::PULSEAUDIO)
  message_trgt("OSS support             " mythtv_oss)
  message_trgt("ALSA support            " PkgConfig::ALSA)
  message_trgt("JACK support            " PkgConfig::JACK)
  if(WIN32)
    message("Windows (Windows audio)   yes")
    message("Windows (DirectX)         yes")
  endif()
  message("")
  message("# Video Output Support")
  message_trgt("x11 support             " X11::X11)
  message_trgt("x11/xrandr support      " X11::Xrandr)
  if(TARGET X11::X11)
    message_trgt("VDPAU support           " PkgConfig::VDPAU)
    get_target_property(_FFNVCODEC_DEFS PkgConfig::FFNVCODEC INTERFACE_COMPILE_DEFINITIONS)
    if("USING_NVDEC" IN_LIST _FFNVCODEC_DEFS)
      set(_USING_NVDEC ON)
    endif()
    message_vrbl("NVDEC support           " _USING_NVDEC)
  endif()
  if(APPLE)
    message_vrbl("VideoToolBox support    " APPLE_VIDEOTOOLBOX_LIBRARY)
  endif()
  message_trgt("VAAPI support           " PkgConfig::VAAPI)
  message_trgt("DRM support             " PkgConfig::DRM)
  if(TARGET PkgConfig::DRM)
    message_trgt("DRM Qt integration      " Qt${QT_VERSION_MAJOR}::GuiPrivate)
  endif()
  message_trg4("Video4Linux codecs      " PkgConfig::V4L2 "DRM" PkgConfig::DRM)
  message_trgt("MMAL decoder support    " mythtv_mmal)
  if(TARGET OpenGL::GL)
    message_trgt("OpenGL                  " OpenGL::GL)
    message_trgt("EGL support             " OpenGL::EGL)
  elseif(TARGET PkgConfig::GLES2)
    message_trgt("OpenGL                  " PkgConfig::GLES2 "GLES")
    message_trgt("EGL support             " PkgConfig::EGL)
  endif()
  if(WIN32)
    message_vrbl("Windows (Direct3D)      " HAVE_D3D9_H)
    message_vrbl("DXVA2 support           " HAVE_DXVA2)
  endif()
  message_trg4("Vulkan                  " Vulkan::Vulkan "libglslang"
               PkgConfig::GLSLANG)
  message_trgt("MHEG support            " mythtv_mheg)
  message_trgt("libass subtitle support " PkgConfig::LIBASS)
  message("")
endif()

message("# Misc Features")
message_vrbl("Frontend                " ENABLE_FRONTEND)
message_vrbl("Backend                 " ENABLE_BACKEND)
message_trgt("Qt private headers      " Qt${QT_VERSION_MAJOR}::GuiPrivate)
if(TARGET PkgConfig::WAYLAND_CLIENT)
  get_target_property(_WAYLAND_DEFS PkgConfig::WAYLAND_CLIENT INTERFACE_COMPILE_DEFINITIONS)
  if("USING_WAYLANDEXTRAS" IN_LIST _WAYLAND_DEFS)
    set(_USING_WAYLANDEXTRAS ON)
  endif()
endif()
message_vrbl("Wayland extras          " _USING_WAYLANDEXTRAS)
message("multi threaded libavcodec ${threads-no}")
if(USING_FRONTEND)
  message_trgt("libxml2 support         " PkgConfig::LibXml2
               ${LIBXML2_INCLUDE_DIR})
endif()
message_trgt("libdns_sd (Bonjour)     " PkgConfig::LIBDNS_SD)
message_trgt("libcrypto               " PkgConfig::LIBCRYPTO)
message_trgt("gnutls                  " PkgConfig::GNUTLS)
if(SYSTEM_LIBBLURAY_FOUND)
  message("bluray support            yes (system)")
else()
  message("bluray support            yes (internal)")
  message("BD-J (Bluray java)        ${bdjava-no}")
  message("BD-J type                 ${bdj_type}")
endif()
message_vrbl("systemd_notify          " SYSTEMD_NOTIFY)
message_vrbl("systemd_journal         " SYSTEMD_JOURNALD)
message("")

message("Bindings")
message_vrbl("bindings_perl           " USING_BINDINGS_PERL)
if(MYTH_PERL_CONFIG_OPTS)
  message("Perl config options ${MYTH_PERL_CONFIG_OPTS}")
endif()
message_vrbl("bindings_python         " USING_BINDINGS_PYTHON)
message_vrbl("bindings_php            " USING_BINDINGS_PHP)
message("")

message("# External Codec Options")
message_trgt("mp3lame                 " Lame::Lame)
message_trgt("xvid                    " LibXvid::LibXvid)
message_trgt("x264                    " LibX264::LibX264)
message_trgt("x265 (HEVC)             " LibX265::LibX265)
message_trgt("vpx                     " PkgConfig::LIBVPX)
message_trgt("libaom   (AV1)          " PkgConfig::LIBAOM)
message_trgt("libdav1d (AV1)          " PkgConfig::LIBDAV1D)
message("")

message("# Compilation Options")
message("C++ standard supported    c++${CMAKE_CXX_STANDARD}")
message_vrbl("Enforce c++11 nullptr   " HAVE_CXX_Wzero-as-null-pointer-constant)
message_vrbl("Enforce shadowed vars   " HAVE_CXX_Wshadow)
