#ifndef GLWIDGET_H
#define GLWIDGET_H
#include<QOpenGLWidget>
#include<QOpenGLFunctions>
#include<QGLWidget>
#include<QTimer>
#include<QDebug>
#include<cmath>



class GLWidget: public QGLWidget, protected QOpenGLFunctions
{
private:
    QTimer timer;

private slots:
    void Repaint();


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
    void ShiftX();
    void ShiftY();
    void ShiftZ();
    void RotationX();
    void RotationY();
    void RotationZ();



    double red_background_color{0.15};
    double green_background_color{0.6};
    double blue_background_color{0.9};

    double shiftx{0};
    double shifty{0};
    double shiftz{0};
    bool flagx{false};
    bool flagy{false};
    bool flagz{false};

    double rotx{0};
    double roty{0};
    double rotz{0};
    bool flag_rotx{false};
    bool flag_roty{false};
    bool flag_rotz{false};


    double red_vertex_color{1.0};
    double green_vertex_color{0.1};
    double blue_vertex_color{0.1};

    double red_edge_color{0.2};
    double green_edge_color{0.3};
    double blue_edge_color{0.5};

    double paint_scale{1};
    double edge_scale{1};
    double mash_scale{0};

    bool point {true};
    bool lines {true};
    bool ortho {true};
    bool solid {true};
    bool square {true};

    unsigned count_vertex{9};
    unsigned count_index{72};
    double* new_array;
    double* array;

};

#endif // GLWIDGET_H
