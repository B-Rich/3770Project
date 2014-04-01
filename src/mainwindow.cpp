#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   startInfo = new StartDialog();
   setCentralWidget(testArea = new TestEnv());

   QObject::connect(startInfo, SIGNAL(name), this, SLOT(getName));
   QObject::connect(startInfo, SIGNAL(age), this, SLOT(getAge));
   QObject::connect(startInfo, SIGNAL(gender), this, SLOT(getGender));
   QObject::connect(startInfo, SIGNAL(dominantHand), this, SLOT(getDominantHand));

   
   int button = startInfo->exec();
   if(button == QMessageBox::Ok)
   {
      
   }
   
   
}

/*MainWindow::setUp()
{

   
}*/

void MainWindow::getName(QString name)
{
   testerName = name;
}

void MainWindow::getAge(QString age)
{
   testerAge = age;
}

void MainWindow::getGender(QString gender)
{
   testerGender = gender;
}

void MainWindow::getDominantHand(QString dominantHand)
{
   testerDominantHand = dominantHand;
}
