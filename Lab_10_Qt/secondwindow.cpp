#include "secondwindow.h"
#include "ui_secondwindow.h"
#include <QPainter>

static bool isDraw = true;

SecondWindow::SecondWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SecondWindow)
{
    ui->setupUi(this);
    this->color = Qt::white;
}

SecondWindow::~SecondWindow()
{
    delete ui;
}

void SecondWindow::GetMessage(int figure, QColor* color, bool _isDraw){
    this->figure = figure;
    this->color = *color;
    isDraw = _isDraw;
    repaint();
}

void movePoints(QPointF *points, int count, QPointF qpoint){
    //foreach (QPointF* point, points) {
    //    *point = *point + qpoint;
    //}
    for(int i=0; i < count; i++){
        points[i] = points[i] + qpoint;
    }
}

void SecondWindow::paintEvent(QPaintEvent *event) {
    if(isDraw)
    {
        QPainter *paint = new QPainter(this);

        // Round One!!!
        QPointF points[4] = {
              QPointF(65, 0),
              QPointF(130, 115),
              QPointF(65, 225),
              QPointF(0, 115)
        };
        QPointF points2[10] = {
                QPointF(90, 0),
                QPointF(114, 70),
                QPointF(182, 71),
                QPointF(129, 112),
                QPointF(148, 181),
                QPointF(90, 142),
                QPointF(35, 181),
                QPointF(55, 112),
                QPointF(0, 71),
                QPointF(71, 71)
        };
        movePoints(points, 4, QPointF(120, 100));
        movePoints(points2, 10, QPointF(100, 100));

        paint->setPen(QPen(Qt::black, 0));
        paint->setRenderHint(QPainter::Antialiasing, true);
        paint->setBrush(QBrush(this->color, Qt::SolidPattern));

        switch(this->figure){
            case 1: paint->drawPolygon(points, 4); break;
            case 2: paint->drawRect(150, 150, 100, 100); break;
            case 3: paint->drawPolygon(points2, 10); break;
        }

        //paint->setBrush(QBrush(QColor::fromHsv(j,255, 255), Qt::SolidPattern));

        paint->end();
    }
}
