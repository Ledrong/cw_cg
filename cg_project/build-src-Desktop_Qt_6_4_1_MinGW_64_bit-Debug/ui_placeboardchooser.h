/********************************************************************************
** Form generated from reading UI file 'placeboardchooser.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLACEBOARDCHOOSER_H
#define UI_PLACEBOARDCHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_PlaceBoardChooser
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
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QLabel *label_6;
    QLineEdit *lineEdit_6;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *PlaceBoardChooser)
    {
        if (PlaceBoardChooser->objectName().isEmpty())
            PlaceBoardChooser->setObjectName("PlaceBoardChooser");
        PlaceBoardChooser->resize(660, 435);
        verticalLayout_2 = new QVBoxLayout(PlaceBoardChooser);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        label_2 = new QLabel(PlaceBoardChooser);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(PlaceBoardChooser);
        lineEdit->setObjectName("lineEdit");

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(PlaceBoardChooser);
        label_3->setObjectName("label_3");

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(PlaceBoardChooser);
        lineEdit_2->setObjectName("lineEdit_2");

        verticalLayout->addWidget(lineEdit_2);

        label = new QLabel(PlaceBoardChooser);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        lineEdit_3 = new QLineEdit(PlaceBoardChooser);
        lineEdit_3->setObjectName("lineEdit_3");

        verticalLayout->addWidget(lineEdit_3);

        label_4 = new QLabel(PlaceBoardChooser);
        label_4->setObjectName("label_4");

        verticalLayout->addWidget(label_4);

        lineEdit_4 = new QLineEdit(PlaceBoardChooser);
        lineEdit_4->setObjectName("lineEdit_4");

        verticalLayout->addWidget(lineEdit_4);

        label_5 = new QLabel(PlaceBoardChooser);
        label_5->setObjectName("label_5");

        verticalLayout->addWidget(label_5);

        lineEdit_5 = new QLineEdit(PlaceBoardChooser);
        lineEdit_5->setObjectName("lineEdit_5");

        verticalLayout->addWidget(lineEdit_5);

        label_6 = new QLabel(PlaceBoardChooser);
        label_6->setObjectName("label_6");

        verticalLayout->addWidget(label_6);

        lineEdit_6 = new QLineEdit(PlaceBoardChooser);
        lineEdit_6->setObjectName("lineEdit_6");

        verticalLayout->addWidget(lineEdit_6);

        buttonBox = new QDialogButtonBox(PlaceBoardChooser);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(PlaceBoardChooser);

        QMetaObject::connectSlotsByName(PlaceBoardChooser);
    } // setupUi

    void retranslateUi(QDialog *PlaceBoardChooser)
    {
        PlaceBoardChooser->setWindowTitle(QCoreApplication::translate("PlaceBoardChooser", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Ox)", nullptr));
        lineEdit->setText(QCoreApplication::translate("PlaceBoardChooser", "1", nullptr));
        label_3->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\275\320\276\320\274\320\265\321\200 \321\217\321\207\320\265\320\271\320\272\320\270 (\320\277\320\276 \320\276\321\201\320\270 Oy)", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("PlaceBoardChooser", "1", nullptr));
        label->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \321\210\320\270\321\200\320\270\320\275\321\203 \321\210\320\272\320\260\321\204\320\260 (\320\272\320\276\320\273-\320\262\320\276 \321\217\321\207\320\265\320\265\320\272 \320\277\320\276 \320\276\321\201\320\270 Ox):", nullptr));
        lineEdit_3->setInputMask(QString());
        lineEdit_3->setText(QCoreApplication::translate("PlaceBoardChooser", "3", nullptr));
        label_4->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\264\320\273\320\270\320\275\321\203 \321\210\320\272\320\260\321\204\320\260 (\320\272\320\276\320\273-\320\262\320\276 \321\217\321\207\320\265\320\265\320\272 \320\277\320\276 \320\276\321\201\320\270 Oy):", nullptr));
        lineEdit_4->setText(QCoreApplication::translate("PlaceBoardChooser", "1", nullptr));
        label_5->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\262\321\213\321\201\320\276\321\202\321\203  \321\210\320\272\320\260\321\204\320\260 (\320\272\320\276\320\273-\320\262\320\276 \321\217\321\207\320\265\320\265\320\272)", nullptr));
        lineEdit_5->setText(QCoreApplication::translate("PlaceBoardChooser", "4", nullptr));
        label_6->setText(QCoreApplication::translate("PlaceBoardChooser", "\320\232\320\260\320\272 \320\277\320\276\320\262\320\265\321\200\320\275\321\203\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202? 1 - \320\264\320\262\320\265\321\200\321\206\320\260\320\274\320\270 \320\276\321\202 \320\275\320\260\320\261\320\273\321\216\320\264\320\260\321\202\320\265\320\273\321\217, 2 - \320\264\320\262\320\265\321\200\321\206\320\260\320\274\320\270 \320\275\320\260 \320\275\320\260\320\261\320\273\321\216\320\264\320\260\321\202\320\265\320\273\321\217, 3 - \320\264\320\262\320\265\321\200\321\206\320\260\320\274\320\270 \320\262\320\277\321\200\320\260\320\262\320\276, 4 - \320\264\320\262\320\265\321\200\321\206\320\260\320\274\320\270 \320\262\320\273\320\265\320\262\320\276", nullptr));
        lineEdit_6->setText(QCoreApplication::translate("PlaceBoardChooser", "2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlaceBoardChooser: public Ui_PlaceBoardChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLACEBOARDCHOOSER_H
