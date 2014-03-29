#ifndef MAINWINDOW_H
#define MAINWINDOW_H
 
#include <QMainWindow>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>
#include <QLineEdit>
#include "testenv.h"
 
class MainWindow : public QMainWindow {
 
  Q_OBJECT
   
public:
 
  MainWindow(QWidget *parent=0);

private:
   TestEnv *testArea;
   QString participantName;
};
 
#endif
