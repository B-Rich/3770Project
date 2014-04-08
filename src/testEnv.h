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
#include <QDebug>

class TestEnv : public QWidget {
 
  Q_OBJECT
   
public:
 
  TestEnv(int num=10, int dist=100, int s=20, QWidget *parent=0);
   
public slots:
   void start();
   int retTime();
   int getErrors() {return errors;}
   void changeSize(int s) {size=s;}
   void changeDistance(int d) {moveDistance=d;}
   void changeNumTargets(int n) {totalTargets=n;}

signals:
   void emitHit(const int &rem);
   void emitError(const int &er);
   void retResults(const int &t, const int &e);
   void emitFinish();

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
   int size;
   QRect *curTarget;
   static const double PI = 3.14159265359;
   int errors;

   void stop();
   void newTarget();
   
};

#endif
