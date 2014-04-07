#ifndef TESTENV_H
#define TESTENV_H

#include <QWidget>
#include <QTime>
#include <QPainter>
#include <QRect>
#include <QMouseEvent>
#include <QPoint>
#include <QCursor>
#include <QtGlobal>
#include <QtCore/qmath.h>

class TestEnv : public QWidget {
 
  Q_OBJECT
   
public:
 
  TestEnv(int num=100, int dist=100, QWidget *parent=0);
   
public slots:
   void start();
   int retTime();

signals:
   void emitHit(const int &rem);

protected:
   void paintEvent(QPaintEvent *event);
   void mousePressEvent(QMouseEvent *event);
   
private:
   bool started;
   QTime *timer;
   int totalTime;
   int totalTargets;
   int remainingTargets;
   int moveDistance;
   QRect *curTarget;
   static const double PI = 3.14159265359;
   int errors;

   void stop();
   void newTarget();
   
};

#endif
