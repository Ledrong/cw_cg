/********************************************************************************
** Form generated from reading UI file 'movechooser.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MOVECHOOSER_H
#define UI_MOVECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_moveChooser
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_4;
    QLineEdit *lineEdit_3;
    QLabel *label_3;
    QLabel *label_4;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *moveChooser)
    {
        if (moveChooser->objectName().isEmpty())
            moveChooser->setObjectName("moveChooser");
        moveChooser->resize(265, 115);
        verticalLayout = new QVBoxLayout(moveChooser);
        verticalLayout->setObjectName("verticalLayout");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        lineEdit_4 = new QLineEdit(moveChooser);
        lineEdit_4->setObjectName("lineEdit_4");

        gridLayout->addWidget(lineEdit_4, 1, 0, 1, 1);

        lineEdit_3 = new QLineEdit(moveChooser);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 1, 1, 1, 1);

        label_3 = new QLabel(moveChooser);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        label_4 = new QLabel(moveChooser);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        buttonBox = new QDialogButtonBox(moveChooser);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(moveChooser);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, moveChooser, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, moveChooser, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(moveChooser);
    } // setupUi

    void retranslateUi(QDialog *moveChooser)
    {
        moveChooser->setWindowTitle(QCoreApplication::translate("moveChooser", "Dialog", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("moveChooser", "0", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("moveChooser", "0", nullptr));
        label_3->setText(QCoreApplication::translate("moveChooser", "\320\235\320\276\320\262\320\260\321\217 \321\217\321\207\320\265\320\271\320\272\320\260 X:", nullptr));
        label_4->setText(QCoreApplication::translate("moveChooser", "\320\235\320\276\320\262\320\260\321\217 \321\217\321\207\320\265\320\271\320\272\320\260 Y:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class moveChooser: public Ui_moveChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MOVECHOOSER_H
