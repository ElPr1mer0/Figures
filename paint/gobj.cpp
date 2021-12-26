#include "gobj.h"

//////////////////////////GOBJ//////////////////////
//////////////////////////GOBJ//////////////////////
//////////////////////////GOBJ//////////////////////

GOBJ::~GOBJ(){}

void GOBJ::paintEvent1(QPaintEvent *, MainWindow *){}

void GOBJ::setCentr(){}

void GOBJ::changePosition(int, int){}

void GOBJ::setColor(int, int, int){}

void GOBJ::setConnectionColor(int red, int green, int blue){
    this->cRed = red;
    this->cGreen = green;
    this->cBlue = blue;
}

void GOBJ::connection(QPaintEvent *,MainWindow *ev, GOBJ* obj1, GOBJ* obj2){
    if(obj1->CentrX != -1000 && obj1->CentrY != -1000
    && obj2->CentrX != -1000 && obj2->CentrX != -1000){
        QPainter painter;
        painter.begin(ev);
        QColor c(this->cRed,this->cGreen,this->cBlue);
        painter.setPen(c);
        painter.setBrush(QBrush(c));
        painter.drawLine(obj1->CentrX,obj1->CentrY,obj2->CentrX,obj2->CentrY);
        painter.end();
    }
}

//////////////////////////CIRCLE//////////////////////
//////////////////////////CIRCLE//////////////////////
//////////////////////////CIRCLE//////////////////////

CIRCLE::~CIRCLE(){}

void CIRCLE::paintEvent1(QPaintEvent *, MainWindow *ev){
    QPainter painter;
    painter.begin(ev);
    QColor c(this->red,this->green,this->blue);
    painter.setBrush(QBrush(c));
    painter.drawEllipse(x1,y1,w,h);
    QColor c2(this->cRed,this->cGreen,this->cBlue);
    painter.setBrush(QBrush(c2));
    painter.drawEllipse(CentrX,CentrY,5,5);
    painter.end();
}

void CIRCLE::setCentr(){
    this->CentrX = this->x1+this->w/2-1;
    this->CentrY = this->y1+this->h/2-1;
}

void CIRCLE::changePosition(int newCentrX, int newCentrY){
    int distanceX, distanceY;
    distanceX = newCentrX-this->CentrX;
    distanceY = newCentrY-this->CentrY;
    this->CentrX = newCentrX;
    this->CentrY = newCentrY;
    this->x1 += distanceX;
    this->y1 += distanceY;
}

void CIRCLE::setColor(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

//////////////////////////LINE//////////////////////
//////////////////////////LINE//////////////////////
//////////////////////////LINE//////////////////////

LINE::~LINE(){}

void LINE::paintEvent1(QPaintEvent *, MainWindow *ev){
    if(x2 == -1000 || y2 == -1000) return;
    QPainter painter;
    painter.begin(ev);
    painter.drawLine(x1,y1,x2,y2);
    painter.end();
}

void LINE::setCentr(){};

//////////////////////////RECTANGLE//////////////////////
//////////////////////////RECTANGLE//////////////////////
//////////////////////////RECTANGLE//////////////////////

RECTANGLE::~RECTANGLE(){}

void RECTANGLE::paintEvent1(QPaintEvent *, MainWindow *ev){
    QPainter painter;
    painter.begin(ev);
    QColor c(this->red,this->green,this->blue);
    painter.setBrush(QBrush(c));
    painter.drawRect(x1,y1,w,h);
    QColor c2(this->cRed,this->cGreen,this->cBlue);
    painter.setBrush(QBrush(c2));
    painter.drawEllipse(CentrX,CentrY,5,5);
    painter.end();
}

void RECTANGLE::setCentr(){
    this->CentrX = this->x1+this->w/2-1;
    this->CentrY = this->y1+this->h/2-1;
}

void RECTANGLE::changePosition(int newCentrX, int newCentrY){
    int distanceX, distanceY;
    distanceX = newCentrX-this->CentrX;
    distanceY = newCentrY-this->CentrY;
    this->CentrX = newCentrX;
    this->CentrY = newCentrY;
    this->x1 += distanceX;
    this->y1 += distanceY;
}

void RECTANGLE::setColor(int red, int green, int blue){
    this->red = red;
    this->green = green;
    this->blue = blue;
}

//////////////////////////TRIANGLE//////////////////////
//////////////////////////TRIANGLE//////////////////////
//////////////////////////TRIANGLE//////////////////////

TRIANGLE::~TRIANGLE(){}

void TRIANGLE::paintEvent1(QPaintEvent *, MainWindow *ev){
    if (x2 == -1000 || y2 == -1000) return;
    QPainter painter;
    painter.begin(ev);
    painter.drawLine(x1,y1,x2,y2);
    if (x3 == -1000 || y3 == -1000) return;
    painter.drawLine(x2,y2,x3,y3);
    painter.drawLine(x3,y3,x1,y1);
    QColor c2(this->cRed,this->cGreen,this->cBlue);
    painter.setBrush(QBrush(c2));
    painter.drawEllipse(CentrX,CentrY,5,5);
    painter.end();
}

void TRIANGLE::setCentr(){
    if(this->x1 == -1000||this->x2 == -1000 ||this->x3 == -1000
    ||this->y1 == -1000 ||this->y2 == -1000 ||this->y3 == -1000) return;
    this->CentrX = (this->x1+this->x2+this->x3)/3;
    this->CentrY = (this->y1+this->y2+this->y3)/3;
}

void TRIANGLE::changePosition(int newCentrX, int newCentrY){
    int distanceX, distanceY;
    distanceX = newCentrX-this->CentrX;
    distanceY = newCentrY-this->CentrY;
    this->CentrX = newCentrX;
    this->CentrY = newCentrY;
    this->x1 += distanceX;
    this->y1 += distanceY;
    this->x2 += distanceX;
    this->y2 += distanceY;
    this->x3 += distanceX;
    this->y3 += distanceY;
}
