#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"glwidget.h"
#include<QDebug>
#include <QSettings>
#include<QFileDialog>
#include<QDir>
#include<QMessageBox>
#include<QString>
#include<QPixmap>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SaveSettings();

    void LoadSettings();

    QString CheckCorrectInput(QString text, int min, int max);



private slots:
    void on_BackRedSlider_valueChanged(int value);

    void on_BackGreenSlider_valueChanged(int value);

    void on_BackBlueSlider_valueChanged(int value);

    void on_VertexRedSlider_valueChanged(int value);

    void on_VertexGreenSlider_valueChanged(int value);

    void on_VertexBlueSlider_valueChanged(int value);

    void on_Scale_valueChanged(int value);

    void on_Open_clicked();

    void on_ShapeSquare_clicked();

    void on_ShapeRound_clicked();

    void on_LineSolid_clicked();

    void on_LineStipple_clicked();

    void on_Ortho_clicked();

    void on_Perspective_clicked();

    void on_EdgeRedSlider_valueChanged(int value);

    void on_EdgeGreenSlider_valueChanged(int value);

    void on_EdgeBlueSlider_valueChanged(int value);

    void on_ScaleEdge_valueChanged(int value);

    void on_radioButton_Points_clicked(bool checked);

    void on_radioButton_Lines_clicked(bool checked);

    void on_JPG_clicked();

    void on_BMP_clicked();

    void on_ShiftX_valueChanged(int value);

    void on_ShiftY_valueChanged(int value);

    void on_ShiftZ_valueChanged(int value);

    void on_RotationX_valueChanged(int value);

    void on_RotationY_valueChanged(int value);

    void on_RotationZ_valueChanged(int value);

    void on_Save_clicked();

    void on_Reset_clicked();

    void on_MashScale_valueChanged(int value);


    void on_ValueShiftX_editingFinished();

    void on_ValueShiftY_editingFinished();

    void on_ValueShiftZ_editingFinished();

    void on_BackRedValue_editingFinished();

    void on_BackGreenValue_editingFinished();

    void on_BackBlueValue_editingFinished();

    void on_VertexRedValue_editingFinished();

    void on_VertexGreenValue_editingFinished();

    void on_VertexBlueValue_editingFinished();

    void on_ScaleValue_editingFinished();

    void on_EdgeRedValue_editingFinished();

    void on_EdgeGreenValue_editingFinished();

    void on_EdgeBlueValue_editingFinished();

    void on_ScaleEdgeValue_editingFinished();

    void on_ValueRotationX_editingFinished();

    void on_ValueRotationY_editingFinished();

    void on_ValueRotationZ_editingFinished();

    void on_ValueMashScale_editingFinished();

private:
    Ui::MainWindow *ui;

};
#endif // MAINWINDOW_H
