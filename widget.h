#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtWidgets>
#include <QCoreApplication>

class Widget : public QWidget
{
    Q_OBJECT
protected:
    QPushButton *SlyButton;
    QWidget *message; // Если все-таки получилось
    int xCursor; // Храним положение курсора
    int yCursor; //
    int leftBorder;  // границы окошка
    int rightBorder; //
    int topBorder;   //
    int bottomBorder;//
    void getBorders(); // вычислить границы в системе координат монитора

public:
    Widget(QWidget *parent = 0);
    ~Widget();
    void timerEvent(QTimerEvent *te);
    bool isCursorClose(); // курсор приблизился?
    QPoint getMove(int sens); // перемещение в противоположную сторону от курсора
    bool isOnDisplayBorder();  // для отслеживания столкновений с границами экрана
    void keyPressEvent(QKeyEvent *ke); // для экстренного закрытия
public slots:
    void slotRun(); // для перенесения в случайное место
    void slotShowMessage(); //
};

class MesageBox: public QWidget
{
    Q_OBJECT
protected:
    QPushButton *bClose;
    QLabel *lText;
    int sec; // счетчик секунд жизни
public:
    MesageBox(QWidget *parent=0);
    ~MesageBox();
    void timerEvent(QTimerEvent *te);
};

int getRandom(int i, int j, int seed); // получение псевдо-случайного числа в заданном диапазоне
#endif // WIDGET_H
