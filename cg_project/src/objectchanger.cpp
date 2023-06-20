#include "objectchanger.hpp"
#include "ui_objectchanger.h"

#include "movechooser.hpp"

#include <QErrorMessage>
#include <QDebug>

ObjectChanger::ObjectChanger(UsageFacade *facade_, QWidget *parent)
    : QDialog(parent), ui(new Ui::ObjectChanger)
{
    ui->setupUi(this);
    this->setWindowTitle("Перемещение объектов сцены");

    facade = facade_;
    CellScene *scene = facade->getScene();

    PolModel model;
    PolModel::model_t modelType_;
    int count = 0;

    for (size_t i = 0; i < scene->getModelsNum(); i++)
    {
        model = scene->getModel(i);
        modelType_ = model.getModelType();

        if (modelType_ == PolModel::model_t::Board || \
                modelType_ == PolModel::model_t::tableTrunk || \
                modelType_ == PolModel::model_t::chairFoliage || \
                modelType_ == PolModel::model_t::Bed || \
                modelType_ == PolModel::model_t::Torsher || \
                modelType_ == PolModel::model_t::Tv)
        {
            count++;
            ui->listWidget->addItem(
                    QString::number(count) + ". " +
                                    scene->getModel(i).getName()      + " - (" +
                    QString::number(scene->getModel(i).getUsedXCell() + 1) + "; " +
                    QString::number(scene->getModel(i).getUsedYCell() + 1) + ")");
        }
    }
}

ObjectChanger::~ObjectChanger() { delete ui; }

void ObjectChanger::on_pushButton_clicked()
{
    size_t curRow = size_t(this->ui->listWidget->currentRow());
    if (curRow < 0)
        return;

    CellScene *scene     = facade->getScene();
    size_t modelsNum     = scene->getModelsNum();
    PolModel model;
//    PolModel::model_t modelType_;
//    bool flag = false;

    moveChooser moveChooserWindow(nullptr);
    moveChooserWindow.setModal(true);
    moveChooserWindow.exec();

    if (moveChooserWindow.status == moveChooser::OK)
    {
        model = scene->getModel(curRow);

        if (model.getModelNum() == curRow)
        {
            scene->clearUsedCells(curRow);
            int retCode = changeModel(scene->getModel(curRow),
                moveChooserWindow.getNewXCell(),
                moveChooserWindow.getNewYCell());

            if (retCode == 1)
            {
                close();
                scene->markUsedCells(curRow);
                QErrorMessage *err = new QErrorMessage();
                err->showMessage("Некоторые из выбранных ячеек заняты");
                return;
                }
            else if(retCode == 2)
            {
                close();
                scene->markUsedCells(curRow);
                QErrorMessage *err = new QErrorMessage();
                err->showMessage("Объект не влезает в сцену");
                return;
            }
            else if(retCode == 3)
            {
                close();
                scene->markUsedCells(curRow);
                QErrorMessage *err = new QErrorMessage();
                err->showMessage("Машины разрешено ставить только на доргах");
                return;
            }
            else if(retCode == 4)
            {
                close();
                scene->markUsedCells(curRow);
                QErrorMessage *err = new QErrorMessage();
                err->showMessage("Дороги не должны прилегать к дому");
                return;
            }
            else
            {
                scene->deleteModel(curRow);
                scene->markUsedCells(scene->getModelsNum() - 1);
                scene->printUsedCells();
            }
//            modelsNum --;
//            i--;
        }
        modelsNum --;
        recalculationModelsNum();
    }
    else
        return;

    close();
}

int ObjectChanger::changeModel(PolModel &model, int newXCell, int newYCell)
{
    int retCode = 0;

    PolModel::model_t modelType_ = model.getModelType();

    if (modelType_ == PolModel::model_t::Board)
    {
        retCode = facade->addBoard(newXCell, newYCell,
                                   model.getWidthModel(),
                                   model.getHeightModel(),
                                   model.getBoardHeight(),
                                   model.getDirectionModel());
    }
    else if (modelType_ == PolModel::model_t::tableTrunk)
    {
        retCode = facade->addTable(newXCell, newYCell);
    }
    else if (modelType_ == PolModel::model_t::chairFoliage)
    {
        retCode = facade->addChair(newXCell, newYCell, model.getDirectionModel());
    }
    else if (modelType_ == PolModel::model_t::Bed)
    {
        retCode = facade->addBed(newXCell, newYCell, model.getDirectionModel());
    }
    else if (modelType_ == PolModel::model_t::Torsher)
    {
        retCode = facade->addTorsher(newXCell, newYCell);
    }
    else if (modelType_ == PolModel::model_t::Tv)
    {
        retCode = facade->addTv(newXCell, newYCell,                                   model.getWidthModel(),
                                model.getHeightModel(),
                                model.getBoardHeight(),
                                model.getDirectionModel());
    }

    return retCode;
}

void ObjectChanger::recalculationModelsNum()
{
    CellScene *scene     = facade->getScene();
    size_t modelsNum = scene->getModelsNum();
    PolModel model;
    PolModel::model_t modelType_;
    int cur = 0, border = 0;

    for (size_t i = 0; i < modelsNum; i++)
    {
        model = scene->getModel(cur);
        modelType_ = model.getModelType();
        scene->getModel(cur).setModelNum(i);
        cur++;
    }
}
