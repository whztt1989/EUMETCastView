#ifndef OPTIONS_H
#define OPTIONS_H

#include <list>
#include <string>
#include <time.h>
#include <qstringlist.h>
#include <QColor>
#include <QRect>


class Options 
{
public:
	Options();
	void Initialize();
    void checkStringListValues();
	void Save();

/* Calendar date and time (UTC) */
	struct tm utc;
	QStringList tlelist;
	QStringList catnbrlist;
    int zoomfactoravhrr;
    int zoomfactormeteosat;
    int zoomfactorprojection;
    int zoomfactorviirs;
    QStringList segmentdirectorylist;
    QStringList segmentdirectorylistinc;
    bool buttonMetop;
    bool buttonNoaa;
    bool buttonGAC;
    bool buttonHRP;
    bool buttonVIIRS;
    bool buttonRealTime;
    bool buttonEqualization;
    int nbrofvisiblesegments;
    int realminutesshown;
    int nbrofhours;


    QStringList metop_invlist, noaa_invlist, gac_invlist, hrp_invlist, viirs_invlist;
    bool sattrackinimage;

    double getObsLat() { return(obslat); }
	void setObsLat(const double lat) { obslat = lat; }
	double getObsLon() { return(obslon); }
	void setObsLon(const double lon) { obslon = lon; }
	double getObsAlt() { return(obsalt); }
	void setObsAlt(const double alt) { obsalt = alt; }
	void deleteTleFile( QString sel );
    bool addTleFile( QString sel );

    void deleteSegmentDirectory( QString sel );
    QStringList channellistmetop;
    QStringList channellistnoaa;
    QStringList channellistgac;
    QStringList channellisthrp;
    QStringList channellistviirs;

    QStringList stationlistname;
    QStringList stationlistlon;
    QStringList stationlistlat;

    QStringList geostationarylistlon;
    QStringList geostationarylistname;

    QString segmenttype;
    QString backgroundimage2D;
    QString backgroundimage3D;
    QStringList tlesources;
    QString gshhsglobe1;
    QString gshhsglobe2;
    QString gshhsglobe3;
    QString gshhsoverlay1;
    QString gshhsoverlay2;
    QString gshhsoverlay3;
    QString sathorizoncolor;
    QString sattrackcolor;
    QString satsegmentcolor;
    QString satsegmentcolorsel;
    QString globeoverlaycolor1;
    QString globeoverlaycolor2;
    QString globeoverlaycolor3;
    QString imageoverlaycolor1;
    QString imageoverlaycolor2;
    QString imageoverlaycolor3;
    QString globelonlatcolor;
    QString maplccextentcolor;
    QString mapgvpextentcolor;
    QString projectionoverlaycolor1;
    QString projectionoverlaycolor2;
    QString projectionoverlaycolor3;
    QString projectionoverlaylonlatcolor;

    QString skyboxup;
    QString skyboxdown;
    QString skyboxleft;
    QString skyboxright;
    QString skyboxfront;
    QString skyboxback;


    bool textureOn;
    bool stationnameOn;
    bool lightingOn;
    bool imageontextureOnMet;
    bool imageontextureOnAVHRR;
    bool imageontextureOnVIIRS;
    bool udpmessages;
    bool gshhsglobe1On;
    bool gshhsglobe2On;
    bool gshhsglobe3On;
    bool graytextureOn;

    int currenttoolbox; // LLC - GVP - Stereographic
    int currenttabwidget; // AVHRR - VIIRS - Geostationary - Projections
    int parallel1;
    int parallel2;
    int centralmeridian;
    int latitudeoforigin;
    int mapextentnorth;
    int mapextentsouth;
    int mapextentwest;
    int mapextenteast;
    bool mapextentlamberton;
    bool mapextentperspectiveon;
    int mapheight;
    int mapwidth;
    double mapgvplon;
    double mapgvplat;
    int mapgvpheight;
    double mapgvpscale;
    double maplccscalex;
    double maplccscaley;
    double mapsglat;
    double mapsglon;
    double mapsgscale;
    int mapsgpanvert;
    int mapsgpanhorizon;
    double mapsgradius;
    double meteosatgamma;
    double yawcorrection;
    int smoothprojectiontype;
    bool gridonprojection;
    float clahecliplimit;


    QByteArray ephemsplittersizes;
    QByteArray mainwindowgeometry;
    QByteArray windowstate;
    QString localdirremote;
    QString dirremote;
	double obslat, obslon, obsalt;

    // Global variable not saved
    int channelontexture;
    bool fbo_changed;
    bool texture_changed;
    bool bPhongModel;

    int lastcomboMet006;
    int lastcomboMet008;
    int lastcomboMet016;
    int lastcomboMet039;
    int lastcomboMet062;
    int lastcomboMet073;
    int lastcomboMet087;
    int lastcomboMet097;
    int lastcomboMet108;
    int lastcomboMet120;
    int lastcomboMet134;

    bool lastinverseMet006;
    bool lastinverseMet008;
    bool lastinverseMet016;
    bool lastinverseMet039;
    bool lastinverseMet062;
    bool lastinverseMet073;
    bool lastinverseMet087;
    bool lastinverseMet097;
    bool lastinverseMet108;
    bool lastinverseMet120;
    bool lastinverseMet134;

    int lastinputprojection;
    int lastVIIRSband;

    int lastcomboM1;
    int lastcomboM2;
    int lastcomboM3;
    int lastcomboM4;
    int lastcomboM5;
    int lastcomboM6;
    int lastcomboM7;
    int lastcomboM8;
    int lastcomboM9;
    int lastcomboM10;
    int lastcomboM11;
    int lastcomboM12;
    int lastcomboM13;
    int lastcomboM14;
    int lastcomboM15;
    int lastcomboM16;

    bool lastinverseM1;
    bool lastinverseM2;
    bool lastinverseM3;
    bool lastinverseM4;
    bool lastinverseM5;
    bool lastinverseM6;
    bool lastinverseM7;
    bool lastinverseM8;
    bool lastinverseM9;
    bool lastinverseM10;
    bool lastinverseM11;
    bool lastinverseM12;
    bool lastinverseM13;
    bool lastinverseM14;
    bool lastinverseM15;
    bool lastinverseM16;

}; 


#endif
