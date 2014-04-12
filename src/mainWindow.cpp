#include "mainWindow.h"
 
const QString MainWindow::cursorDir = "../cursors/";
const QString MainWindow::resultsDir = "../results/";
const int MainWindow::numTargets = 10;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   showFullScreen();
   startInfo = new StartDialog(this);
   setCentralWidget(testArea = new TestEnv(numTargets,200,15,this));
   QObject::connect(testArea, SIGNAL(emitHit(const int&)), this, SLOT(setRem(const int&)));
   QObject::connect(testArea, SIGNAL(emitError(const int&)), this, SLOT(setErr(const int&)));
   QObject::connect(testArea, SIGNAL(emitFinish()), this, SLOT(startTests()));
   QObject::connect(testArea, SIGNAL(retResults(const int&, const int&)), this, SLOT(saveResults(const int&, const int&)));
   createDock();
   getInfo();
   loadCursors();
   displayInformation();
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

void MainWindow::loadCursors()
{
   cursorList << Qt::ArrowCursor;
   
   QPixmap cursorCrossPic;
   cursorCrossPic.load((cursorDir+QString("cursorCross.bmp")), "BMP", Qt::MonoOnly);
   cursorCrossPic.setMask(QBitmap(cursorCrossPic));
   QCursor cursorCross(cursorCrossPic, 15,15);
   cursorList << cursorCross;

   QPixmap cursorDownPic;
   cursorDownPic.load((cursorDir+QString("cursorDown.bmp")), "BMP", Qt::MonoOnly);
   cursorDownPic.setMask(QBitmap(cursorDownPic));
   QCursor cursorDown(cursorDownPic, 15,31);
   cursorList << cursorDown;

   QPixmap cursorLeftPic;
   cursorLeftPic.load((cursorDir+QString("cursorLeft.bmp")), "BMP", Qt::MonoOnly);
   cursorLeftPic.setMask(QBitmap(cursorLeftPic));
   QCursor cursorLeft(cursorLeftPic, 0,15);
   cursorList << cursorLeft;

   QPixmap cursorRightPic;
   cursorRightPic.load((cursorDir+QString("cursorRight.bmp")), "BMP", Qt::MonoOnly);
   cursorRightPic.setMask(QBitmap(cursorRightPic));
   QCursor cursorRight(cursorRightPic, 31,15);
   cursorList << cursorRight;
   
   roundNum = 1;
}

void MainWindow::displayInformation()
{
   QString info = 
      "Welcome " + testerName + "!\n\n" +
      "This program will measure the speed and accuracy \n" +
      "with which you (the user) are able to click each target.\n\n" +
      "You will be presented with " + QString::number(cursorList.size()) + " different cursor styles and\n" +
      QString::number(numTargets) + " targets.\n\n" +
      "Upon clicking 'OK', the test will begin!\n\n" + "Good Luck!";
   
   QMessageBox msgBox;
   msgBox.setText(info);
   msgBox.setWindowTitle("Instructions");
   msgBox.exec();
}

void MainWindow::startTests()
{
   if (cursorList.size() == 0) // Finished Testing, go to results
   {
      setCursor(Qt::ArrowCursor);
      thankUser();
      saveResultsToFile();
      close();
   }
   else
   {
      rndNum->setText(QString::number(roundNum));
      QMessageBox::information(this,"Information", QString("Now beginning round %1.\n Click OK to begin.").arg(roundNum));
      setCursor(cursorList.takeFirst());
      try //Catch infinite loop
      {
      testArea->start();
      } catch (QString temp)
      {
         qDebug() << temp;
      }
      roundNum++;
   }
}

void MainWindow::createDock()
{
   QDockWidget* dock = new QDockWidget("", this);
   dock->setAllowedAreas(Qt::TopDockWidgetArea);
   dock->setFeatures(QDockWidget::NoDockWidgetFeatures);

   QLabel *roundNumTitle = new QLabel("Round #:");
   rndNum = new QLabel(QString::number(0));
   QLabel *tarRemTitle = new QLabel("Targets Remaining:");
   tarRem = new QLabel(QString::number(0));
   QLabel *errorNumTitle = new QLabel("Errors:");
   errorNum = new QLabel(QString::number(0));

   QWidget *parentWidget = new QWidget();
   QHBoxLayout *layout = new QHBoxLayout();

   layout->addWidget(roundNumTitle);
   layout->addWidget(rndNum);
   layout->addStretch();
   layout->addWidget(tarRemTitle);
   layout->addWidget(tarRem);
   layout->addStretch();
   layout->addWidget(errorNumTitle);
   layout->addWidget(errorNum);

   parentWidget->setLayout(layout);
   dock->setWidget(parentWidget);
   addDockWidget(Qt::TopDockWidgetArea, dock);
}

void MainWindow::thankUser()
{
   QString info = 
      "Thank you " + testerName + " for participating in our tests!\n\n" +
      "Your performance data and general attributes will be recorded solely \n" +
      "for the purpose of constructing statistics from the sample groups.\n" + 
      "Your name will not be associated with any published data.";
   QMessageBox::information(this,"Thank You!", info);
}

void MainWindow::saveResults(const int &t, const int &e)
{
   results.append(ResultHold(t,e));
}

void MainWindow::saveResultsToFile()
{
   QString filename = resultsDir+testerName+tr(".txt");
   QFile file(filename);

   bool duplicate=true;
   int j=1;
   while (duplicate)
   {
      if (file.exists())
         file.setFileName(resultsDir+testerName+QString::number(1)+tr(".txt"));
      else
         duplicate = false;
      j++;
   }
   
   if (!file.open(QIODevice::WriteOnly))
   {
      QMessageBox::warning(this, tr("Unable to save results"), tr("Cannot write file %1: %2").arg(filename).arg(file.errorString()));
   }
   else
   {
      QTextStream out(&file);
      out << "Name:    " << testerName << endl;
      out << "Age:     " << testerAge << endl;
      out << "Gender:  " << testerGender << endl;
      out << "DomHand: " << testerDominantHand << endl;
      out << endl << endl;

      for (int i=0; i<results.size(); i++)
      {
         out << tr("Test #: %1").arg(i+1) << endl;
         out << tr("Time:   %1").arg(results[i].time) << endl;
         out << tr("Errors: %1").arg(results[i].errors);
         if (i != results.size()-1)
            out << endl << endl;
         else
            out << endl;
      }
   }
}
