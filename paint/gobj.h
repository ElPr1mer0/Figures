#ifndef GOBJ_H
#define GOBJ_H
#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QPixmap>
#include "mainwindow.h"
#include <math.h>

class GOBJ{
public:
    virtual ~GOBJ();
    virtual void paintEvent1(QPaintEvent*, MainWindow*);
    virtual void setCentr();
    virtual void changePosition(int, int);
    virtual void setColor(int, int, int);

    void setConnectionColor(int, int, int);
    void connection(QPaintEvent *,MainWindow *, GOBJ*, GOBJ*);

    int x1, y1, x2 = -1000, y2 = -1000, x3 = -1000, y3 = -1000, w, h;
    int CentrX = -1000, CentrY = -1000;
    int red = 0, green = 0, blue = 0;
    int cRed = 255, cGreen = 0, cBlue = 0;
};



class CIRCLE:public GOBJ{
public:
    ~CIRCLE();
    void paintEvent1(QPaintEvent*, MainWindow*) override;
    void setCentr() override;
    void changePosition(int, int) override;
    void setColor(int, int, int) override;
};



class LINE: public GOBJ{
public:
    ~LINE();
    void paintEvent1(QPaintEvent*, MainWindow*) override;
    void setCentr() override;
};



class RECTANGLE: public GOBJ{
public:
    ~RECTANGLE();
    void paintEvent1(QPaintEvent*, MainWindow*) override;
    void setCentr() override;
    void changePosition(int, int) override;
    void setColor(int, int, int) override;
};



class TRIANGLE: public GOBJ{
public:
    ~TRIANGLE();
    void paintEvent1(QPaintEvent*, MainWindow*) override;
    void setCentr() override;
    void changePosition(int, int) override;
};

#endif // GOBJ_H
