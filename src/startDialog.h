#ifndef STARTDIALOG_H
#define STARTDIALOG_H


#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QSpinBox>
#include <QList>
#include <QString>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>

class StartDialog : public QDialog
{
   Q_OBJECT

      public:

   StartDialog(QWidget *parent = 0);
   QList<QString> getValues();

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
