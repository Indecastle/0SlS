#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>

#include <QtDebug>

static int i = 0, j=0, kek=0;
static bool isDraw = false;

void funcKEK(){
    //kek = (kek+10) % 260;
    //qDebug() << kek;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->setInterval(20);
    qDebug() << "hello world";

    //std::thread th(funcKEK);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout(){
    i = (i + 1) % 360;
    j = (j + 1) % 359;
    qDebug() << i << " " << j;
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

void MainWindow::paintEvent(QPaintEvent *event) {
    if(isDraw)
    {
        QPainter *paint = new QPainter(this);

        // Round One!!!

        paint->setPen(QPen(Qt::blue, 2));
        paint->setRenderHint(QPainter::Antialiasing, true);

        paint->setBrush(QBrush(QColor::fromHsv(j,255, 255), Qt::SolidPattern));
        paint->drawRect(50, 50, 50, 50);

        paint->setBrush(QBrush(Qt::red, Qt::Dense1Pattern));
        paint->drawRect(110, 50, 50, 50);

        paint->setBrush(QBrush(Qt::red, Qt::Dense7Pattern));
        paint->drawRect(170, 50, 50, 50);

        paint->setBrush(QBrush(Qt::blue, Qt::NoBrush));
        paint->drawRect(230, 50, 50, 50);

        // Round Two!!!
        paint->setPen(QPen(Qt::darkGreen, 3, Qt::DashDotDotLine, Qt::RoundCap));

        paint->setBrush(QBrush(Qt::blue, Qt::SolidPattern));
        paint->drawEllipse(50, 110, 50, 50);

        paint->setBrush(QBrush(Qt::yellow, Qt::SolidPattern));
        paint->drawEllipse(110, 110, 40, 55);

        paint->setBrush(QBrush(Qt::darkCyan, Qt::SolidPattern));
        paint->drawEllipse(170, 110, 60, 50);

        paint->setBrush(QBrush(Qt::darkGray, Qt::FDiagPattern));
        paint->drawEllipse(240, 110, 30, 30);

        // Round Three!!!
        paint->setPen(QPen(Qt::red, 2, Qt::DashDotLine, Qt::FlatCap, Qt::MiterJoin));

        QPointF points[5] = {
              QPointF(60, 170),
              QPointF(90, 170),
              QPointF(100, 220),
              QPointF(50, 220),
            QPointF(60, 170)
        };

        paint->setBrush(QBrush(Qt::blue, Qt::HorPattern));
        paint->drawPolyline(points, 5);

        movePoints(points, 4, QPointF(60, 0));
        paint->setBrush(QBrush(Qt::red, Qt::VerPattern));
        paint->drawPolygon(points, 4);

        movePoints(points, 4, QPointF(60, 0));
        paint->setBrush(QBrush(Qt::red, Qt::CrossPattern));
        paint->drawPolygon(points, 4);

        movePoints(points, 4, QPointF(60, 0));
        paint->setBrush(QBrush(Qt::blue, Qt::BDiagPattern));
        paint->drawPolygon(points, 4);

        // Round Four!!!
        paint->setPen(QPen(Qt::darkMagenta, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

        paint->drawLine(50, 250, width() - 10, 250-40);
        paint->drawLine(50, 260, width(), 260);
        paint->drawLine(50, 270, width() - 10, 270+40);


        // Round Five!!!
        paint->setPen(QPen(Qt::darkCyan, 2, Qt::SolidLine));

        paint->drawArc(QRect(50, 300, 50, 50), 64*i, 120*16);
        paint->drawArc(QRect(110, 300, 50, 50), 128*i, 120*16);
        paint->setPen(QPen(Qt::darkMagenta, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        paint->drawArc(QRect(170, 300, 50, 50), 64*i, 120*30);
        paint->drawArc(QRect(230, 300, 100, 50), 64*i, 120*16);

        paint->end();
    }
}

void MainWindow::on_pushButton_clicked()
{
    isDraw = !isDraw;
    if(isDraw)
        timer->start();
    else
        timer->stop();
    repaint();
}
