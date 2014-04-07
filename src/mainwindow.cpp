#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   showMaximized();
   startInfo = new StartDialog(this);
   setCentralWidget(testArea = new TestEnv(10,200,50,this));
   QObject::connect(testArea, SIGNAL(emitHit(const int&)), this, SLOT(setRem(const int&)));
   QObject::connect(testArea, SIGNAL(emitError(const int&)), this, SLOT(setErr(const int&)));
   createDock();
   getInfo();
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
   testArea->start();
}

void MainWindow::createDock()
{
   QDockWidget* dock = new QDockWidget("", this);
   dock->setAllowedAreas(Qt::TopDockWidgetArea);
   dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

   QLabel *tarRemTitle = new QLabel("Targets Remaining:");
   tarRem = new QLabel("");
   QLabel *errorNumTitle = new QLabel("Errors:");
   errorNum = new QLabel("");

   QWidget *parentWidget = new QWidget();
   QHBoxLayout *layout = new QHBoxLayout();

   layout->addWidget(tarRemTitle);
   layout->addWidget(tarRem);
   layout->addWidget(errorNumTitle);
   layout->addWidget(errorNum);
   //layout->addSpace();

   parentWidget->setLayout(layout);
   dock->setWidget(parentWidget);
   addDockWidget(Qt::TopDockWidgetArea, dock);
}
