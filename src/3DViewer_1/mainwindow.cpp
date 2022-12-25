#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    LoadSettings();
    setlocale(LC_ALL, "en_US.UTF-8");
}

MainWindow::~MainWindow()
{
    SaveSettings();
    delete ui;
}


void MainWindow::SaveSettings()
{
   QSettings set("prog_settings", "conf");
   set.setValue("red_background_color", ui->Screen->red_background_color);
   set.setValue("green_background_color", ui->Screen->green_background_color);
   set.setValue("blue_background_color",ui->Screen->blue_background_color);
   set.setValue("red_vertex_color", ui->Screen->red_vertex_color);
   set.setValue("green_vertex_color", ui->Screen->green_vertex_color);
   set.setValue("blue_vertex_color",ui->Screen->blue_vertex_color);
   set.setValue("red_edge_color", ui->Screen->red_edge_color);
   set.setValue("green_edge_color", ui->Screen->green_edge_color);
   set.setValue("blue_edge_color",ui->Screen->blue_edge_color);
   set.setValue("radioButton_Points", ui->Screen->point);
   set.setValue("radioButton_Lines", ui->Screen->lines);
   set.setValue("Ortho", ui->Screen->ortho);
   set.setValue("paint_scale", ui->Screen->paint_scale);
   set.setValue("edge_scale", ui->Screen->edge_scale);
   set.setValue("ShapeSquare", ui->Screen->square);
   set.setValue("Solid", ui->Screen->solid);
   set.setValue("ShiftX", ui->Screen->shiftx);
   set.setValue("ShiftY", ui->Screen->shifty);
   set.setValue("ShiftZ", ui->Screen->shiftz);
   set.setValue("RotX", ui->RotationX->value());
   set.setValue("RotY", ui->RotationY->value());
   set.setValue("RotZ", ui->RotationZ->value());
   set.setValue("Mash_scale", ui->Screen->mash_scale);
}

void MainWindow::LoadSettings()
{
    QSettings set("prog_settings", "conf");
    ui->BackRedSlider->setValue(set.value("red_background_color",0).toFloat()*100);
    ui->BackGreenSlider->setValue(set.value("green_background_color",0).toFloat()*100);
    ui->BackBlueSlider->setValue(set.value("blue_background_color",0).toFloat()*100);
    ui->VertexRedSlider->setValue(set.value("red_vertex_color",0).toFloat()*100);
    ui->VertexGreenSlider->setValue(set.value("green_vertex_color",0).toFloat()*100);
    ui->VertexBlueSlider->setValue(set.value("blue_vertex_color",0).toFloat()*100);
    ui->Scale->setValue(set.value("paint_scale", ui->Screen->paint_scale).toInt());
    ui->EdgeRedSlider->setValue(set.value("red_edge_color",0).toFloat()*100);
    ui->EdgeGreenSlider->setValue(set.value("green_edge_color",0).toFloat()*100);
    ui->EdgeBlueSlider->setValue(set.value("blue_edge_color",0).toFloat()*100);
    ui->ScaleEdge->setValue(set.value("edge_scale", ui->Screen->edge_scale).toInt());
    ui->Screen->point = set.value("radioButton_Points",0).toBool();
    ui->radioButton_Points->setChecked(ui->Screen->point);
    ui->Screen->lines = set.value("radioButton_Lines",0).toBool();
    ui->radioButton_Lines->setChecked(ui->Screen->lines);
    ui->ShiftX->setValue(set.value("ShiftX",0).toFloat()*100);
    ui->ValueShiftX->setText(QString::number(ui->ShiftX->value()));
    ui->ShiftY->setValue(set.value("ShiftY",0).toFloat()*100);
    ui->ValueShiftY->setText(QString::number(ui->ShiftY->value()));
    ui->ShiftZ->setValue(set.value("ShiftZ",0).toFloat()*100);
    ui->ValueShiftZ->setText(QString::number(ui->ShiftZ->value()));
    ui->RotationX->setValue(set.value("RotX",0).toInt());
    ui->ValueRotationX->setText(set.value("RotX",0).toString());
    ui->RotationY->setValue(set.value("RotY",0).toInt());
    ui->ValueRotationY->setText(set.value("RotY",0).toString());
    ui->RotationZ->setValue(set.value("RotZ",0).toInt());
    ui->ValueRotationZ->setText(set.value("RotZ",0).toString());
    ui->MashScale->setValue((set.value("Mash_scale",0).toFloat()-1)*ui->MashScale->maximum());
    ui->ValueMashScale->setText(QString::number(ui->MashScale->value()));


    ui->Screen->ortho= set.value("Ortho",0).toBool();
    if(ui->Screen->ortho){
        ui->Ortho->setChecked(true);
    } else {
        ui->Perspective->setChecked(true);
    }
    ui->Screen->solid=set.value("Solid",  0).toBool();
    if(ui->Screen->solid){
        ui->LineSolid->setChecked(true);
    } else {
        ui->LineStipple->setChecked(true);
    }

    ui->Screen->square = set.value("ShapeSquare",  0).toBool();
    if(ui->Screen->square){
        ui->ShapeSquare->setChecked(true);
    } else {
        ui->ShapeRound->setChecked(true);
    }
}


void MainWindow::on_Save_clicked()
{
    SaveSettings();
}

void MainWindow::on_Reset_clicked()
{
    ui->BackRedSlider->setValue(40);
    ui->BackGreenSlider->setValue(75);
    ui->BackBlueSlider->setValue(90);
    ui->radioButton_Points->setChecked(true);
    ui->radioButton_Lines->setChecked(true);
    ui->VertexRedSlider->setValue(100);
    ui->VertexGreenSlider->setValue(10);
    ui->VertexBlueSlider->setValue(80);
    ui->ShapeSquare->setChecked(true);
    ui->Scale->setValue(10);
    ui->EdgeRedSlider->setValue(100);
    ui->EdgeGreenSlider->setValue(100);
    ui->EdgeBlueSlider->setValue(10);
    ui->LineSolid->setChecked(true);
    ui->ScaleEdge->setValue(2);
    ui->Ortho->setChecked(true);
    ui->ShiftX->setValue(0);
    ui->ValueShiftX->setText("0");
    ui->ShiftY->setValue(0);
    ui->ValueShiftY->setText("0");
    ui->ShiftZ->setValue(0);
    ui->ValueShiftZ->setText("0");
    ui->RotationX->setValue(0);
    ui->ValueRotationX->setText("0");
    ui->RotationY->setValue(0);
    ui->ValueRotationY->setText("0");
    ui->RotationZ->setValue(0);
    ui->ValueRotationZ->setText("0");
    ui->MashScale->setValue(0);
    ui->ValueMashScale->setText("0");
    ui->Screen->ortho=true;
    ui->Screen->update();
}


void MainWindow::on_BackRedSlider_valueChanged(int value)
{
    ui->BackRedValue->setText(QString::number(value));
    ui->Screen->red_background_color=(float)value/100;
}

void MainWindow::on_BackGreenSlider_valueChanged(int value)
{
    ui->BackGreenValue->setText(QString::number(value));
    ui->Screen->green_background_color=(float)value/100;
}

void MainWindow::on_BackBlueSlider_valueChanged(int value)
{
    ui->BackBlueValue->setText(QString::number(value));
    ui->Screen->blue_background_color=(float)value/100;
}

void MainWindow::on_VertexRedSlider_valueChanged(int value)
{
    ui->VertexRedValue->setText(QString::number(value));
    ui->Screen->red_vertex_color=(float)value/100;
}

void MainWindow::on_VertexGreenSlider_valueChanged(int value)
{
    ui->VertexGreenValue->setText(QString::number(value));
    ui->Screen->green_vertex_color=(float)value/100;
}

void MainWindow::on_VertexBlueSlider_valueChanged(int value)
{
    ui->VertexBlueValue->setText(QString::number(value));
    ui->Screen->blue_vertex_color=(float)value/100;
}

void MainWindow::on_EdgeRedSlider_valueChanged(int value)
{
    ui->EdgeRedValue->setText(QString::number(value));
    ui->Screen->red_edge_color=(float)value/100;
}

void MainWindow::on_EdgeGreenSlider_valueChanged(int value)
{
    ui->EdgeGreenValue->setText(QString::number(value));
    ui->Screen->green_edge_color=(float)value/100;
}

void MainWindow::on_EdgeBlueSlider_valueChanged(int value)
{
    ui->EdgeBlueValue->setText(QString::number(value));
    ui->Screen->blue_edge_color=(float)value/100;
}

void MainWindow::on_ScaleEdge_valueChanged(int value)
{
    ui->ScaleEdgeValue->setText(QString::number(value));
    ui->Screen->edge_scale=(float)value;
}


void MainWindow::on_Scale_valueChanged(int value)
{
    ui->ScaleValue->setText(QString::number(value));
    ui->Screen->paint_scale=(float)value;
}

void MainWindow::on_Open_clicked()
{
    if(ui->Screen->new_array) {
        ui->Screen->ClearScreen();
    }

    QString name= QFileDialog::getOpenFileName(0, tr("Open model"), QDir::homePath(), tr("OBJ (*.obj)"), 0, QFileDialog::DontUseNativeDialog);

    if(!name.isEmpty())
    {
            QByteArray array = name.toLocal8Bit();
            const char *str = array.data();
            int result = parse(str, &ui->Screen->obj);
            if (!result){
                size_t index = name.lastIndexOf("/");
                QString title = name.mid(index+1, name.length()-1);
                ui->Title->setText(title);
                ui->info_v->setText("Vertices: " + QString::number(ui->Screen->obj.count_vertex-1));
                ui->info_e->setText("Edges: " + QString::number(ui->Screen->obj.count_faces));
                ui->Screen->Start();

            } else {
                QMessageBox message;
                message.setText("Error. File can`t be open");
                message.exec();
            }
    } else {
        QMessageBox message;
        message.setText("Load any model");
        message.exec();
    }
}

void MainWindow::on_ShapeSquare_clicked()
{
    ui->Screen->square=true;
}

void MainWindow::on_ShapeRound_clicked()
{
    ui->Screen->square=false;
}

void MainWindow::on_LineSolid_clicked()
{
    ui->Screen->solid=true;
}

void MainWindow::on_LineStipple_clicked()
{
    ui->Screen->solid=false;
}

void MainWindow::on_Ortho_clicked()
{
    ui->Screen->ortho=true;
}

void MainWindow::on_Perspective_clicked()
{
    ui->Screen->ortho=false;
}

void MainWindow::on_radioButton_Points_clicked(bool checked)
{
    ui->Screen->point = checked;
}

void MainWindow::on_radioButton_Lines_clicked(bool checked)
{
    ui->Screen->lines = checked;
}


void MainWindow::on_JPG_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save ..."), QDir::homePath(), tr("JPG (*jpeg *jpg)"), 0, QFileDialog::DontUseNativeDialog);
    if(!fileName.isEmpty()){
        ui->Screen->ScreenshotJPG(fileName);
    }
}

void MainWindow::on_BMP_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(0, tr("Save ..."), QDir::homePath(), tr("BMP (*.bmp)"), 0, QFileDialog::DontUseNativeDialog);
    if(!fileName.isEmpty()){
        ui->Screen->ScreenshotBMP(fileName);
    }
}

void MainWindow::on_GIF_clicked()
{
    make_gif = new QTimer();
    gif = new QGifImage();
    connect(make_gif,SIGNAL(timeout()),this,SLOT(create_gif()));
    make_gif->start(100);
}


void MainWindow::create_gif()
{
    if(iter<50){
       QImage screenshot = ui->Screen->grabFramebuffer().scaled(640,480);
       gif->addFrame(screenshot, 100);
       iter++;
     } else {
       make_gif->stop();
       disconnect(make_gif);
       QString fileName = QFileDialog::getSaveFileName(0, tr("Save..."), QDir::homePath(), tr("GIF (*.gif)"), 0 , QFileDialog::DontUseNativeDialog );
       gif->save(fileName + ".gif");
       iter = 0;
    }
}

void MainWindow::on_ShiftX_valueChanged(int value)
{
    ui->ValueShiftX->setText(QString::number(value));
    ui->Screen->shiftx = (float)value/100;
}

void MainWindow::on_ShiftY_valueChanged(int value)
{
    ui->ValueShiftY->setText(QString::number(value));
    ui->Screen->shifty = (float)value/100;
}

void MainWindow::on_ShiftZ_valueChanged(int value)
{
    ui->ValueShiftZ->setText(QString::number(value));
    ui->Screen->shiftz = (float)value/100;
}

void MainWindow::on_RotationX_valueChanged(int value)
{
    ui->ValueRotationX->setText(QString::number(value));
    ui->Screen->rotx = (float)value*(M_PI/180);
}

void MainWindow::on_RotationY_valueChanged(int value)
{
    ui->ValueRotationY->setText(QString::number(value));
    ui->Screen->roty = (float)value*M_PI/180;
}

void MainWindow::on_RotationZ_valueChanged(int value)
{
    ui->ValueRotationZ->setText(QString::number(value));
    ui->Screen->rotz = (float)value*M_PI/180;
}

void MainWindow::on_MashScale_valueChanged(int value)
{
    ui->ValueMashScale->setText(QString::number(value));
    ui->Screen->mash_scale = (value<0 ? 1.01 - 1/(float)ui->MashScale->minimum()*value : (!value ? 1 : 1 + 1/(float)ui->MashScale->maximum()*value));
}


void MainWindow::on_ValueShiftX_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueShiftX->text(), ui->ShiftX->minimum(), ui->ShiftX->maximum());
    ui->ValueShiftX->setText(text);
    ui->ShiftX->setValue(text.toInt());

}

void MainWindow::on_ValueShiftY_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueShiftY->text(), ui->ShiftY->minimum(), ui->ShiftY->maximum());
    ui->ValueShiftY->setText(text);
    ui->ShiftY->setValue(text.toInt());
}

void MainWindow::on_ValueShiftZ_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueShiftZ->text(), ui->ShiftZ->minimum(), ui->ShiftZ->maximum());
    ui->ValueShiftZ->setText(text);
    ui->ShiftZ->setValue(text.toInt());
}

void MainWindow::on_BackRedValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->BackRedValue->text(), ui->BackRedSlider->minimum(), ui->BackRedSlider->maximum());
    ui->BackRedValue->setText(text);
    ui->BackRedSlider->setValue(text.toInt());
}

void MainWindow::on_BackGreenValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->BackGreenValue->text(), ui->BackGreenSlider->minimum(), ui->BackGreenSlider->maximum());
    ui->BackGreenValue->setText(text);
    ui->BackGreenSlider->setValue(text.toInt());
}

void MainWindow::on_BackBlueValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->BackBlueValue->text(), ui->BackBlueSlider->minimum(), ui->BackBlueSlider->maximum());
    ui->BackBlueValue->setText(text);
    ui->BackBlueSlider->setValue(text.toInt());
}

void MainWindow::on_VertexRedValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->VertexRedValue->text(), ui->VertexRedSlider->minimum(), ui->VertexRedSlider->maximum());
    ui->VertexRedValue->setText(text);
    ui->VertexRedSlider->setValue(text.toInt());
}

void MainWindow::on_VertexGreenValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->VertexGreenValue->text(), ui->VertexGreenSlider->minimum(), ui->VertexGreenSlider->maximum());
    ui->VertexGreenValue->setText(text);
    ui->VertexGreenSlider->setValue(text.toInt());
}

void MainWindow::on_VertexBlueValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->VertexBlueValue->text(), ui->VertexBlueSlider->minimum(), ui->VertexBlueSlider->maximum());
    ui->VertexBlueValue->setText(text);
    ui->VertexBlueSlider->setValue(text.toInt());
}

void MainWindow::on_ScaleValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->ScaleValue->text(), ui->Scale->minimum(), ui->Scale->maximum());
    ui->ScaleValue->setText(text);
    ui->Scale->setValue(text.toInt());
}

void MainWindow::on_EdgeRedValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->EdgeRedValue->text(), ui->EdgeRedSlider->minimum(), ui->EdgeRedSlider->maximum());
    ui->EdgeRedValue->setText(text);
    ui->EdgeRedSlider->setValue(text.toInt());
}

void MainWindow::on_EdgeGreenValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->EdgeGreenValue->text(), ui->EdgeGreenSlider->minimum(), ui->EdgeGreenSlider->maximum());
    ui->EdgeGreenValue->setText(text);
    ui->EdgeGreenSlider->setValue(text.toInt());
}

void MainWindow::on_EdgeBlueValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->EdgeBlueValue->text(), ui->EdgeBlueSlider->minimum(), ui->EdgeBlueSlider->maximum());
    ui->EdgeBlueValue->setText(text);
    ui->EdgeBlueSlider->setValue(text.toInt());
}

void MainWindow::on_ScaleEdgeValue_editingFinished()
{
    QString text = CheckCorrectInput(ui->ScaleEdgeValue->text(), ui->ScaleEdge->minimum(), ui->ScaleEdge->maximum());
    ui->ScaleEdgeValue->setText(text);
    ui->ScaleEdge->setValue(text.toInt());
}

void MainWindow::on_ValueRotationX_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueRotationX->text(), ui->RotationX->minimum(), ui->RotationX->maximum());
    ui->ValueRotationX->setText(text);
    ui->RotationX->setValue(text.toInt());
}

void MainWindow::on_ValueRotationY_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueRotationY->text(), ui->RotationY->minimum(), ui->RotationY->maximum());
    ui->ValueRotationY->setText(text);
    ui->RotationY->setValue(text.toInt());
}

void MainWindow::on_ValueRotationZ_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueRotationZ->text(), ui->RotationZ->minimum(), ui->RotationZ->maximum());
    ui->ValueRotationZ->setText(text);
    ui->RotationZ->setValue(text.toInt());
}

void MainWindow::on_ValueMashScale_editingFinished()
{
    QString text = CheckCorrectInput(ui->ValueMashScale->text(), ui->MashScale->minimum(), ui->MashScale->maximum());
    ui->ValueMashScale->setText(text);
    ui->MashScale->setValue(text.toInt());
}

QString MainWindow::CheckCorrectInput(QString text, int min, int max){
    QString result="";
    if(text.toFloat()){
        int value = text.toFloat();
        if(value<min){
            result=QString::number(min);
        } else if(value >max) {
            result =QString::number(max);
        } else {
            result = QString::number(value);
        }
    } else {
        result ="0";
    }
    return result;
}


