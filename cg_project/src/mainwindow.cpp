#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "QDebug"
#include <QErrorMessage>
#include <QShortcut>
#include <QTimer>

#include "config.hpp"

#include "illuminantplacechooser.hpp"
#include "objecthangman.hpp"
#include "objectchanger.hpp"
#include "placechooser.h"
#include "sizechooser.hpp"
#include "specialgraphicsview.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    facade = new UsageFacade;

    QListWidgetItem *board     = new QListWidgetItem("      Шкаф");
    ui->listWidget->addItem(board);

    QListWidgetItem *table       = new QListWidgetItem("      Стол");
    ui->listWidget->addItem(table);
    QListWidgetItem *bed       = new QListWidgetItem("      Кровать");
    ui->listWidget->addItem(bed);
    QListWidgetItem *chair       = new QListWidgetItem("      Стул");
    ui->listWidget->addItem(chair);
    QListWidgetItem *torsher       = new QListWidgetItem("      Торшер");
    ui->listWidget->addItem(torsher);
    QListWidgetItem *tv       = new QListWidgetItem("      Телевизор");
    ui->listWidget->addItem(tv);

    QListWidgetItem *flashlight = new QListWidgetItem("      Источник света");
    ui->listWidget->addItem(flashlight);


    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    QShortcut *shortcutDown = new QShortcut(QKeySequence("down"), this);
    QObject::connect(shortcutDown, SIGNAL(activated()), this, SLOT(pictureDown()));

    QShortcut *shortcutUp = new QShortcut(QKeySequence("up"), this);
    QObject::connect(shortcutUp, SIGNAL(activated()), this, SLOT(pictureUp()));

    QShortcut *shortcutLeft = new QShortcut(QKeySequence("left"), this);
    QObject::connect(shortcutLeft, SIGNAL(activated()), this, SLOT(pictureLeft()));

    QShortcut *shortcutRight = new QShortcut(QKeySequence("right"), this);
    QObject::connect(shortcutRight, SIGNAL(activated()), this, SLOT(pictureRight()));

    QShortcut *shortcutScaleUp = new QShortcut(QKeySequence("z"), this);
    QObject::connect(shortcutScaleUp, SIGNAL(activated()), this, SLOT(pictureScaleUp()));

    QShortcut *shortcutScaleDown = new QShortcut(QKeySequence("x"), this);
    QObject::connect(
        shortcutScaleDown, SIGNAL(activated()), this, SLOT(pictureScaleDown()));

    QShortcut *shortcutRotateXRight = new QShortcut(QKeySequence("s"), this);
    QObject::connect(
        shortcutRotateXRight, SIGNAL(activated()), this, SLOT(pictureRotateXRight()));

    QShortcut *shortcutRotateXLeft = new QShortcut(QKeySequence("w"), this);
    QObject::connect(
        shortcutRotateXLeft, SIGNAL(activated()), this, SLOT(pictureRotateXLeft()));

    QShortcut *shortcutRotateYRight = new QShortcut(QKeySequence("a"), this);
    QObject::connect(
        shortcutRotateYRight, SIGNAL(activated()), this, SLOT(pictureRotateYRight()));

    QShortcut *shortcutRotateYLeft = new QShortcut(QKeySequence("d"), this);
    QObject::connect(
        shortcutRotateYLeft, SIGNAL(activated()), this, SLOT(pictureRotateYLeft()));

    QShortcut *shortcutRotateZLeft = new QShortcut(QKeySequence("q"), this);
    QObject::connect(
        shortcutRotateZLeft, SIGNAL(activated()), this, SLOT(pictureRotateZLeft()));

    QShortcut *shortcutRotateZRight = new QShortcut(QKeySequence("e"), this);
    QObject::connect(
        shortcutRotateZRight, SIGNAL(activated()), this, SLOT(pictureRotateZRight()));
}

MainWindow::~MainWindow() { delete ui; }


void MainWindow::pictureDown()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->moveDownScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureUp()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->moveUpScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureLeft()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->moveLeftScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRight()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->moveRightScene(MOVE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureScaleUp()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->scaleScene(SCALE_VALUE + 1, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureScaleDown()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->scaleScene(1 - SCALE_VALUE, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXRight()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateXScene(ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateXLeft()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateXScene(-ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYRight()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateYScene(ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateYLeft()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateYScene(-ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZRight()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateZScene(ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureRotateZLeft()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->rotateZScene(-ROTATE_UNIT, ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::pictureToCenter()
{
    if (!facade->isSceneSet())
        return;

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();

    QGraphicsScene *setScene = facade->toCenter(ui->graphicsView->rect());
    ui->graphicsView->setScene(setScene);
}

void MainWindow::on_pushButton_createScene_clicked()
{
    SizeChooser chooserWindow(nullptr);
    chooserWindow.setModal(true);
    chooserWindow.exec();

    if (chooserWindow.getWidth() == -1 || chooserWindow.getheight() == -1)
        return;

    facade->setCellScene(chooserWindow.getWidth(), chooserWindow.getheight());
    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}

void MainWindow::on_pushButton_addModel_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    int curRow = this->ui->listWidget->currentRow();
    if (curRow < 0)
        return;

    if (curRow >= 0 && curRow < 6)
    {
        int retCode = 0;

        if (curRow == 0)
        {
            PlaceBoardChooser placeBoardChooserWindow(nullptr);
            placeBoardChooserWindow.setModal(true);
            placeBoardChooserWindow.exec();

            if (placeBoardChooserWindow.status == PlaceBoardChooser::OK)
                retCode = facade->addBoard(
                            placeBoardChooserWindow.getXCell(),
                            placeBoardChooserWindow.getYCell(),
                            placeBoardChooserWindow.getModelLength(),
                            placeBoardChooserWindow.getModelHeight(),
                            placeBoardChooserWindow.getBoardHeight(),
                            placeBoardChooserWindow.getModelDirection());
            else
                return;
        }
        else if (curRow == 1)
        {
            PlaceTableChooser PlaceTableChooserWindow(nullptr);
            PlaceTableChooserWindow.setModal(true);
            PlaceTableChooserWindow.exec();

            if (PlaceTableChooserWindow.status == PlaceTableChooser::OK)
                retCode = facade->addTable(
                        PlaceTableChooserWindow.getXCell(),
                        PlaceTableChooserWindow.getYCell());
            else
                return;
        }
        else if (curRow == 3)
        {
            PlaceChairChooser PlaceChairChooserWindow(nullptr);
            PlaceChairChooserWindow.setModal(true);
            PlaceChairChooserWindow.exec();

            if (PlaceChairChooserWindow.status == PlaceChairChooser::OK)
                retCode = facade->addChair(
                        PlaceChairChooserWindow.getXCell(),
                        PlaceChairChooserWindow.getYCell(),
                        PlaceChairChooserWindow.getModelDirection());
            else
                return;
        }
        else if (curRow == 2)
        {
            PlaceBedChooser PlaceBedChooserWindow(nullptr);
            PlaceBedChooserWindow.setModal(true);
            PlaceBedChooserWindow.exec();

            if (PlaceBedChooserWindow.status == PlaceBedChooser::OK)
                retCode = facade->addBed(
                        PlaceBedChooserWindow.getXCell(),
                        PlaceBedChooserWindow.getYCell(),
                        PlaceBedChooserWindow.getModelDirection());
            else
                return;
        }
        else if (curRow == 4)
        {
            PlaceTorsherChooser PlaceTorsherChooserWindow(nullptr);
            PlaceTorsherChooserWindow.setModal(true);
            PlaceTorsherChooserWindow.exec();

            if (PlaceTorsherChooserWindow.status == PlaceTorsherChooser::OK)
                retCode = facade->addTorsher(
                        PlaceTorsherChooserWindow.getXCell(),
                        PlaceTorsherChooserWindow.getYCell());
            else
                return;
        }
        else if (curRow == 5)
        {
            PlaceTvChooser PlaceTvChooserWindow(nullptr);
            PlaceTvChooserWindow.setModal(true);
            PlaceTvChooserWindow.exec();

            if (PlaceTvChooserWindow.status == PlaceTvChooser::OK)
                retCode = facade->addTv(
                            PlaceTvChooserWindow.getXCell(),
                            PlaceTvChooserWindow.getYCell(),
                            PlaceTvChooserWindow.getModelLength(),
                            PlaceTvChooserWindow.getModelHeight(),
                            PlaceTvChooserWindow.getBoardHeight(),
                            PlaceTvChooserWindow.getModelDirection());
            else
                return;
        }

        if (retCode == 1)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("Некоторые из выбранных ячеек заняты");
            return;
        }
        else if(retCode == 2)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("Объект не влезает в сцену");
            return;
        }
        else if(retCode == 3)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("разрешено ставить только");
            return;
        }
        else if(retCode == 4)
        {
            QErrorMessage *err = new QErrorMessage();
            err->showMessage("не должны прилегать");
            return;
        }
    }
    else
    {
        IlluminantPlaceChooser placeIlluminantChooserWindow(nullptr);
        placeIlluminantChooserWindow.setModal(true);
        placeIlluminantChooserWindow.exec();

        if (placeIlluminantChooserWindow.status == IlluminantPlaceChooser::OK)
            facade->addIlluminant(
                placeIlluminantChooserWindow.getXAngle(),
                placeIlluminantChooserWindow.getYAngle());
        else
            return;
    }

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}


void MainWindow::on_pushButton_deleteModel_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    ObjectHangman objectHangmanWindow(facade->getScene(), nullptr);
    objectHangmanWindow.setModal(true);
    objectHangmanWindow.exec();

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}


void MainWindow::on_pushButton_moveModel_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    ObjectChanger objectChangerWindow(facade, nullptr);
    objectChangerWindow.setModal(true);
    objectChangerWindow.exec();

    QGraphicsScene *setScene = facade->drawScene(ui->graphicsView->rect());

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    ui->graphicsView->setScene(setScene);
}

void MainWindow::on_pushButton_sceneToInitianPosition_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    if (ui->graphicsView->scene())
        delete ui->graphicsView->scene();
    QGraphicsScene *setScene = facade->toCenter(ui->graphicsView->rect());

    ui->graphicsView->setScene(setScene);
}



void MainWindow::on_pushButton_up_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateXLeft();
}

void MainWindow::on_pushButton_down_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateXRight();
}

void MainWindow::on_pushButton_left_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateYRight();
}

void MainWindow::on_pushButton_right_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateYLeft();
}

void MainWindow::on_pushButton_leftCircle_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateZRight();
}

void MainWindow::on_pushButton_rightCircle_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRotateZLeft();
}



void MainWindow::on_pushButton_up_scene_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureUp();
}

void MainWindow::on_pushButton_down_scene_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureDown();
}

void MainWindow::on_pushButton_left_scene_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureLeft();
}

void MainWindow::on_pushButton_right_scene_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureRight();
}



void MainWindow::on_pushButton_zoom_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureScaleUp();
}

void MainWindow::on_pushButton_distance_clicked()
{
    if (!facade->isSceneSet())
    {
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Сцена ещё не была задана.");
        return;
    }

    pictureScaleDown();
}
