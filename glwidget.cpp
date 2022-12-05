#include "glwidget.h"


GLWidget::GLWidget(QWidget *parent):QGLWidget(parent)
{
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateGL()));
    timer.start(30);
    new_array = new double[count_vertex*3] {};
    array = new double[count_vertex*3] {
//            0.0,  0.8, -0.8,
//           -0.8, -0.8, -0.8,
//            0.8, -0.8, -0.8
            0,0,0,
            -0.5, -0.5, 0.5,
             0.5, -0.5, 0.5,
             0.5, 0.5, 0.5,
            -0.5, 0.5, 0.5,
            -0.5, -0.5, -0.5,
             0.5, -0.5, -0.5,
             0.5, 0.5, -0.5,
            -0.5, 0.5, -0.5
    };

    for(size_t i=0; i<count_vertex*3; i++){
        new_array[i]=array[i];
    }
}


GLWidget::~GLWidget(){
    delete new_array;
    delete array;
}


//GLuint index_edge[]={
//    0,1,2

//};




//float vertices_cube1[27] = {0,    0,    0,    -0.5, -0.5, 0.5,  0.5,
//                            -0.5, 0.5,  0.5,  0.5,  0.5,  -0.5, 0.5,
//                            0.5,  -0.5, -0.5, -0.5, 0.5,  -0.5, -0.5,
//                            0.5,  0.5,  -0.5, -0.5, 0.5,  -0.5};

unsigned int index_edge[] = {
    1, 2, 2, 3, 3, 1,
    1, 3, 3, 4, 4, 1,
    1, 2, 2, 6, 6, 1,
    1, 5, 5, 6, 6, 1,
    2, 3, 3, 7, 7, 2,
    2, 6, 6, 7, 7, 2,
    5,6,6,8,8,5,
    6,7,7,8,8,6,
    1,4,4,5,5,1,
    4,5,5,8,8,4,
    4,3,3,7,7,4,
    4,8,8,7,7,4


};

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}


void GLWidget::ShiftX(){
    for(size_t i=0; i<count_vertex*3; i+=3){

        new_array[i]+=shiftx-(new_array[i]-array[i]);
        qDebug() << new_array[i]<<"   "<< new_array[i+1]<<"   "<< new_array[i+2];
    }
}

void GLWidget::ShiftY()
{
    for(size_t i=1; i<count_vertex*3; i+=3){
        new_array[i]+=shifty-(new_array[i]-array[i]);
        qDebug() << new_array[i-1]<<"   "<< new_array[i]<<"   "<< new_array[i+1];
    }
}

void GLWidget::ShiftZ()
{
    for(size_t i=2; i<count_vertex*3; i+=3){
        new_array[i]+=shiftz-(new_array[i]-array[i]);
        qDebug() << new_array[i-2]<<"   "<< new_array[i-1]<<"   "<< new_array[i];
    }
}

void GLWidget::RotationX(){
    for(size_t i=0; i<count_vertex*3; i+=3){
        double y = new_array[i+1];
        double z = new_array[i+2];
        new_array[i+1] = (cos(rotx) * y - sin(rotx) * z);
        new_array[i+2] = (sin(rotx) * y + cos(rotx) * z);
        qDebug() << new_array[i]<<"   "<< new_array[i+1]<<"   "<< new_array[i+2];
    }

}

void GLWidget::RotationY()
{
    for(size_t i=0; i<count_vertex*3; i+=3){
        new_array[i] = cos(roty)*array[i] + sin(roty) * array[i+2];
        new_array[i+2] = -sin(roty) * array[i] + cos(roty) * array[i+2];
        qDebug() << new_array[i]<<"   "<< new_array[i+1]<<"   "<< new_array[i+2];
    }
}

void GLWidget::RotationZ()
{
    for(size_t i=0; i<count_vertex*3; i+=3){
        new_array[i] = cos(rotz) * array[i] + sin(rotz) * array[i+1];
        new_array[i+1] = -sin(rotz) * array[i] + cos(rotz) * array[i+1];
        qDebug() << new_array[i]<<"   "<< new_array[i+1]<<"   "<< new_array[i+2];
    }
}

void GLWidget::Repaint()
{
    if(flagx){
        ShiftX();
        flagx=false;
    } else if(flagy){
        ShiftY();
        flagy=false;
    } else if(flagz){
        ShiftZ();
        flagz=false;
    } else if(flag_rotx){
        RotationX();
        flag_rotx=false;
    } else if(flag_roty){
        RotationY();
        flag_roty=false;
    } else if(flag_rotz){
        RotationZ();
        flag_rotz=false;
    }

}


void GLWidget::paintGL(){
    glMatrixMode(GL_PROJECTION);
    glClearColor(red_background_color, green_background_color, blue_background_color, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(ortho){
        glOrtho(-1,1,-1,1, -2, 2);
    } else {
        glFrustum(-1.5, 1.5, -1.5, 1.5, 1, 10);
        glTranslated(0,0,-2.5);
    }



    if(point && !lines){
        PaintPoints();
    } else if (!point && lines){
        PaintLines();
    } else if (point && lines){
        PaintPoints();
        PaintLines();
    }
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0,0,width,height);
}


void GLWidget::PaintPoints()
{
    glPointSize(paint_scale);
    if(square){
        PaintPointsArray();
    }else {
        PaintRoundPoints();
    }
}

void GLWidget::PaintPointsArray(){
    glColor3d(red_vertex_color, green_vertex_color, blue_vertex_color);
    Repaint();


    glVertexPointer(3,GL_DOUBLE,0,new_array);
    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS,1,count_vertex-1);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void GLWidget::PaintRoundPoints(){
    glEnable(GL_POINT_SMOOTH);
        PaintPointsArray();
    glDisable(GL_POINT_SMOOTH);
}

void GLWidget::PaintLines()
{
    glLineWidth(edge_scale);
    if(solid){
        PaintSolidLines();
    } else {
        PaintStippleLines();
    }
}

void GLWidget::PaintSolidLines(){
    glColor3f(red_edge_color, green_edge_color, blue_edge_color);

    Repaint();

    glVertexPointer(3,GL_DOUBLE,0,new_array);
    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_LINES,count_index, GL_UNSIGNED_INT, index_edge);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::PaintStippleLines(){
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x00ff);
        PaintSolidLines();
    glDisable(GL_LINE_STIPPLE);
}

void GLWidget::ScreenshotJPG(QString fileName){
    this->grabFrameBuffer().save(fileName+".jpg");
}

void GLWidget::ScreenshotBMP(QString fileName){
    this->grabFrameBuffer().save(fileName+".bmp");
}
