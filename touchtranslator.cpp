#include <QtWidgets>

#include <QColor>
#include <QImage>
#include <QPoint>
#include <QWidget>
#include <QMouseEvent>

#include "touchtranslator.h"

TouchTranslator::TouchTranslator()
{

}

bool TouchTranslator::eventFilter(QObject *obj, QEvent *event)
{
    qDebug() << "type: " << event->type();
    switch (event->type()) {
    case QEvent::TouchUpdate:
    {
        const QTouchEvent *touch = static_cast<QTouchEvent *>(event);
        const QList<QTouchEvent::TouchPoint> touchPoints = touch->touchPoints();
        for (const QTouchEvent::TouchPoint &touchPoint : touchPoints) {
            qDebug() << "Touch event: " << touchPoint.state();
            if (touchPoint.state() == Qt::TouchPointPressed) {
                qDebug() << "Send fake press event: " << touchPoint.startPos();
                QMouseEvent fake(QEvent::MouseButtonPress, touchPoint.pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QApplication::sendEvent(obj, (QEvent*)&fake);
                return true;
            }
        }
        break;
    }
    case QEvent::TouchEnd:
    {
        const QTouchEvent *touch = static_cast<QTouchEvent *>(event);
        const QList<QTouchEvent::TouchPoint> touchPoints = touch->touchPoints();
        for (const QTouchEvent::TouchPoint &touchPoint : touchPoints) {
            qDebug() << "Touch event: " << touchPoint.state();
            if (touchPoint.state() == Qt::TouchPointReleased) {
                qDebug() << "Send fake release event: " << touchPoint.startPos();
                QMouseEvent fake(QEvent::MouseButtonRelease, touchPoint.pos(), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier);
                QApplication::sendEvent(obj, (QEvent*)&fake);
                return true;
            }
        }
        break;
    }
    case QEvent::MouseButtonPress:
    case QEvent::MouseButtonRelease:
    {
        const QMouseEvent *mouse = static_cast<QMouseEvent *>(event);
        qDebug() << "Mouse event: " << event->type();
        qDebug() << "Mouse pose: " << mouse->pos();
        break;
    }
    default:
        return QObject::eventFilter(obj, event);
    }
    return QObject::eventFilter(obj, event);
}
