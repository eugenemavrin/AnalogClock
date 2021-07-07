#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *) override;


private:
    void drawHours(QPainter& painter, const QTime& time);
    void drawMinutes(QPainter& painter, const QTime& time);
    void drawSeconds(QPainter& paiter, const QTime& time);

private:
    Ui::Widget *ui = nullptr;


};
#endif // WIDGET_H
