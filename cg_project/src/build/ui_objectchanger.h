/********************************************************************************
** Form generated from reading UI file 'objectchanger.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTCHANGER_H
#define UI_OBJECTCHANGER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ObjectChanger
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *ObjectChanger)
    {
        if (ObjectChanger->objectName().isEmpty())
            ObjectChanger->setObjectName(QString::fromUtf8("ObjectChanger"));
        ObjectChanger->resize(300, 441);
        listWidget = new QListWidget(ObjectChanger);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 301, 391));
        pushButton = new QPushButton(ObjectChanger);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(0, 390, 301, 51));

        retranslateUi(ObjectChanger);

        QMetaObject::connectSlotsByName(ObjectChanger);
    } // setupUi

    void retranslateUi(QDialog *ObjectChanger)
    {
        ObjectChanger->setWindowTitle(QCoreApplication::translate("ObjectChanger", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("ObjectChanger", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectChanger: public Ui_ObjectChanger {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTCHANGER_H
