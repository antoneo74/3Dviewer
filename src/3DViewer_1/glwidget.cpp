#include "glwidget.h"

GLWidget::GLWidget(QWidget *parent):QOpenGLWidget(parent)
{
    InitObj();
}

GLWidget::~GLWidget(){
    if (new_array) {
        delete new_array;
        new_array=NULL;
    }
    free_object(&obj);
}

void GLWidget::initializeGL(){
    initializeOpenGLFunctions();
    glEnable(GL_DEPTH_TEST);
}

void GLWidget::Transform(){
    scale(&obj, new_array, mash_scale);
    rotate_vertices(&obj, new_array,rotx, roty, rotz);
    shift(&obj,new_array,max,shiftx,shifty,shiftz);
}

void GLWidget::ClearScreen(){

    if (new_array) {
        delete new_array;
        new_array=NULL;
    }
    free_object(&obj);
}

void GLWidget::InitObj()
{
    obj.count_faces=0;
    obj.count_index=0;
    obj.count_vertex=1;
    obj.indexies=NULL;
    obj.vertices=NULL;
}

void GLWidget::Start()
{
    max=min=0;
    new_array = new float[obj.count_vertex*3] {};
    for(size_t i=0; i<obj.count_vertex*3; i++){
        new_array[i]=obj.vertices[i];
        if (new_array[i]>max) max = new_array[i];
        if (new_array[i]<min) min = new_array[i];
    }
    int range = 1;
    min*=range;
    max*=range;

    paintGL();
}

void GLWidget::paintGL(){
    glMatrixMode(GL_PROJECTION);
    glClearColor(red_background_color, green_background_color, blue_background_color, 1);
    glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    if(ortho){
        glOrtho(min,max,min,max, -(max-min)*10, (max-min)*10);
    } else {
        glFrustum(min, max, min, max, max-min, (max-min)*100);
        glTranslatef(0,0,-0.1);
        glTranslatef(0,0,-(max-min)*2);
    }

    if(new_array){
        if(point && !lines){
            PaintPoints();
        } else if (!point && lines){
            PaintLines();
        } else if (point && lines){
            PaintPoints();
            PaintLines();
        }
        update();
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
    Transform();

    glVertexPointer(3,GL_FLOAT,0,new_array);
    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS,1,obj.count_vertex-1);
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

    Transform();

    //glVertexPointer(3,GL_FLOAT,0,new_array);
    glEnableClientState(GL_VERTEX_ARRAY);
        glDrawElements(GL_LINES,obj.count_index*2, GL_UNSIGNED_INT, obj.indexies);
    glDisableClientState(GL_VERTEX_ARRAY);
}

void GLWidget::PaintStippleLines(){
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1,0x00ff);
        PaintSolidLines();
    glDisable(GL_LINE_STIPPLE);
}

void GLWidget::ScreenshotJPG(QString fileName){
    this->grabFramebuffer().save(fileName+".jpg");
}

void GLWidget::ScreenshotBMP(QString fileName){
    this->grabFramebuffer().save(fileName+".bmp");
}

