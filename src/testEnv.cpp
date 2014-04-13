#include "testEnv.h"

TestEnv::TestEnv(int num, int dist, int s, QWidget *parent) : QWidget(parent), totalTargets(num), moveDistance(dist), size(s)
{
   started = false;
   timer = new QTime();
   curTarget = new QRect(0,0,size,size);
   qsrand((uint)QTime::currentTime().msec());
   setMinimumSize(250,250);
   this->setAutoFillBackground(true);
   this->setPalette(QPalette(Qt::white));
   outline = new QRect(0,0,geometry().width()-1,geometry().height()-1);

   distTimer = new QTimer();
   distance = 0;
   positionList = new QList<QPoint>;
   mousePositionList = new QList<QPoint>;

   QObject::connect(distTimer, SIGNAL(timeout()), this, SLOT(positionUpdate()));

   setMouseTracking(true);
}

void TestEnv::start()
{
	distance = 0;
	positionList->clear();
	mousePositionList->clear();
   totalTime=0;
   errors=0;
   remainingTargets = totalTargets;
   newTarget();
   started = true;
   emit emitHit(totalTargets);
   timer->start();
   distTimer->start(50);
   update();
}

int TestEnv::retTime()
{
   return totalTime;
}

void TestEnv::positionUpdate()
{
   positionList->push_back(*(mousePositionList->end() - 1));
}

void TestEnv::mouseMoveEvent(QMouseEvent* event)
{
	mousePositionList->push_back(event->pos());
}

void TestEnv::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
   
   painter.drawRect(*outline);

   painter.setBrush(QBrush(Qt::darkGray));
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
	calcDist();
   emit TestEnv::retResults(totalTime, errors, distance);
   emit TestEnv::emitFinish();
}

void TestEnv::calcDist()
{
   for(QList<QPoint>::iterator it = positionList->begin(); it != positionList->end(); it++)
   {
      if(it != positionList->end() - 1)
      {
         int p1X = it->x();
			int p1Y = it->y();
			it++;
			int p2X = it->x();
			int p2Y = it->y();

			double xDiff = (p1X - p2X) * 1.0;
			double yDiff = (p1Y - p2Y) * 1.0;

			double xDiffSquare = pow(xDiff, 2.0);
			double yDiffSquare = pow(yDiff, 2.0);

			double sum = xDiffSquare + yDiffSquare;
			distance += sqrt(sum);

			it--;
      }
   }
}

void TestEnv::newTarget()
{
   QPoint curPos = TestEnv::mapFromGlobal(QCursor::pos());

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
      if (outline->contains(*curTarget, true))
      {
         notDone = false;
      }
      i++;
      if (i==100) //Break the infinite loop
      {
         throw QString("Could not create a new target within field");
         stop();
      }
   }
}

void TestEnv::resizeEvent(QResizeEvent *event)
{
   outline->setSize(event->size()-QSize(1,1));
   QWidget::resizeEvent(event);
}
