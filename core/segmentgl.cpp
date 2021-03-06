#include "segmentgl.h"
#include "options.h"

extern Options opts;

SegmentGL::SegmentGL(QOpenGLShaderProgram *prog, SatelliteList *satlist, AVHRRSatellite *seglist )
{

    sats = satlist;
    segs = seglist;

    program = prog;

    initializeOpenGLFunctions();

    program->bind();

    vao.create();
    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

    positionsBuf.create();
    positionsBuf.setUsagePattern(QOpenGLBuffer::DynamicDraw);
    positionsBuf.bind();

    nbrOfVertices = 50;
    positionsBuf.allocate( nbrOfVertices * 3 * sizeof(GLfloat));

    vertexPosition = program->attributeLocation("VertexPosition");
    program->enableAttributeArray(vertexPosition);
    program->setAttributeBuffer(vertexPosition, GL_FLOAT, 0, 3);


}

/*

It is occasionally necessary to project points from 3D to 2D in software.  A
sample application is the rendering HUD effects like targeting boxes and
character names in a game.  The following code transforms and projects a 3D
point or vector by the current OpenGL matrices and returns a 2D vector with
associated depth value.  The 2D vector is in the screen coordinate frame, where
y increases from 0 at the top of the screen to height - 1 at the bottom and x
increases from 0 at the left to width - 1 at the right.

Morgan McGuire
matrix@graphics3d.com



Vector3 glProject(const Vector4& v) {
    // Get the matrices
    double modelView[16];
    double projection[16];
    glGetDoublev(GL_MODELVIEW_MATRIX, modelView);
    glGetDoublev(GL_PROJECTION_MATRIX, projection);

    // Compose the matrices into a net row-major transformation
    Vector4 transformation[4];
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 4; ++c) {
            transformation[r][c] = 0;
            for (int i = 0; i < 4; ++i) {
                // OpenGL matrices are column major
                transformation[r][c] += projection[r + i * 4] * modelView[i + c * 4];
            }
        }
    }

    // Transform the vertex
    Vector4 result;
    for (r = 0; r < 4; ++r) {
        result[r] = transformation[r].dot(v);
    }

    // Homogeneous division
    const double rhw = 1 / result.w;

    return Vector3((result.x * rhw + 1) * width / 2,
                   (1 - result.y * rhw) * height / 2,
                   rhw);
}
*/



void SegmentGL::render(QMatrix4x4 projection, float dist, QQuaternion quat, int width, int height)
{

    //qDebug() << "in  SegmentGL::Render()";

    QMatrix4x4 modelview;
    modelview.translate(0.0, 0.0, dist);
    modelview.rotate(quat);

    if (opts.buttonMetop && segs->seglmetop->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglmetop->GetSegmentlistptr()->begin();
        while ( segit != segs->seglmetop->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

    if (opts.buttonNoaa && segs->seglnoaa->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglnoaa->GetSegmentlistptr()->begin();
        while ( segit != segs->seglnoaa->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

    if (opts.buttonHRP && segs->seglhrp->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglhrp->GetSegmentlistptr()->begin();
        while ( segit != segs->seglhrp->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

    if (opts.buttonGAC && segs->seglgac->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglgac->GetSegmentlistptr()->begin();
        while ( segit != segs->seglgac->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

    if (opts.buttonVIIRSM && segs->seglviirsm->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglviirsm->GetSegmentlistptr()->begin();
        while ( segit != segs->seglviirsm->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

    if (opts.buttonVIIRSDNB && segs->seglviirsdnb->NbrOfSegments() > 0)
    {
        QList<Segment*>::iterator segit = segs->seglviirsdnb->GetSegmentlistptr()->begin();
        while ( segit != segs->seglviirsdnb->GetSegmentlistptr()->end() )
        {
            if(segs->getShowAllSegments())
            {
                RenderContour(*segit, projection, modelview, width, height);

            }
            else
            {
                if ((*segit)->segmentshow)
                {
                    RenderContour(*segit, projection, modelview, width, height);
                }
            }
            ++segit;
        }
    }

}

void SegmentGL::RenderContour(Segment *seg, QMatrix4x4 projection, QMatrix4x4 modelview, int width, int height)
{

    QVector3D vec;
    QVector3D pos;
    QVector<GLfloat> positions;
    QEci qeci;


    CalculateSegmentContour(&positions, seg->cornerpointfirst1.latitude, seg->cornerpointfirst1.longitude, seg->cornerpointlast1.latitude, seg->cornerpointlast1.longitude);
    CalculateSegmentContour(&positions,seg->cornerpointlast1.latitude, seg->cornerpointlast1.longitude, seg->cornerpointlast2.latitude, seg->cornerpointlast2.longitude);
    CalculateSegmentContour(&positions, seg->cornerpointlast2.latitude, seg->cornerpointlast2.longitude, seg->cornerpointfirst2.latitude, seg->cornerpointfirst2.longitude);
    CalculateSegmentContour(&positions,seg->cornerpointfirst2.latitude, seg->cornerpointfirst2.longitude, seg->cornerpointfirst1.latitude, seg->cornerpointfirst1.longitude);

    seg->qsgp4->getPosition(seg->minutes_since_state_vector, qeci);
    QGeodetic qgeo = qeci.ToGeo();
    double lat1 = qgeo.latitude;
    double lon1 = qgeo.longitude;

    seg->qsgp4->getPosition(seg->minutes_since_state_vector + seg->minutes_sensing, qeci);
    qgeo = qeci.ToGeo();
    double lat2 = qgeo.latitude;
    double lon2 = qgeo.longitude;

    CalculateSegmentContour(&positions, lat1, lon1, lat2, lon2);

    positionsBuf.bind();
    positionsBuf.write(0, positions.data(), positions.size() * sizeof(GLfloat));
    positionsBuf.release();

    QOpenGLVertexArrayObject::Binder vaoBinder(&vao);

    program->bind();
    program->setUniformValue("MVP", projection * modelview);
    QColor rendercolor(opts.satsegmentcolor);
    QColor rendercolorsel(opts.satsegmentcolorsel);

    if((*seg).segmentselected)
        program->setUniformValue("outcolor", QVector4D(rendercolorsel.redF(), rendercolorsel.greenF(), rendercolorsel.blueF(), 1.0f));
    else
        program->setUniformValue("outcolor", QVector4D(rendercolor.redF(), rendercolor.greenF(), rendercolor.blueF(), 1.0f));

    QMatrix3x3 norm = modelview.normalMatrix();
    program->setUniformValue("NormalMatrix", norm);

    glDrawArrays(GL_LINE_LOOP, 0, nbrOfVertices - 10);
    glDrawArrays(GL_LINE_STRIP, nbrOfVertices - 10, 10);


    float mvmatrix[16], projmatrix[16];
    QMatrix4x4 MVP;
    MVP = projection * modelview;

    float *ptr = modelview.data();
    for(int i = 0; i < 16; i++)
        mvmatrix[i] = *(ptr + i);

    ptr = projection.data();
    for(int i = 0; i < 16; i++)
        projmatrix[i] = *(ptr + i);

    QVector2D win;

    LonLat2PointRad((float)seg->cornerpointfirst1.latitude, (float)seg->cornerpointfirst1.longitude, &vec, 1.0);
    win = glhProjectf (vec, mvmatrix, projmatrix, width, height);
    seg->winvecend1 = win;

    LonLat2PointRad((float)seg->cornerpointfirst2.latitude, (float)seg->cornerpointfirst2.longitude, &vec, 1.0);
    win = glhProjectf (vec, mvmatrix, projmatrix, width, height);
    seg->winvecend2 = win;

    LonLat2PointRad((float)seg->cornerpointlast1.latitude, (float)seg->cornerpointlast1.longitude, &vec, 1.0);
    win = glhProjectf (vec, mvmatrix, projmatrix, width, height);
    seg->winvecend3 = win;

    LonLat2PointRad((float)seg->cornerpointlast2.latitude, (float)seg->cornerpointlast2.longitude, &vec, 1.0);
    win = glhProjectf (vec, mvmatrix, projmatrix, width, height);
    seg->winvecend4 = win;

    win = glhProjectf (seg->vec1, mvmatrix, projmatrix, width, height);
    seg->winvec1 = win;

    win = glhProjectf (seg->vec2, mvmatrix, projmatrix, width, height);
    seg->winvec2 = win;

}


QVector2D SegmentGL::glhProjectf(QVector3D obj, float *modelview, float *projection, int width, int height)
  {
      //Transformation vectors
      float fTempo[8];
      //Modelview transform
      fTempo[0]=modelview[0]*obj.x()+modelview[4]*obj.y()+modelview[8]*obj.z()+modelview[12];  //w is always 1
      fTempo[1]=modelview[1]*obj.x()+modelview[5]*obj.y()+modelview[9]*obj.z()+modelview[13];
      fTempo[2]=modelview[2]*obj.x()+modelview[6]*obj.y()+modelview[10]*obj.z()+modelview[14];
      fTempo[3]=modelview[3]*obj.x()+modelview[7]*obj.y()+modelview[11]*obj.z()+modelview[15];
      //Projection transform, the final row of projection matrix is always [0 0 -1 0]
      //so we optimize for that.
      fTempo[4]=projection[0]*fTempo[0]+projection[4]*fTempo[1]+projection[8]*fTempo[2]+projection[12]*fTempo[3];
      fTempo[5]=projection[1]*fTempo[0]+projection[5]*fTempo[1]+projection[9]*fTempo[2]+projection[13]*fTempo[3];
      fTempo[6]=projection[2]*fTempo[0]+projection[6]*fTempo[1]+projection[10]*fTempo[2]+projection[14]*fTempo[3];
      fTempo[7]=-fTempo[2];
      //The result normalizes between -1 and 1
//      if(fTempo[7]==0.0)	//The w value
//         return 0;
      fTempo[7]=1.0/fTempo[7];
      //Perspective division
      fTempo[4]*=fTempo[7];
      fTempo[5]*=fTempo[7];
      fTempo[6]*=fTempo[7];
      //Window coordinates
      //Map x, y to range 0-1
      QVector2D win((fTempo[4]*0.5+0.5)*width, (fTempo[5]*0.5+0.5)*height);
      //This is only correct when glDepthRange(0.0, 1.0)
      //windowCoordinate[2]=(1.0+fTempo[6])*0.5;	//Between 0 and 1
      return win;
  }


void SegmentGL::CalculateSegmentContour(QVector<GLfloat> *positions, float lat_first, float lon_first, float lat_last, float lon_last)
{
    QVector3D pos;

    double sinlatdiff = sin((lat_first-lat_last)/2);
    double sinlondiff = sin((lon_first-lon_last)/2);

    double sinpsi = sqrt(sinlatdiff * sinlatdiff + cos(lat_first)*cos(lat_last)*sinlondiff * sinlondiff);
    double delta = 2*asin(sinpsi);

    int nDelta = 10;
    double deltax = delta / (nDelta - 1);
    double lonpos, latpos, dlon, tc;

    tc = fmod(atan2(sin(lon_first-lon_last)*cos(lat_last), cos(lat_first)*sin(lat_last)-sin(lat_first)*cos(lat_last)*cos(lon_first-lon_last)) , 2 * PI);
    for (int pix = 0 ; pix < nDelta; pix++)
    {
        latpos = asin(sin(lat_first)*cos(deltax * pix)+cos(lat_first)*sin(deltax * pix)*cos(tc));
        dlon=atan2(sin(tc)*sin(deltax * pix)*cos(lat_first),cos(deltax * pix)-sin(lat_first)*sin(latpos));
        lonpos=fmod( lon_first-dlon + PI,2*PI )-PI;

        LonLat2PointRad(latpos, lonpos, &pos, 1.001f);

        positions->append(pos.x());
        positions->append(pos.y());
        positions->append(pos.z());
    }
}

SegmentGL::~SegmentGL()
{

}

