/********************************************************************************
** Form generated from reading UI file 'placetablechooser.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACETABLECHOOSER_H
#define UI_PLACETABLECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlaceTableChooser
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PlaceTableChooser)
    {
        if (PlaceTableChooser->objectName().isEmpty())
            PlaceTableChooser->setObjectName("PlaceTableChooser");
        PlaceTableChooser->resize(406, 159);
        verticalLayout_2 = new QVBoxLayout(PlaceTableChooser);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(PlaceTableChooser);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(PlaceTableChooser);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(PlaceTableChooser);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(PlaceTableChooser);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        buttonBox = new QDialogButtonBox(PlaceTableChooser);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PlaceTableChooser);

        QMetaObject::connectSlotsByName(PlaceTableChooser);
    } // setupUi

    void retranslateUi(QDialog *PlaceTableChooser)
    {
        PlaceTableChooser->setWindowTitle(QCoreApplication::translate("PlaceTableChooser", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PlaceTableChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Ox)", nullptr));
        lineEdit->setText(QCoreApplication::translate("PlaceTableChooser", "5", nullptr));
        label_3->setText(QCoreApplication::translate("PlaceTableChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Oy)", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("PlaceTableChooser", "4", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaceTableChooser: public Ui_PlaceTableChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLACETABLECHOOSER_H
