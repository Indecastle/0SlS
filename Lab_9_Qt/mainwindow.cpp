#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <thread>

#include <QtDebug>

static int i = 0, j=0, kek=0;
static bool isDraw = true;
static QPoint python[20];

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
    timer->start();
    qDebug() << "hello world";

    //std::thread th(funcKEK);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onTimeout(){

    i = (i + 1) % 360;
    j = (j + 2) % 359;

    QPoint pos = QWidget::mapFromGlobal(QCursor::pos()) - QPoint(16,16);
    if(python[0] != pos)
        for (int i = 19; i >= 1; i--){
            python[i] = python[i-1];
        }
    python[0] = pos;

    qDebug() << i << " " << j << " " << pos;
    repaint();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    if(isDraw)
    {
        QPainter *paint = new QPainter(this);

        // Round One!!!

        paint->setPen(QPen(Qt::black, 0));
        paint->setRenderHint(QPainter::Antialiasing, true);

        paint->setBrush(QBrush(QColor::fromHsv(j,255, 255), Qt::SolidPattern));

        for ( int i =0; i < 20; i++){
            paint->drawRect(python[i].x(), python[i].y(), 32, 32);
        }
        paint->end();
    }
}
