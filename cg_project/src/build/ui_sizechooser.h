/********************************************************************************
** Form generated from reading UI file 'sizechooser.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIZECHOOSER_H
#define UI_SIZECHOOSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SizeChooser
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SizeChooser)
    {
        if (SizeChooser->objectName().isEmpty())
            SizeChooser->setObjectName(QString::fromUtf8("SizeChooser"));
        SizeChooser->resize(379, 167);
        verticalLayout = new QVBoxLayout(SizeChooser);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(SizeChooser);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        lineEdit = new QLineEdit(SizeChooser);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        verticalLayout->addWidget(lineEdit);

        label_3 = new QLabel(SizeChooser);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout->addWidget(label_3);

        lineEdit_2 = new QLineEdit(SizeChooser);
        lineEdit_2->setObjectName(QString::fromUtf8("lineEdit_2"));

        verticalLayout->addWidget(lineEdit_2);

        buttonBox = new QDialogButtonBox(SizeChooser);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setMinimumSize(QSize(361, 26));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(SizeChooser);
        QObject::connect(buttonBox, SIGNAL(rejected()), SizeChooser, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), SizeChooser, SLOT(accept()));

        QMetaObject::connectSlotsByName(SizeChooser);
    } // setupUi

    void retranslateUi(QDialog *SizeChooser)
    {
        SizeChooser->setWindowTitle(QCoreApplication::translate("SizeChooser", "Dialog", nullptr));
        label_2->setText(QCoreApplication::translate("SizeChooser", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\272\320\273\320\265\321\202\320\276\320\272 \320\262 \320\264\320\273\320\270\320\275\321\203:", nullptr));
        lineEdit->setText(QCoreApplication::translate("SizeChooser", "10", nullptr));
        label_3->setText(QCoreApplication::translate("SizeChooser", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\272\320\273\320\265\321\202\320\276\320\272 \320\262 \321\210\320\270\321\200\320\270\320\275\321\203:", nullptr));
        lineEdit_2->setText(QCoreApplication::translate("SizeChooser", "10", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SizeChooser: public Ui_SizeChooser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIZECHOOSER_H
