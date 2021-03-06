#include "pixgeoconversion.h"
#include "globals.h"
#include <QDebug>


pixgeoConversion::pixgeoConversion()
{
}

/**************************************************************
 * function pixcoord2geocoord                                 *
 *                                                            *
 * PURPOSE:                                                   *
 *   return the latitude and longitude of an MSG image        *
 *   for a given pair of pixel column and row.                *
 *   (based on the formulas given in Ref. [1])                *
 *                                                            *
 *                                                            *
 * DEPENDENCIES:                                              *
 *   none                                                     *
 *                                                            *
 *                                                            *
 * REFERENCE:                                                 *
 * [1] LRIT/HRIT Global Specification                         *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                       *
 *     for the parameters used in the program.                *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific          *
 *     Implementation, EUMETSAT Document,                     *
 *     (EUM/MSG/SPE/057, Issue 6, 21. June 2006).             *
 *                                                            *
 *                                                            *
 * MODIFICATION HISTORY:                                      *
 *   Version 1.01                                             *
 *  08.08.2008 removed a bug in longi = atan(s2/s1) statement *
 *   Copyright(c) EUMETSAT 2005, 2009                         *
 *                                                            *
 *                                                            *
 * INPUT:                                                     *
 *   row    (int) row-value of the pixel                      *
 *   column (int) line-value of the pixel                     *
 *   coff   (int) coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *   loff   (int) coefficient of the scalling function        *
 *                (see page 28, Ref [1])                      *
 *                                                            *
 * OUTPUT:                                                    *
 *   latitude  (double) geographic Latitude of the given      *
 *                      pixel [Degrees]                       *
 *   longitude (double) geographic Longitude of the given     *
 *                      pixel [Degrees]                       *
 *                                                            *
 *                                                            *
 *************************************************************/

int pixgeoConversion::pixcoord2geocoord(double sub_lon_deg, int column, int row, long coff, long loff, long long cfac, long long lfac, double *latitude, double *longitude)
{

  double s1=0.0, s2=0.0, s3=0.0, sn=0.0, sd=0.0, sxy=0.0, sa=0.0;
  double x=0.0, y=0.0;
  double longi=0.0, lati=0.0;
  double sub_lon = sub_lon_deg*PI/180.0;

  int c=0, l=0;


  c=column;
  l=row;


  /*  calculate viewing angle of the satellite by use of the equation  */
  /*  on page 28, Ref [1]. */

  x = pow(2,16) * ( (double)c - (double)coff) / (double)cfac;
  y = pow(2,16) * ( (double)l - (double)loff) / (double)lfac;


  /*  now calculate the inverse projection */

  /* first check for visibility, whether the pixel is located on the Earth   */
  /* surface or in space. 						     */
  /* To do this calculate the argument to sqrt of "sd", which is named "sa". */
  /* If it is negative then the sqrt will return NaN and the pixel will be   */
  /* located in space, otherwise all is fine and the pixel is located on the */
  /* Earth surface.                                                          */

  sa =  pow(SAT_HEIGHT * cos(x) * cos(y),2 )  - (cos(y)*cos(y) + (double)1.006803 * sin(y)*sin(y)) * (double)1737121856. ;

  //if (sa_max < sa)
  //    sa_max = sa;  //  40681000
  /* produce error values */
  if ( sa <= 450000.0 ) {
    *latitude = -999.999;
    *longitude = -999.999;
    return (-1);
  }


  /* now calculate the rest of the formulas using equations on */
  /* page 25, Ref. [1]  */

//  sd = sqrt( pow(SAT_HEIGHT * cos(x) * cos(y),2)
//         - (cos(y)*cos(y) + (double)1.006803 * sin(y)*sin(y)) * (double)1737121856. );
  sd = sqrt(sa);
  sn = (SAT_HEIGHT * cos(x) * cos(y) - sd)
    / ( cos(y)*cos(y) + (double)1.006803 * sin(y)*sin(y) ) ;

  s1 = SAT_HEIGHT - sn * cos(x) * cos(y);
  s2 = sn * sin(x) * cos(y);
  s3 = -sn * sin(y);

  sxy = sqrt( s1*s1 + s2*s2 );

  /* using the previous calculations the inverse projection can be  */
  /* calculated now, which means calculating the lat./long. from    */
  /* the pixel row and column by equations on page 25, Ref [1].     */

  longi = atan(s2/s1) + sub_lon;
  lati  = atan(((double)1.006803*s3)/sxy);
  /* convert from radians into degrees */
  *latitude = lati*180./PI;
  *longitude = longi*180./PI;



  return (0);

}

/**********************************************************
 * function geocoord2pixcoord                             *
 *                                                        *
 * PURPOSE:                                               *
 *   return the pixel column and line of an MSG image     *
 *   for a given pair of latitude/longitude.              *
 *   (based on the formulas given in Ref. [1])            *
 *                                                        *
 *                                                        *
 * DEPENDENCIES:                                          *
 *   up to now none                                       *
 *                                                        *
 *                                                        *
 * REFERENCE:                                             *
 * [1] LRIT/HRIT Global Specification                     *
 *     (CGMS 03, Issue 2.6, 12.08.1999)                   *
 *     for the parameters used in the program             *
 * [2] MSG Ground Segment LRIT/HRIT Mission Specific      *
 *     Implementation, EUMETSAT Document,                 *
 *     (EUM/MSG/SPE/057, Issue 6, 21. June 2006).         *
 *                                                        *
 *                                                        *
 * MODIFICATION HISTORY:                                  *
 *   Version 1.01                                         *
  *   (c) EUMETSAT 2005, 2009                             *
 *                                                        *
 *                                                        *
 * INPUT:                                                 *
 *   latitude  (double) geographic Latitude of a point    *
 *                      [Degrees]                         *
 *   longitude (double) geographic Longitude of a point   *
 *                      [Degrees]                         *
 *   coff (int)   coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *   loff (int)   coefficient of the scalling function    *
 *                (see page 28, Ref [1])                  *
 *                                                        *
 *                                                        *
 * OUTPUT:                                                *
 *   row    (int) row-value of the wanted pixel           *
 *   column (int) column-value of the wanted pixel        *
 *                                                        *
 *********************************************************/

int pixgeoConversion::geocoord2pixcoord(double sub_lon_deg, double latitude, double longitude, long coff, long loff, long long cfac, long long lfac, int *column, int *row)
{
  int ccc=0, lll=0;

  double lati=0.0, longi=0.0;
  double c_lat=0.0;
  double lat=0.0;
  double lon=0.0;
  double r1=0.0, r2=0.0, r3=0.0, rn=0.0, re=0.0, rl=0.0;
  double xx=0.0, yy=0.0;
  double cc=0.0, ll=0.0;
  double dotprod=0.0;

  double sub_lon = sub_lon_deg*PI/180.0;
  lati= latitude;
  longi= longitude;

  /* check if the values are sane, otherwise return error values */
  if (lati < -90.0 || lati > 90.0 || longi < -180.0 || longi > 180.0 ){
    *row = -999;
    *column = -999;
    return (-1);
  }


  /* convert them to radiants */
  lat = lati*PI / (double)180.;
  lon = longi *PI / (double)180.;

  /* calculate the geocentric latitude from the          */
  /* geograhpic one using equations on page 24, Ref. [1] */

  c_lat = atan ( ((double)0.993243*(sin(lat)/cos(lat)) ));


  /* using c_lat calculate the length form the Earth */
  /* centre to the surface of the Earth ellipsoid    */
  /* equations on page 23, Ref. [1]                  */

  re = R_POL / sqrt( ((double)1.0 - (double)0.00675701 * cos(c_lat) * cos(c_lat) ) );


  /* calculate the forward projection using equations on */
  /* page 24, Ref. [1]                                        */

  rl = re;
  r1 = SAT_HEIGHT - rl * cos(c_lat) * cos(lon - sub_lon);
  r2 = - rl *  cos(c_lat) * sin(lon - sub_lon);
  r3 = rl * sin(c_lat);
  rn = sqrt( r1*r1 + r2*r2 +r3*r3 );


  /* check for visibility, whether the point on the Earth given by the */
  /* latitude/longitude pair is visible from the satellte or not. This */
  /* is given by the dot product between the vectors of:               */
  /* 1) the point to the spacecraft,			               */
  /* 2) the point to the centre of the Earth.			       */
  /* If the dot product is positive the point is visible otherwise it  */
  /* is invisible.						       */

  dotprod = r1*(rl * cos(c_lat) * cos(lon - sub_lon)) - r2*r2 - r3*r3*(pow((R_EQ/R_POL),2));

  //qDebug() << QString("dotprod = %1 ").arg(dotprod);

  if (dotprod <= 26.7e6){
    *column = -999;
    *row = -999;
    return (-1);
  }


  /* the forward projection is x and y */

  xx = atan( (-r2/r1) );
  yy = asin( (-r3/rn) );


  /* convert to pixel column and row using the scaling functions on */
  /* page 28, Ref. [1]. And finding nearest integer value for them. */


  cc = coff + xx *  pow(2,-16) * cfac;
  ll = loff + yy *  pow(2,-16) * lfac;


  ccc=nint(cc);
  lll=nint(ll);

  *column = ccc;
  *row = lll;


  return (0);

}

int pixgeoConversion::geocoord2pixcoordrad(double sub_lon_deg, double lat_rad, double lon_rad, long coff, long loff, long long cfac, long long lfac, int *column, int *row)
{
  int ccc=0, lll=0;

  double lati=0.0, longi=0.0;
  double c_lat=0.0;
  double lat=0.0;
  double lon=0.0;
  double r1=0.0, r2=0.0, r3=0.0, rn=0.0, re=0.0, rl=0.0;
  double xx=0.0, yy=0.0;
  double cc=0.0, ll=0.0;
  double dotprod=0.0;
  double sub_lon = sub_lon_deg*PI/180.0;

  lati= lat_rad;
  longi= lon_rad;

  /* check if the values are sane, otherwise return error values */
  if (lati < -PI/2 || lati > PI/2 || longi < -PI || longi > PI ){
    *row = -999;
    *column = -999;
    return (-1);
  }


  /* convert them to radiants */
  lat = lati;
  lon = longi;

  /* calculate the geocentric latitude from the          */
  /* geograhpic one using equations on page 24, Ref. [1] */

  c_lat = atan ( ((double)0.993243*(sin(lat)/cos(lat)) ));


  /* using c_lat calculate the length form the Earth */
  /* centre to the surface of the Earth ellipsoid    */
  /* equations on page 23, Ref. [1]                  */

  re = R_POL / sqrt( ((double)1.0 - (double)0.00675701 * cos(c_lat) * cos(c_lat) ) );


  /* calculate the forward projection using equations on */
  /* page 24, Ref. [1]                                        */

  rl = re;
  r1 = SAT_HEIGHT - rl * cos(c_lat) * cos(lon - sub_lon);
  r2 = - rl *  cos(c_lat) * sin(lon - sub_lon);
  r3 = rl * sin(c_lat);
  rn = sqrt( r1*r1 + r2*r2 +r3*r3 );


  /* check for visibility, whether the point on the Earth given by the */
  /* latitude/longitude pair is visible from the satellte or not. This */
  /* is given by the dot product between the vectors of:               */
  /* 1) the point to the spacecraft,			               */
  /* 2) the point to the centre of the Earth.			       */
  /* If the dot product is positive the point is visible otherwise it  */
  /* is invisible.						       */

  dotprod = r1*(rl * cos(c_lat) * cos(lon - sub_lon)) - r2*r2 - r3*r3*(pow((R_EQ/R_POL),2));

  if (dotprod <= 0 ){
    *column = -999;
    *row = -999;
    return (-1);
  }


  /* the forward projection is x and y */

  xx = atan( (-r2/r1) );
  yy = asin( (-r3/rn) );


  /* convert to pixel column and row using the scaling functions on */
  /* page 28, Ref. [1]. And finding nearest integer value for them. */


  cc = coff + xx *  pow(2,-16) * cfac;
  ll = loff + yy *  pow(2,-16) * lfac;


  ccc=nint(cc);
  lll=nint(ll);

  *column = ccc;
  *row = lll;


  return (0);

}



/* this function returns the nearest integer to the value val */
/* and is used in function geocoord2pixcoord */

int pixgeoConversion::nint(double val)
{
  double a=0.0; /* integral  part of val */
  double b=0.0; /* frational part of val */

  b = modf(val,&a);

  if ( b > 0.5 ){
    val = ceil(val);
  }
  else{
    val = floor(val);
  }

  return (int)val;

}
