#include "mainwindow.h"
 
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
   startInfo = new StartDialog();
   startInfo->exec();
   setCentralWidget(testArea = new TestEnv());
   
}

/*MainWindow::setUp()
{

   
}*/
