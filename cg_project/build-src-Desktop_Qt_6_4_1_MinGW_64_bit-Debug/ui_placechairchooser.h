/********************************************************************************
** Form generated from reading UI file 'placechairchooser.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACECHAIRCHOOSER_H
#define UI_PLACECHAIRCHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlaceChairChooser
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QLabel *label;
    QLineEdit *lineEdit_3;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PlaceChairChooser)
    {
        if (PlaceChairChooser->objectName().isEmpty())
            PlaceChairChooser->setObjectName("PlaceChairChooser");
        PlaceChairChooser->resize(513, 376);
        verticalLayout_2 = new QVBoxLayout(PlaceChairChooser);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(PlaceChairChooser);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(PlaceChairChooser);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(PlaceChairChooser);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(PlaceChairChooser);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        label = new QLabel(PlaceChairChooser);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEdit_3 = new QLineEdit(PlaceChairChooser);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);

        buttonBox = new QDialogButtonBox(PlaceChairChooser);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PlaceChairChooser);

        QMetaObject::connectSlotsByName(PlaceChairChooser);
    } // setupUi

    void retranslateUi(QDialog *PlaceChairChooser)
    {
        PlaceChairChooser->setWindowTitle(QCoreApplication::translate("PlaceChairChooser", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PlaceChairChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Ox)", nullptr));
        lineEdit->setText(QCoreApplication::translate("PlaceChairChooser", "5", nullptr));
        label_3->setText(QCoreApplication::translate("PlaceChairChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Oy)", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("PlaceChairChooser", "5", nullptr));
        label->setText(QCoreApplication::translate("PlaceChairChooser", "\320\232\320\260\320\272 \320\277\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202? 1 - \321\201\320\277\320\270\320\275\320\272\320\276\320\271 \320\272 \320\275\320\260\320\261\320\273\321\216\320\264\320\260\321\202\320\265\320\273\321\216, 2 - \321\201\320\277\320\270\320\275\320\272\320\276\320\271 \320\276\321\202 \320\275\320\260\320\261\320\273\321\216\320\264\320\260\321\202\320\265\320\273\321\217, 3 - \321\201\320\277\320\270\320\275\320\272\320\276\320\271 \320\262\320\277\321\200\320\260\320\262\320\276, 4 - \321\201\320\277\320\270\320\275\320\272\320\276\320\271 \320\262\320\273\320\265\320\262\320\276", nullptr));
        lineEdit_3->setText(QCoreApplication::translate("PlaceChairChooser", "2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaceChairChooser: public Ui_PlaceChairChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLACECHAIRCHOOSER_H
