#-------------------------------------------------
#
# Project created by QtCreator 2011-11-28T10:50:15
#
#-------------------------------------------------

QT       += core gui network widgets printsupport
QT       += concurrent
unix:TARGET = ../EUMETCastView
else:win32:TARGET = ../../EUMETCastView
TEMPLATE = app
CONFIG += static
CONFIG += c++11


SOURCES += main.cpp \
    mainwindow.cpp \
    options.cpp \
    segmentimage.cpp \
    satellite.cpp \
    globals.cpp \
    avhrrsatellite.cpp \
    segment.cpp \
    segmentgac.cpp \
    segmenthrp.cpp \
    segmentmetop.cpp \
    segmentnoaa.cpp \
    segmentlist.cpp \
    segmentlistgac.cpp \
    segmentlisthrp.cpp \
    segmentlistmetop.cpp \
    segmentlistnoaa.cpp \
    generalverticalperspective.cpp \
    lambertconformalconic.cpp \
    stereographic.cpp \
    pixgeoconversion.cpp \
    solar.cpp \
    formephem.cpp \
    downloadmanager.cpp \
    msgdataaccess.cpp \
    msgfileaccess.cpp \
    formtoolbox.cpp \
    formimage.cpp \
    imagescrollarea.cpp \
    gshhsdata.cpp \
    cylequidist.cpp \
    mapcyl.cpp \
    formmapcyl.cpp \
    globe.cpp \
    geometryengine.cpp \
    octahedron.cpp \
    projextentsgl.cpp \
    satgl.cpp \
    segmentgl.cpp \
    skybox.cpp \
    soc.cpp \
    trackball.cpp \
    sathorizon.cpp \
    dialogpreferences.cpp \
    segmentlistgeostationary.cpp \
    formgeostationary.cpp \
    texturewriter.cpp \
    sgp_math.cpp \
    sgp_obs.cpp \
    sgp_time.cpp \
    qcompressor.cpp \
    segmentviirsm.cpp \
    segmentviirsdnb.cpp \
    segmentlistviirsdnb.cpp \
    segmentlistviirsm.cpp \
    poi.cpp \
    equirectangular.cpp \
    infrascales.cpp \
    infrawidget.cpp \
    forminfrascales.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    options.h \
    segmentimage.h \
    satellite.h \
    globals.h \
    avhrrsatellite.h \
    segment.h \
    segmentgac.h \
    segmenthrp.h \
    segmentmetop.h \
    segmentnoaa.h \
    segmentlist.h \
    segmentlistgac.h \
    segmentlisthrp.h \
    segmentlistmetop.h \
    segmentlistnoaa.h \
    generalverticalperspective.h \
    lambertconformalconic.h \
    stereographic.h \
    pixgeoconversion.h \
    formephem.h \
    downloadmanager.h \
    msgdataaccess.h \
    msgfileaccess.h \
    formtoolbox.h \
    formimage.h \
    imagescrollarea.h \
    gshhs.h \
    gshhsdata.h \
    cylequidist.h \
    mapcyl.h \
    formmapcyl.h \
    globe.h \
    geometryengine.h \
    octahedron.h \
    projextentsgl.h \
    satgl.h \
    segmentgl.h \
    skybox.h \
    soc.h \
    trackball.h \
    sathorizon.h \
    dialogpreferences.h \
    segmentlistgeostationary.h \
    formgeostationary.h \
    texturewriter.h \
    sgp4sdp4.h \
    stdafx.h \
    qcompressor.h \
    segmentviirsm.h \
    segmentviirsdnb.h \
    segmentlistviirsdnb.h \
    segmentlistviirsm.h \
    poi.h \
    stb_image.h \
    equirectangular.h \
    infrascales.h \
    infrawidget.h \
    colormaps.h \
    forminfrascales.h \
    qcustomplot.h

#QMAKE_CXXFLAGS += -std=c++0x -Wno-trigraphs
unix:QMAKE_CXXFLAGS += -Wno-trigraphs

FORMS    += mainwindow.ui \
    dialogpreferences.ui \
    formephem.ui \
    formmapcyl.ui \
    formtoolbox.ui \
    formgeostationary.ui

RESOURCES += \
    EUMETCastView.qrc \
    shaders.qrc

unix:INCLUDEPATH += /usr/include/GL /usr/include/freetype2 /usr/local/hdf5/include ../bz2 ../zlib128-dll/include ../meteosatlib  ../QSgp4
else:win32:INCLUDEPATH += "C:\Program Files\HDF_Group\HDF5\1.8.15\include" ../bz2 ../zlib128-dll/include ../meteosatlib ../QSgp4

CONFIG(release, debug|release) {
    #This is a release build
    unix:LIBS += -lpthread -lz -L/usr/ \
        -L$$_PRO_FILE_PWD_/../libs/linux_gplusplus/release -lmeteosat -lDISE -lJPEG -lWT -lT4 -lCOMP -lqsgp4 -lbz2 -lhdf5_serial
        #-L/usr/local/hdf5/lib -lhdf5
    else:win32:LIBS += \
        -L$$PWD/../../libs/win64_MSVC2012/release -lmeteosat -lDISE -lJPEG -lWT -lT4 -lCOMP -lqsgp4 -lbz2 -lzlib \
        -L"C:\Program Files\HDF_Group\HDF5\1.8.15\lib" -lhdf5

} else {
    #This is a debug build
unix:LIBS += -lpthread -lz -L/usr/ \
    -L$$_PRO_FILE_PWD_/../libs/linux_gplusplus/debug -lmeteosat -lDISE -lJPEG -lWT -lT4 -lCOMP -lqsgp4 -lbz2 -lhdf5_serial
    #-L/usr/local/hdf5/lib -lhdf5
else:win32:LIBS += \
    -L$$PWD/../../libs/win64_MSVC2012/debug -lmeteosat -lDISE -lJPEG -lWT -lT4 -lCOMP -lqsgp4 -lbz2 -lzlib \
    -L"C:\Program Files\HDF_Group\HDF5\1.8.15\lib" -lhdf5
}

CONFIG(release, debug|release): DEFINES += NDEBUG

DISTFILES += \
    EUMETCastView.ini \
    images/NE2_50M_SR_W_4096.jpg \
    images/Topography.jpg \
    images/ulukai/corona_bk.png \
    images/ulukai/corona_dn.png \
    images/ulukai/corona_ft.png \
    images/ulukai/corona_lf.png \
    images/ulukai/corona_rt.png \
    images/ulukai/corona_up.png \
    images/ulukai/readme.txt
