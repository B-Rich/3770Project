#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include <QCursor>
#include <QList>
#include <QDebug>
#include <QDockWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "testenv.h"
#include "startDialog.h"
 
class MainWindow : public QMainWindow {
 
  Q_OBJECT
   
public:
 
   MainWindow(QWidget *parent=0);

public slots:
   void setRem(const int &x) {tarRem->setText(QString::number(x));}
   void setErr(const int &x) {errorNum->setText(QString::number(x));}
   
protected:
   void setUp();
   void getInfo();
   void startTests();
   void createDock();

private:
   TestEnv *testArea;
   QString *participantName;
   QList <QCursor> *cursorList;
   StartDialog *startInfo;

   QString testerName;
   QString testerAge;
   QString testerGender;
   QString testerDominantHand;

   QLabel *tarRem;
   QLabel *errorNum;
};
 
#endif
