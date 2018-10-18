#include "widget.h"
#include <QApplication>
#include <QDateTime>
#include <math.h>

//-----------------------------------------------
// Widget
//-----------------------------------------------
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    SlyButton=new QPushButton("Поднять Зарплату", this);
    setFixedSize(150,30);
    SlyButton->setFixedSize(size());
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::SplashScreen);
//   QObject::connect(SlyButton, SIGNAL(clicked()), this, SLOT(slotRun()));
    QObject::connect(SlyButton, SIGNAL(clicked()), this, SLOT(slotShowMessage()));

//    setWindowIcon(QIcon("smile.png"));
    startTimer(10); // считываем положение курсора каждые ...
}
//-----------------------------------------------
Widget::~Widget()
{

}
//-----------------------------------------------
void Widget::slotRun()
{
    QRect display = QApplication::desktop()->screenGeometry();

    QPoint newPosition;

    int left=0, top=0;
    int right=display.right() - width(), bottom=display.bottom()-width();
    int seed=x()*y();


    newPosition.setX(getRandom(left, right, seed));
    newPosition.setY(getRandom(top, bottom, seed*3.14));

    QRect position(newPosition,size());
    setGeometry(position);
}
//-----------------------------------------------
int getRandom(int i, int j, int seed)
{

    int r=qrand();
    r%=j;
    if(r<i) r+=i;
    return r;

}
//-----------------------------------------------
void Widget::timerEvent(QTimerEvent *te)
{
    QPoint p=QCursor::pos();
    getBorders();

    xCursor=p.x();
    yCursor=p.y();
    if(isCursorClose())
    {
//        qDebug() << "cursor x: " << xCursor << " y: " << yCursor;
        move(getMove(5));
        if(isOnDisplayBorder()) slotRun();
    }
}
//-----------------------------------------------
bool Widget::isCursorClose()
{

    int howClose=25;
    if(
        (xCursor >= leftBorder-howClose && xCursor <= rightBorder+howClose)
            &&
        (yCursor >= topBorder-howClose && yCursor <= bottomBorder+howClose) ) return true;

    return false;
}
//-----------------------------------------------
void Widget::getBorders()
{
    QPoint p=pos();
    leftBorder=p.x();
    topBorder=p.y();
    rightBorder=p.x()+width();
    bottomBorder=p.y()+height();
//    qDebug() << "left: " << leftBorder << " right: " << rightBorder << "top: " << topBorder << " bottom: " << bottomBorder;
}
//-----------------------------------------------
QPoint Widget::getMove(int sens) // sens - просто величина перемещения
{

    QPoint result=pos(); // получаем глобальную координату
    int xCenter=leftBorder+width()/2; // получаем центральную точку,
    int yCenter=topBorder+height()/2; // относительно которой будем считать

    double angle=atan2(yCursor-yCenter, xCursor-xCenter);

//    qDebug() << "angle: " << angle;

    int x=result.x(), y=-result.y();

    x=x-sens*cos(angle); // x с минусом потому что y-ось перевернута
    y=y+sens*sin(angle);
//    qDebug() << "x: " << x << " y: " << y;
    result.setX(x);
    result.setY(-y);

    return result;
}
//-----------------------------------------------
bool Widget::isOnDisplayBorder()
{
    QRect display=QApplication::desktop()->screenGeometry();

    if(leftBorder<=0 || rightBorder>=display.right()) return true;
    if(topBorder<=0 || bottomBorder>=display.bottom()) return true;
    return false;
}
//-----------------------------------------------
void Widget::slotShowMessage()
{
    MesageBox *m=new MesageBox;
    m->show();
    close();
}
//-----------------------------------------------
void Widget::keyPressEvent(QKeyEvent *ke)
{
    if(ke->key()==Qt::Key_C) close();
}

//
// MesageBox
//
MesageBox::MesageBox(QWidget *parent) : QWidget(parent)
{
    setFixedSize(200,80);
    bClose=new QPushButton("Согласен, это справедливо.");
    lText=new QLabel("Ты следующий на повышение,\nпосле Сержа=)");
    QObject::connect(bClose, SIGNAL(clicked()), this, SLOT(close()));
    QVBoxLayout *box=new QVBoxLayout;
    box->addWidget(lText);
    box->setSpacing(1);
    box->addWidget(bClose);
    setLayout(box);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon("wink.png"));
    sec=0;
    startTimer(1000);
}
//-----------------------------------------------
MesageBox::~MesageBox()
{
    delete bClose;
    delete lText;
}
//-----------------------------------------------
void MesageBox::timerEvent(QTimerEvent *te)
{
    sec++;
    if(sec==60) close();
}



