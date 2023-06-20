/********************************************************************************
** Form generated from reading UI file 'objecthangman.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OBJECTHANGMAN_H
#define UI_OBJECTHANGMAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_ObjectHangman
{
public:
    QListWidget *listWidget;
    QPushButton *pushButton;

    void setupUi(QDialog *ObjectHangman)
    {
        if (ObjectHangman->objectName().isEmpty())
            ObjectHangman->setObjectName("ObjectHangman");
        ObjectHangman->resize(299, 440);
        listWidget = new QListWidget(ObjectHangman);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 0, 301, 391));
        pushButton = new QPushButton(ObjectHangman);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(0, 390, 301, 51));

        retranslateUi(ObjectHangman);

        QMetaObject::connectSlotsByName(ObjectHangman);
    } // setupUi

    void retranslateUi(QDialog *ObjectHangman)
    {
        ObjectHangman->setWindowTitle(QCoreApplication::translate("ObjectHangman", "Dialog", nullptr));
        pushButton->setText(QCoreApplication::translate("ObjectHangman", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ObjectHangman: public Ui_ObjectHangman {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OBJECTHANGMAN_H
