#include "testEnv.h"

TestEnv::TestEnv(int num, int dist, int s, QWidget *parent) : QWidget(parent), totalTargets(num), moveDistance(dist), size(s)
{
   started = false;
   timer = new QTime();
   curTarget = new QRect(0,0,size,size);
   qsrand((uint)QTime::currentTime().msec());
   setMinimumSize(500, 500);
   this->setAutoFillBackground(true);
   this->setPalette(QPalette(Qt::white));
}

void TestEnv::start()
{
   totalTime=0;
   errors=0;
   remainingTargets = totalTargets;
   newTarget();
   started = true;
   emit emitHit(totalTargets);
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
   painter.setBrush(QBrush(Qt::gray));
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
         emit TestEnv::emitError(++errors);
      }
   }
}

void TestEnv::stop()
{
   started = false;
   totalTime = timer->elapsed();
   update();
   emit TestEnv::emitHit(0);
   emit TestEnv::emitError(0);
   emit TestEnv::retResults(totalTime, errors);
   emit TestEnv::emitFinish();
}

void TestEnv::newTarget()
{
   QPoint curPos = TestEnv::mapFromGlobal(QCursor::pos());
   QRect curGeom = geometry();

   bool notDone = true;
   int i=0; //To catch infinite loops
   while (notDone && (i<100))
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
      if (curGeom.contains(*curTarget, true))
      {
         if (curTarget->bottomRight().y() < curGeom.height())
         {
            notDone = false;
         }
      }
      i++;
      if (i==100) //Break the infinite loop
      {
         throw QString("Could not create a new target within field");
         stop();
      }
   }
}
