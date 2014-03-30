#ifndef STARTDIALOG_H
#define STARTDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSpinBox>

class StartDialog : public QDialog
{
   Q_OBJECT

      public:

   StartDialog(QWidget *parent = 0);

   //public signals:

   //void name(QString name);

   //protected event:

   //clicked();
	     

  private:

   QLabel *nameLabel;
   QLabel *ageLabel;
   QLabel *genderLabel;
   QLabel *dominantHandLabel;

   QLineEdit *nameLineEdit;

   QRadioButton *maleGenderRadioButton;
   QRadioButton *femaleGenderRadioButton;
   QRadioButton *leftDominantHandRadioButton;
   QRadioButton *rightDominantHandRadioButton;

   QButtonGroup *genderButtonGroup;
   QButtonGroup *dominantHandButtonGroup;

   QSpinBox *ageSpinBox;

   QPushButton *okButton;
   QPushButton *cancelButton;
   
};

#endif
