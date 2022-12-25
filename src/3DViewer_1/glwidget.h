#ifndef GLWIDGET_H
#define GLWIDGET_H
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QTimer>
#include<QFileDialog>
#include<QDebug>
#include<cmath>

#include "QtGifImage/src/gifimage/qgifimage.h"

#ifdef __cplusplus
extern "C" {
#endif

#include "../load_object.h"
#include "../transform.h"

#ifdef __cplusplus
}
#endif

class GLWidget: public QOpenGLWidget, protected QOpenGLFunctions
{
private:
    QTimer timer;

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();

    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int width, int height) override;
    void PaintPoints();
    void PaintPointsArray();
    void PaintRoundPoints();
    void PaintLines();
    void PaintSolidLines();
    void PaintStippleLines();
    void ScreenshotJPG(QString);
    void ScreenshotBMP(QString);
    void Transform();
    void Start();
    void ClearScreen();
    void InitObj();

    float red_background_color{0.15};
    float green_background_color{0.6};
    float blue_background_color{0.9};

    float shiftx{0};
    float shifty{0};
    float shiftz{0};

    float rotx{0};
    float roty{0};
    float rotz{0};

    float red_vertex_color{1.0};
    float green_vertex_color{0.1};
    float blue_vertex_color{0.1};

    float red_edge_color{0.2};
    float green_edge_color{0.3};
    float blue_edge_color{0.5};

    float paint_scale{1};
    float edge_scale{1};
    float mash_scale{0};

    bool point {true};
    bool lines {true};
    bool ortho {true};
    bool solid {true};
    bool square {true};

    float* new_array=NULL;


    Object obj;

    float max{0};
    float min{0};

};

#endif // GLWIDGET_H
