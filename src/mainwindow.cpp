#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   startInfo = new StartDialog(this);
   setCentralWidget(testArea = new TestEnv());

   QObject::connect(startInfo, SIGNAL(name(QString)), this, SLOT(getName(QString)));
   QObject::connect(startInfo, SIGNAL(age(QString)), this, SLOT(getAge(QString)));
   QObject::connect(startInfo, SIGNAL(gender(QString)), this, SLOT(getGender(QString)));
   QObject::connect(startInfo, SIGNAL(dominantHand(QString)), this, SLOT(getDominantHand(QString)));

   
   startInfo->exec();
   while(startInfo->result() != QDialog::Accepted)
   {
      QMessageBox::information(this, "Form Fill-Out", QString("You must fill out all of the fields to continue"));
      startInfo->exec();
   }

   showMaximized();
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
