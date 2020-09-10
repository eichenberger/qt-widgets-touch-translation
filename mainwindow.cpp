#include <QtWidgets>

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>

#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setAttribute(Qt::WA_AcceptTouchEvents);
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::TouchBegin:
    case QEvent::TouchUpdate:
    case QEvent::TouchEnd:
    {
        const QTouchEvent *touch = static_cast<QTouchEvent *>(event);
        const QList<QTouchEvent::TouchPoint> touchPoints = touch->touchPoints();
        for (const QTouchEvent::TouchPoint &touchPoint : touchPoints) {
            qDebug() << "Touch event: " << touchPoint.state();
            if (touchPoint.state() == Qt::TouchPointPressed) {
                qDebug() << "Send fake event: " << touchPoint.pos();
                QMouseEvent fake(QEvent::MouseButtonPress, touchPoint.pos(), touchPoint.screenPos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QApplication::sendEvent(this, (QEvent*)&fake);
            }
        }
        break;
    }
    default:
        return QWidget::event(event);
    }
    return true;
}
