/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "specialgraphicsview.hpp"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_2;
    QWidget *centralwidget;
    QPushButton *pushButton_addModel;
    SpecialGraphicsView *graphicsView;
    QPushButton *pushButton_createScene;
    QPushButton *pushButton_deleteModel;
    QListWidget *listWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_sceneToInitianPosition;
    QPushButton *pushButton_left;
    QPushButton *pushButton_right;
    QPushButton *pushButton_up;
    QPushButton *pushButton_down;
    QPushButton *pushButton_leftCircle;
    QPushButton *pushButton_rightCircle;
    QLabel *label_3;
    QLabel *label_4;
    QPushButton *pushButton_zoom;
    QPushButton *pushButton_distance;
    QLabel *label_5;
    QPushButton *pushButton_left_scene;
    QPushButton *pushButton_up_scene;
    QPushButton *pushButton_down_scene;
    QPushButton *pushButton_right_scene;
    QPushButton *pushButton_moveModel;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1191, 762);
        QIcon icon;
        icon.addFile(QString::fromUtf8("imgs/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        action_2 = new QAction(MainWindow);
        action_2->setObjectName("action_2");
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton_addModel = new QPushButton(centralwidget);
        pushButton_addModel->setObjectName("pushButton_addModel");
        pushButton_addModel->setGeometry(QRect(0, 150, 291, 51));
        QFont font;
        font.setPointSize(12);
        pushButton_addModel->setFont(font);
        graphicsView = new SpecialGraphicsView(centralwidget);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(290, 0, 901, 761));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        pushButton_createScene = new QPushButton(centralwidget);
        pushButton_createScene->setObjectName("pushButton_createScene");
        pushButton_createScene->setGeometry(QRect(0, 460, 141, 51));
        pushButton_createScene->setFont(font);
        pushButton_deleteModel = new QPushButton(centralwidget);
        pushButton_deleteModel->setObjectName("pushButton_deleteModel");
        pushButton_deleteModel->setGeometry(QRect(0, 210, 141, 51));
        pushButton_deleteModel->setFont(font);
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName("listWidget");
        listWidget->setGeometry(QRect(0, 40, 291, 111));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Consolas")});
        font1.setPointSize(16);
        listWidget->setFont(font1);
        listWidget->setIconSize(QSize(100, 100));
        label = new QLabel(centralwidget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 410, 291, 51));
        QFont font2;
        font2.setPointSize(12);
        font2.setBold(true);
        font2.setItalic(false);
        label->setFont(font2);
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(0, 0, 291, 41));
        label_2->setFont(font2);
        label_2->setAlignment(Qt::AlignCenter);
        pushButton_sceneToInitianPosition = new QPushButton(centralwidget);
        pushButton_sceneToInitianPosition->setObjectName("pushButton_sceneToInitianPosition");
        pushButton_sceneToInitianPosition->setGeometry(QRect(150, 460, 141, 51));
        pushButton_sceneToInitianPosition->setFont(font);
        pushButton_left = new QPushButton(centralwidget);
        pushButton_left->setObjectName("pushButton_left");
        pushButton_left->setGeometry(QRect(10, 370, 81, 41));
        pushButton_right = new QPushButton(centralwidget);
        pushButton_right->setObjectName("pushButton_right");
        pushButton_right->setGeometry(QRect(190, 370, 80, 41));
        pushButton_up = new QPushButton(centralwidget);
        pushButton_up->setObjectName("pushButton_up");
        pushButton_up->setGeometry(QRect(100, 320, 81, 41));
        pushButton_down = new QPushButton(centralwidget);
        pushButton_down->setObjectName("pushButton_down");
        pushButton_down->setGeometry(QRect(100, 370, 81, 41));
        pushButton_leftCircle = new QPushButton(centralwidget);
        pushButton_leftCircle->setObjectName("pushButton_leftCircle");
        pushButton_leftCircle->setGeometry(QRect(190, 320, 81, 41));
        pushButton_rightCircle = new QPushButton(centralwidget);
        pushButton_rightCircle->setObjectName("pushButton_rightCircle");
        pushButton_rightCircle->setGeometry(QRect(10, 320, 81, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(0, 270, 291, 41));
        label_3->setFont(font2);
        label_3->setAlignment(Qt::AlignCenter);
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(0, 520, 291, 41));
        label_4->setFont(font2);
        label_4->setAlignment(Qt::AlignCenter);
        pushButton_zoom = new QPushButton(centralwidget);
        pushButton_zoom->setObjectName("pushButton_zoom");
        pushButton_zoom->setGeometry(QRect(0, 560, 141, 51));
        pushButton_distance = new QPushButton(centralwidget);
        pushButton_distance->setObjectName("pushButton_distance");
        pushButton_distance->setGeometry(QRect(150, 560, 141, 51));
        label_5 = new QLabel(centralwidget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(0, 620, 291, 41));
        label_5->setFont(font2);
        label_5->setAlignment(Qt::AlignCenter);
        pushButton_left_scene = new QPushButton(centralwidget);
        pushButton_left_scene->setObjectName("pushButton_left_scene");
        pushButton_left_scene->setGeometry(QRect(10, 680, 81, 41));
        pushButton_up_scene = new QPushButton(centralwidget);
        pushButton_up_scene->setObjectName("pushButton_up_scene");
        pushButton_up_scene->setGeometry(QRect(100, 660, 81, 41));
        pushButton_down_scene = new QPushButton(centralwidget);
        pushButton_down_scene->setObjectName("pushButton_down_scene");
        pushButton_down_scene->setGeometry(QRect(100, 710, 81, 41));
        pushButton_right_scene = new QPushButton(centralwidget);
        pushButton_right_scene->setObjectName("pushButton_right_scene");
        pushButton_right_scene->setGeometry(QRect(190, 680, 80, 41));
        pushButton_moveModel = new QPushButton(centralwidget);
        pushButton_moveModel->setObjectName("pushButton_moveModel");
        pushButton_moveModel->setGeometry(QRect(150, 210, 141, 51));
        pushButton_moveModel->setFont(font);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1191, 24));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\202\321\200\320\276\320\262, \320\277\320\273\320\260\320\275\320\270\321\200\320\276\320\262\321\211\320\270\320\272 \320\272\320\276\320\274\320\275\320\260\321\202\320\275\320\276\320\263\320\276 \320\277\321\200\320\276\321\201\321\202\321\200\320\260\320\275\321\201\321\202\320\262\320\260", nullptr));
        action_2->setText(QCoreApplication::translate("MainWindow", "\320\240\321\203\320\272\320\276\320\262\320\276\320\264\321\201\321\202\320\262\320\276 \320\277\320\276\320\273\321\214\320\267\320\276\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        pushButton_addModel->setText(QCoreApplication::translate("MainWindow", "\320\243\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
        pushButton_createScene->setText(QCoreApplication::translate("MainWindow", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214 \321\201\321\206\320\265\320\275\321\203", nullptr));
        pushButton_deleteModel->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\241\320\246\320\225\320\235\320\220", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\236\320\221\320\252\320\225\320\232\320\242\320\253", nullptr));
        pushButton_sceneToInitianPosition->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265\n"
" \320\277\320\276\320\273\320\276\320\266\320\265\320\275\320\270\320\265 \321\201\321\206\320\265\320\275\321\213", nullptr));
        pushButton_left->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_right->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_up->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_down->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        pushButton_leftCircle->setText(QCoreApplication::translate("MainWindow", "\342\206\272", nullptr));
        pushButton_rightCircle->setText(QCoreApplication::translate("MainWindow", "\342\206\273", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\320\222\320\240\320\220\320\251\320\225\320\235\320\230\320\225 \320\236\320\221\320\252\320\225\320\232\320\242\320\236\320\222", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\320\234\320\220\320\241\320\250\320\242\320\220\320\221\320\230\320\240\320\236\320\222\320\220\320\235\320\230\320\225 \320\241\320\246\320\225\320\235\320\253", nullptr));
        pushButton_zoom->setText(QCoreApplication::translate("MainWindow", "\320\237\321\200\320\270\320\261\320\273\320\270\320\267\320\270\321\202\321\214", nullptr));
        pushButton_distance->setText(QCoreApplication::translate("MainWindow", "\320\236\321\202\320\264\320\260\320\273\320\270\321\202\321\214", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\320\237\320\225\320\240\320\225\320\234\320\225\320\251\320\225\320\235\320\230\320\225 \320\241\320\246\320\225\320\235\320\253", nullptr));
        pushButton_left_scene->setText(QCoreApplication::translate("MainWindow", "\342\206\220", nullptr));
        pushButton_up_scene->setText(QCoreApplication::translate("MainWindow", "\342\206\221", nullptr));
        pushButton_down_scene->setText(QCoreApplication::translate("MainWindow", "\342\206\223", nullptr));
        pushButton_right_scene->setText(QCoreApplication::translate("MainWindow", "\342\206\222", nullptr));
        pushButton_moveModel->setText(QCoreApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\274\320\265\321\201\321\202\320\270\321\202\321\214 \320\276\320\261\321\212\320\265\320\272\321\202", nullptr));
        menu->setTitle(QCoreApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
