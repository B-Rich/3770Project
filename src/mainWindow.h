#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include <QCursor>
#include <QPixmap>
#include <QBitmap>
#include <QList>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFile>
#include <QTextStream>

#include "testEnv.h"
#include "startDialog.h"

struct ResultHold {
   ResultHold(const int &t, const int &e) : time(t), errors(e) {}
   int time;
   int errors;
};

class MainWindow : public QMainWindow {
 
  Q_OBJECT
   
public:
 
   MainWindow(QWidget *parent=0);

public slots:
   void setRem(const int &x) {tarRem->setText(QString::number(x));}
   void setErr(const int &x) {errorNum->setText(QString::number(x));}
   void saveResults(const int &t, const int &e);
   void startTests();
   
protected:
   void setUp();
   void getInfo();
   void createDock();
   void loadCursors();
   void displayInformation();
   void thankUser();
   void saveResults();
   void saveResultsToFile();

private:
   TestEnv *testArea;
   TestEnv *testArea2;
   QString *participantName;
   QList <QCursor> cursorList;
   int roundNum;
   StartDialog *startInfo;

   QString testerName;
   QString testerAge;
   QString testerGender;
   QString testerDominantHand;
   QString testerDominantEye;

   QLabel *tarRem;
   QLabel *errorNum;
   QLabel *rndNum;

   QList <ResultHold> results;
   
   static const QString cursorDir;
   static const QString resultsDir;
   static const int numTargets;
};
 
#endif
