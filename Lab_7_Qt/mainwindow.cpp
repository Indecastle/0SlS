#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtDebug>
#include <QListWidget>

static int i = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeout()));
    timer->start(20);
    qDebug() << "hello world";
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter *paint = new QPainter(this);

    paint->setPen(Qt::red);
    paint->setBrush(QBrush(Qt::blue, Qt::SolidPattern));

    QTransform transform;
    transform.translate(200, 300);
    transform.rotate(i);
    transform.scale(0.5, 1.0);
    paint->setTransform(transform);

    paint->drawText(20, 300, "Hello World");

    paint->drawRect(200, 300, 100, 100);
    paint->rotate(0);
    paint->end();
}

void MainWindow::onTimeout(){
    i = (i + 1) % 360;
    //qDebug() << i;
    repaint();
}

void MainWindow::on_pushButton_2_clicked()
{
    QListWidget *lw1 = ui->listWidget;
    QString et = ui->lineEdit->text();
    bool ok = true;
    for(int i = 0; i < lw1->count(); ++i)
    {
        QListWidgetItem* item = lw1->item(i);
        if (item->text() == et) {
            ok = false;
            break;
        }
    }
    if(ok)
        lw1->addItem(et);
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->listWidget->clear();
    ui->listWidget_2->clear();
}

void MainWindow::on_pushButton_4_clicked()
{
    if(ui->listWidget->currentItem() != nullptr) {
        ui->listWidget_2->addItem( ui->listWidget->currentItem()->text() );
        ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
        delete ui->listWidget->currentItem();
    }
}

void MainWindow::on_pushButton_5_clicked()
{
    if(ui->listWidget->currentItem() != nullptr) {
        ui->listWidget->removeItemWidget(ui->listWidget->currentItem());
        delete ui->listWidget->currentItem();
    }
    if(ui->listWidget_2->currentItem() != nullptr) {
        ui->listWidget_2->removeItemWidget(ui->listWidget_2->currentItem());
        delete ui->listWidget_2->currentItem();
    }
}
