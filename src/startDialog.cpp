
#include "startDialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

const int MIN_AGE = 17;
const int MAX_AGE = 90;

StartDialog::StartDialog(QWidget *parent) : QDialog(parent)
{
   nameLabel = new QLabel("Name:");
   ageLabel = new QLabel("Age:");
   genderLabel = new QLabel("Gender:");
   dominantHandLabel = new QLabel("Dominant Hand:");

   nameLineEdit = new QLineEdit();

   maleGenderRadioButton = new QRadioButton("Male", this);
   femaleGenderRadioButton = new QRadioButton("Female", this);
   leftDominantHandRadioButton = new QRadioButton("Left", this);
   rightDominantHandRadioButton = new QRadioButton("Right", this);

   genderButtonGroup = new QButtonGroup();
   genderButtonGroup->addButton(maleGenderRadioButton);
   genderButtonGroup->addButton(femaleGenderRadioButton);

   dominantHandButtonGroup = new QButtonGroup();
   dominantHandButtonGroup->addButton(leftDominantHandRadioButton);
   dominantHandButtonGroup->addButton(rightDominantHandRadioButton);

   ageSpinBox = new QSpinBox();
   ageSpinBox->setMinimum(MIN_AGE);
   ageSpinBox->setMaximum(MAX_AGE);
   
   okButton = new QPushButton("Ok");
   cancelButton = new QPushButton("Cancel");

   QHBoxLayout *nameLayout = new QHBoxLayout();
   nameLayout->addWidget(nameLabel);
   nameLayout->addWidget(nameLineEdit);

   QHBoxLayout *ageLayout = new QHBoxLayout();
   ageLayout->addWidget(ageLabel);
   ageLayout->addWidget(ageSpinBox);

   QHBoxLayout *genderLayout = new QHBoxLayout();
   genderLayout->addWidget(genderLabel);
   genderLayout->addWidget(maleGenderRadioButton);
   genderLayout->addWidget(femaleGenderRadioButton);

   QHBoxLayout *dominantHandLayout = new QHBoxLayout();
   dominantHandLayout->addWidget(dominantHandLabel);
   dominantHandLayout->addWidget(leftDominantHandRadioButton);
   dominantHandLayout->addWidget(rightDominantHandRadioButton);

   QHBoxLayout *buttonsLayout = new QHBoxLayout();
   buttonsLayout->addWidget(okButton);
   buttonsLayout->addWidget(cancelButton);

   QVBoxLayout *layout = new QVBoxLayout();
   layout->addLayout(nameLayout);
   layout->addLayout(ageLayout);
   layout->addLayout(genderLayout);
   layout->addLayout(dominantHandLayout);
   layout->addLayout(buttonsLayout);

   setLayout(layout);

   
}
