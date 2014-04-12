#include "startDialog.h"

const int MIN_AGE = 17;
const int MAX_AGE = 90;

StartDialog::StartDialog(QWidget *parent) : QDialog(parent)
{
   nameLabel = new QLabel("Name:");
   ageLabel = new QLabel("Age:");
   genderLabel = new QLabel("Gender:");
   dominantHandLabel = new QLabel("Dominant Hand:");
   dominantEyeLabel = new QLabel("Dominant Eye:");

   nameLineEdit = new QLineEdit();

   maleGenderRadioButton = new QRadioButton("Male", this);
   femaleGenderRadioButton = new QRadioButton("Female", this);
   leftDominantHandRadioButton = new QRadioButton("Left", this);
   rightDominantHandRadioButton = new QRadioButton("Right", this);
   leftDominantEyeRadioButton = new QRadioButton("Left", this);
   rightDominantEyeRadioButton = new QRadioButton("Right", this);

   genderButtonGroup = new QButtonGroup();
   genderButtonGroup->addButton(maleGenderRadioButton);
   genderButtonGroup->addButton(femaleGenderRadioButton);

   dominantHandButtonGroup = new QButtonGroup();
   dominantHandButtonGroup->addButton(leftDominantHandRadioButton);
   dominantHandButtonGroup->addButton(rightDominantHandRadioButton);

   dominantEyeButtonGroup = new QButtonGroup();
   dominantEyeButtonGroup->addButton(leftDominantEyeRadioButton);
   dominantEyeButtonGroup->addButton(rightDominantEyeRadioButton);

   ageSpinBox = new QSpinBox();
   ageSpinBox->setMinimum(MIN_AGE);
   ageSpinBox->setMaximum(MAX_AGE);
   
   okButton = new QPushButton("Ok");
   cancelButton = new QPushButton("Cancel");
   okButton->setDefault(true);

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

   QHBoxLayout *dominantEyeLayout = new QHBoxLayout();
   dominantEyeLayout->addWidget(dominantEyeLabel);
   dominantEyeLayout->addWidget(leftDominantEyeRadioButton);
   dominantEyeLayout->addWidget(rightDominantEyeRadioButton);

   QHBoxLayout *buttonsLayout = new QHBoxLayout();
   buttonsLayout->addWidget(cancelButton);
   buttonsLayout->addWidget(okButton);

   QVBoxLayout *layout = new QVBoxLayout();
   layout->addLayout(nameLayout);
   layout->addLayout(ageLayout);
   layout->addLayout(genderLayout);
   layout->addLayout(dominantHandLayout);
   layout->addLayout(dominantEyeLayout);
   layout->addLayout(buttonsLayout);

   setLayout(layout);

   QObject::connect(okButton, SIGNAL(clicked()), this, SLOT(accept()));
   QObject::connect(cancelButton, SIGNAL(clicked()), this, SLOT(reject()));
}

QList<QString> StartDialog::getValues()
{
   QList<QString> values;
   if ((nameLineEdit->text() == QString("")) || (ageSpinBox->value() == 0))
      return values;
   values << nameLineEdit->text() << QString::number(ageSpinBox->value());
   
   if (maleGenderRadioButton->isChecked())
      values << maleGenderRadioButton->text();
   else if (femaleGenderRadioButton->isChecked())
      values << femaleGenderRadioButton->text();
   else
      return QList<QString>();

   if (leftDominantHandRadioButton->isChecked())
      values << leftDominantHandRadioButton->text();
   else if (rightDominantHandRadioButton->isChecked())
      values << rightDominantHandRadioButton->text();
   else
      return QList<QString>();

   if (leftDominantEyeRadioButton->isChecked())
      values << leftDominantEyeRadioButton->text();
   else if (rightDominantEyeRadioButton->isChecked())
      values << rightDominantEyeRadioButton->text();
   else
      return QList<QString>();	

   return values;
}
