#include "testenv.h"

TestEnv::TestEnv(int num, int dist, QWidget *parent) : QWidget(parent), totalTargets(num), moveDistance(dist)
{
   started = false;
   timer = new QTime();
   curTarget = new QRect(0,0,20,20);
   qsrand((uint)QTime::currentTime().msec());
   setMinimumSize(500, 500);
}

void TestEnv::start()
{
   started = true;
   totalTime=0;
   errors=0;
   remainingTargets = totalTargets;
   newTarget();
   
   timer->start();
   update();
}

int TestEnv::retTime()
{
   return totalTime;
}

void TestEnv::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
   this->setAutoFillBackground(true);
   this->setPalette(QPalette(Qt::blue));
   painter.setBrush(palette().foreground().color());
   if (started)
      painter.drawRect(*curTarget);
   QWidget::paintEvent(event);
}

void TestEnv::mousePressEvent(QMouseEvent *event)
{
   if (!started)
   {
      QWidget(event);
   }
   else
   {
      if (curTarget->contains(event->pos()))
      {
         emit TestEnv::emitHit(--remainingTargets);
         if (remainingTargets == 0)
         {
            TestEnv::stop();
         }
         else
         {
            newTarget();
            update();
         }
      }
      else
      {
         errors++;
      }
   }
}

void TestEnv::stop()
{
   started = false;
   totalTime = timer->elapsed();

   update();
}

void TestEnv::newTarget()
{
   QPoint curPos = TestEnv::mapFromGlobal(QCursor::pos());
   bool notDone = true;
   while (notDone)
   {
      int degreesToMove = qrand() % 360;
      double tempDegree = degreesToMove%90;
      
      double radiansToMove = (tempDegree * PI) /180.0;
      int moveX = (int)(qCos(radiansToMove) * moveDistance);
      int moveY = (int)(qSin(radiansToMove) * moveDistance);

      QPoint newPos;
      if (degreesToMove >= 0 && degreesToMove <=90)
      {
         newPos = QPoint((curPos.x() + moveX), (curPos.y() - moveY));
      }
      else if (degreesToMove >90 && degreesToMove <= 180)
      {
         newPos = QPoint((curPos.x() - moveX), (curPos.y() - moveY));
      }
      else if (degreesToMove >180 && degreesToMove <= 270)
      {
         newPos = QPoint((curPos.x() - moveX), (curPos.y() + moveY));
      }
      else
      {
         newPos = QPoint((curPos.x() + moveX), (curPos.y() + moveY));
      }
      curTarget->moveTo(newPos);
      if (QWidget::frameGeometry().contains(*curTarget, true))
      {
         notDone = false;
      }
   }
}
