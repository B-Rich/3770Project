#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   startInfo = new StartDialog(this);
   setCentralWidget(testArea = new TestEnv(10,100,this));

   getInfo();
   showMaximized();

   startTests();
}

void MainWindow::getInfo()
{
   QList<QString> values;
   while (values.size() == 0)
   {
      if(startInfo->exec() != QDialog::Accepted)
      {
         QMessageBox::information(this, "Form Fill-Out", QString("Program requires user information to continue."));
      }
      values = startInfo->getValues();
      if (values.size() == 0)
      {
         QMessageBox::information(this, "Form Fill-Out", QString("All fields must be filled out!"));
      }
   }
   
   testerName = values[0];
   testerAge = values[1];
   testerGender = values[2];
   testerDominantHand = values[3];
}

void MainWindow::startTests()
{
   qDebug() << testerName << testerAge << testerGender << testerDominantHand;
   testArea->start();
}
