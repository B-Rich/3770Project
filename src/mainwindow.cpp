#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   setCentralWidget(testArea = new TestEnv());
}
