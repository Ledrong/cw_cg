/********************************************************************************
** Form generated from reading UI file 'placetreechooser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACETREECHOOSER_H
#define UI_PLACETREECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlaceTreeChooser
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PlaceTreeChooser)
    {
        if (PlaceTreeChooser->objectName().isEmpty())
            PlaceTreeChooser->setObjectName(QString::fromUtf8("PlaceTreeChooser"));
        PlaceTreeChooser->resize(406, 159);
        verticalLayout_2 = new QVBoxLayout(PlaceTreeChooser);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(PlaceTreeChooser);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(PlaceTreeChooser);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(PlaceTreeChooser);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(PlaceTreeChooser);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        buttonBox = new QDialogButtonBox(PlaceTreeChooser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PlaceTreeChooser);

        QMetaObject::connectSlotsByName(PlaceTreeChooser);
    } // setupUi

    void retranslateUi(QDialog *PlaceTreeChooser)
    {
        PlaceTreeChooser->setWindowTitle(QCoreApplication::translate("PlaceTreeChooser", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PlaceTreeChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Ox)", nullptr));
        lineEdit->setText(QCoreApplication::translate("PlaceTreeChooser", "5", nullptr));
        label_3->setText(QCoreApplication::translate("PlaceTreeChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Oy)", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("PlaceTreeChooser", "5", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaceTreeChooser: public Ui_PlaceTreeChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLACETREECHOOSER_H
