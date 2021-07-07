#include "widget.h"
#include "ui_widget.h"

#include <QPainter>
#include <QTime>
#include <QTimer>
#include <QCloseEvent>

namespace C {

const int DefaultWidth = 200;
const int DefaultHeight = 200;

const int HourBold = 4;
const int MinuteBold = 2;

}

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&Widget::update));

    timer->start(1000);
    setWindowTitle(tr("Analog Clock"));
    resize(C::DefaultWidth, C::DefaultHeight);
    width();
    height();
    showFullScreen();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
        QWidget::close();
}

void Widget::paintEvent(QPaintEvent *)
{
    QTime time = QTime::currentTime();

    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    painter.scale(side / 200.0, side / 200.0);

    drawHours(painter, time);
    drawMinutes(painter, time);
    drawSeconds(painter, time);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::drawHours(QPainter& painter, const QTime& time)
{
    QColor hourColor(93, 182, 127);
    QPen hourPen(hourColor, C::HourBold);
    painter.setPen(hourPen);
    painter.save();
    auto angle = 30.0 * ((time.hour() + time.minute() / 60.0));
    painter.rotate(angle);
    painter.drawLine(0, 0, 0, -50);

    painter.restore();

    painter.setPen(hourColor);
    painter.save();
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }

    painter.restore();

}

void Widget::drawMinutes(QPainter& painter, const QTime& time)
{
    QColor minuteColor(240, 96, 91);
    QPen minutePen(minuteColor, C::MinuteBold);
    painter.setPen(minutePen);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawLine(0, 0, 0, -70);
    painter.restore();
}

void Widget::drawSeconds(QPainter& painter, const QTime& time)
{
    QColor secondColor(0, 0, 0, 127);
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.save();

    int sec = time.second();
    for (int i = 0; i <= sec; i++) {
        painter.drawEllipse(-1,-100, 2, 2);
        painter.rotate(6.0);
    }
    painter.restore();
}
