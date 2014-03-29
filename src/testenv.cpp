#include "testenv.h"

TestEnv::TestEnv(QWidget *parent) : QWidget(parent)
{
   started = false;
   timer = new QTime();
}

void TestEnv::start()
{
   started = true;
   timer->start();
   update();
}

void TestEnv::stop()
{
   started = false;
   totalTime = timer->elapsed();
   update();
}

void TestEnv::reset()
{
   totalTime = 0;
}

int TestEnv::retTime()
{
   return totalTime;
}

void TestEnv::paintEvent(QPaintEvent *event)
{
   QPainter painter(this);
   painter.setRenderHint(QPainter::Antialiasing, true);
}
