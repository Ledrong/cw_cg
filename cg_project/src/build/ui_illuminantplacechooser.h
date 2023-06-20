/********************************************************************************
** Form generated from reading UI file 'illuminantplacechooser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ILLUMINANTPLACECHOOSER_H
#define UI_ILLUMINANTPLACECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_IlluminantPlaceChooser
{
public:
    QVBoxLayout *verticalLayout_5;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_8;
    QLineEdit *XAngleInp;
    QLabel *label_9;
    QLineEdit *YAngleInp;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *IlluminantPlaceChooser)
    {
        if (IlluminantPlaceChooser->objectName().isEmpty())
            IlluminantPlaceChooser->setObjectName(QString::fromUtf8("IlluminantPlaceChooser"));
        IlluminantPlaceChooser->resize(397, 150);
        verticalLayout_5 = new QVBoxLayout(IlluminantPlaceChooser);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        label_8 = new QLabel(IlluminantPlaceChooser);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_4->addWidget(label_8);

        XAngleInp = new QLineEdit(IlluminantPlaceChooser);
        XAngleInp->setObjectName(QString::fromUtf8("XAngleInp"));

        verticalLayout_4->addWidget(XAngleInp);

        label_9 = new QLabel(IlluminantPlaceChooser);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_4->addWidget(label_9);

        YAngleInp = new QLineEdit(IlluminantPlaceChooser);
        YAngleInp->setObjectName(QString::fromUtf8("YAngleInp"));

        verticalLayout_4->addWidget(YAngleInp);

        buttonBox = new QDialogButtonBox(IlluminantPlaceChooser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout_4->addWidget(buttonBox);


        verticalLayout_5->addLayout(verticalLayout_4);


        retranslateUi(IlluminantPlaceChooser);

        QMetaObject::connectSlotsByName(IlluminantPlaceChooser);
    } // setupUi

    void retranslateUi(QDialog *IlluminantPlaceChooser)
    {
        IlluminantPlaceChooser->setWindowTitle(QCoreApplication::translate("IlluminantPlaceChooser", "Dialog", nullptr));
        label_8->setText(QCoreApplication::translate("IlluminantPlaceChooser", "\320\243\320\263\320\276\320\273 \320\277\320\276 \320\276\321\201\320\270 X (\320\262 \320\263\321\200\320\260\320\264\321\203\321\201\320\260\321\205):", nullptr));
        XAngleInp->setText(QCoreApplication::translate("IlluminantPlaceChooser", "30", nullptr));
        label_9->setText(QCoreApplication::translate("IlluminantPlaceChooser", "\320\243\320\263\320\276\320\273 \320\277\320\276 \320\276\321\201\320\270 Y (\320\262 \320\263\321\200\320\260\320\264\321\203\321\201\320\260\321\205):", nullptr));
        YAngleInp->setText(QCoreApplication::translate("IlluminantPlaceChooser", "30", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IlluminantPlaceChooser: public Ui_IlluminantPlaceChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ILLUMINANTPLACECHOOSER_H
