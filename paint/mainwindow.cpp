#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gobj.h"
#include <QPixmap>
#include <vector>
#include "QString"
QVector <GOBJ*> figures;
int N;
int R = 20;
int cRed, cGreen, cBlue;
int red, green, blue;
bool figurCreated = false;
bool LineFirstTime = true;
bool TriangleFirstTime = true;
bool TriangleSecondTime = true;
bool HandFirstTime = true;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    int h = 25, w = 25;
    QPixmap pixHand(":/figures/images/hand.png");
    ui->labelHand->setPixmap(pixHand.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pixLine(":/figures/images/line.png");
    ui->labelLine->setPixmap(pixLine.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pixCircle(":/figures/images/circle.png");
    ui->labelCircle->setPixmap(pixCircle.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pixRectangle(":/figures/images/rectangle.png");
    ui->labelRectangle->setPixmap(pixRectangle.scaled(w,h,Qt::KeepAspectRatio));

    QPixmap pixTriangle(":/figures/images/triangle.png");
    ui->labelTriangle->setPixmap(pixTriangle.scaled(w,h,Qt::KeepAspectRatio));
}


MainWindow::~MainWindow(){delete ui;}

void MainWindow::paintEvent(QPaintEvent *event){ 
    if(figurCreated){ // чтобы если фигуры нет, не было вылета
        for (int i = 0;i<figures.size();++i ) {
            figures[i]->setCentr();
            figures[i]->setConnectionColor(cRed,cGreen,cBlue);
            figures[i]->paintEvent1(event, this);
        }

//        for (int i = 0;i<figures.size();++i ) { //последовательно
//            if(i+1<figures.size())
//                figures[i]->connection(event, this,figures[i],figures[i+1]);
//        }



        for (int i = 0;i<figures.size();++i )
            for (int j = i+1;j<figures.size();++j ){ //все подряд
                if(i==figures.size()) break; // чтобы не было выхода за границы
                figures[i]->connection(event, this,figures[i],figures[j]);            
            }
    }
}



void MainWindow::mousePressEvent(QMouseEvent *event){

    if(ui->comboBoxConnectionColor->currentText() == "Red"){//задаём цвет соединения
        cRed = 255; cGreen = 0; cBlue = 0;
    }
    else if(ui->comboBoxConnectionColor->currentText() == "Yellow"){
        cRed = 230; cGreen = 255; cBlue = 0;
    }

    else if(ui->comboBoxConnectionColor->currentText() == "Green"){
        cRed = 0; cGreen = 255; cBlue = 0;
    }
    else if(ui->comboBoxConnectionColor->currentText() == "Blue"){
        cRed = 0; cGreen = 51; cBlue = 255;
    }

    if(ui->comboBoxFigureColor->currentText() == "Red"){//задаём цвет фигуры
        red = 255; green = 0; blue = 0;
    }
    else if(ui->comboBoxFigureColor->currentText() == "Yellow"){
        red = 230; green = 255; blue = 0;
    }

    else if(ui->comboBoxFigureColor->currentText() == "Green"){
        red = 0; green = 255; blue = 0;
    }
    else if(ui->comboBoxFigureColor->currentText() == "Blue"){
        red = 0; green = 51; blue = 255;
    }

    if(ui->radioButtonCircle->isChecked()){
        bool ok;
        GOBJ *circle = new CIRCLE;
        circle->w = ui->lineEditWidth->text().toInt(&ok);
        circle->h = ui->lineEditHeight->text().toInt(&ok);
        circle->x1 = event->position().x()-circle->w/2;
        circle->y1 = event->position().y()-circle->h/2;
        circle->setColor(red,green,blue);
        figures.push_back(circle);
        figurCreated = true;
    }
    else if(ui->radioButtonTriangle->isChecked()){
        if(TriangleFirstTime){// для создания первой точки
            GOBJ *triangle = new TRIANGLE;
            triangle->x1 = event->position().x();
            triangle->y1 = event->position().y();
            figures.push_back(triangle);
            figurCreated = true;
            TriangleFirstTime = false;
        }
        else if(TriangleSecondTime && !TriangleFirstTime){ // для создания второй точки
            figures.back()->x2 = event->position().x();
            figures.back()->y2 = event->position().y();
            TriangleSecondTime = false;
        }
        else if(!TriangleSecondTime && !TriangleFirstTime){// для создания третьей точки
            figures.back()->x3 = event->position().x();
            figures.back()->y3 = event->position().y();
            TriangleFirstTime = true;
            TriangleSecondTime = true;
        }
    }
    else if(ui->radioButtonRectangle->isChecked()){
        bool ok; // чтобы не вылетало, если не будет числа
        GOBJ *rectangle = new RECTANGLE;
        rectangle ->w = ui->lineEditWidth->text().toInt(&ok);
        rectangle ->h = ui->lineEditHeight->text().toInt(&ok);
        rectangle ->x1 = event->position().x()-rectangle->w/2; // чтобы по центру ставилась фигура, ровно на курсор
        rectangle ->y1 = event->position().y()-rectangle->h/2;
        rectangle->setColor(red,green,blue);
        figures.push_back(rectangle);
        figurCreated = true;
    }
    else if(ui->radioButtonHand->isChecked()){
        if(figurCreated){ // если фигура есть, то можно переносить
            if(HandFirstTime){// выбор фигуры
                for (int i = 0;i<figures.size();++i ) {
                    if(figures[i]->CentrX-R <= event->position().x() && figures[i]->CentrX+R >= event->position().x())
                        if(figures[i]->CentrY-R <= event->position().y() && figures[i]->CentrY+R >= event->position().y()){
                            N = i;
                            HandFirstTime = false;
                            break;
                        }
                }
            }
            else{ // ставим фигуру на новое место
               figures[N]->changePosition(event->position().x(),event->position().y());
               HandFirstTime = true;
            }
        }
    }
    else if(ui->radioButtonLine->isChecked()){
        if(LineFirstTime){
            GOBJ *line = new LINE; // для первой второй точки
            line->x1 = event->position().x();
            line->y1 = event->position().y();
            figures.push_back(line);
            LineFirstTime = false;
            figurCreated = true;
        }
        else{
            figures.back()->x2 = event->position().x();
            figures.back()->y2 = event->position().y();
            LineFirstTime = true; // для создания второй точки
        }
    }

   repaint();
}

