#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include <QCursor>
#include <QList>
#include "testenv.h"
#include "startDialog.h"
 
class MainWindow : public QMainWindow {
 
  Q_OBJECT
   
public:
 
   MainWindow(QWidget *parent=0);

   //setUp();

   public slots:

   void getName(QString name);
   void getAge(QString age);
   void getGender(QString gender);
   void getDominantHand(QString dominantHand);
   

  private:
  
   TestEnv *testArea;
   QString *participantName;
   QList <QCursor> *cursorList;
   StartDialog *startInfo;

   QString testerName;
   QString testerAge;
   QString testerGender;
   QString testerDominantHand;
   
};
 
#endif
