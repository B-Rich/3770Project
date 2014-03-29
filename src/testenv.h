#ifndef TESTENV_H
#define TESTENV_H

#include <QWidget>
#include <QTime>
#include <QPainter>

class TestEnv : public QWidget {
 
  Q_OBJECT
   
public:
 
  TestEnv(QWidget *parent=0);
   
public slots:
   void start();
   void stop();
   void reset();
   int retTime();

protected:
   void paintEvent(QPaintEvent *event);
   
private:
   bool started;
   QTime *timer;
   int totalTime;
};

#endif
