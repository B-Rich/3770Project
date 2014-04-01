#ifndef STARTDIALOG_H
#define STARTDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>

class StartDialog : public QDialog
{
   Q_OBJECT

      public:

   StartDialog(QWidget *parent = 0);

   signals:

   void name(QString name);
   void age(QString age);
   void gender(QString gender);
   void dominantHand(QString dominantHand);

   
   public slots:

   void accepted();  

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

   QString testerName;
   QString testerAge;
   QString testerGender;
   QString testerDominantHand;
   
};

#endif
