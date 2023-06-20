#include "objecthangman.hpp"
#include "ui_objecthangman.h"

#include <QErrorMessage>
#include <QDebug>

ObjectHangman::ObjectHangman(CellScene *scene_, QWidget *parent)
    : QDialog(parent), ui(new Ui::ObjectHangman)
{
    ui->setupUi(this);
    this->setWindowTitle("Удаление объектов сцены");

    scene = scene_;

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
                                    scene->getModel(i).getName()       + " - (" +
                    QString::number(scene->getModel(i).getUsedXCell() + 1) + "; " +
                    QString::number(scene->getModel(i).getUsedYCell() + 1) + ")");
        }
    }

    for (size_t i = 0; i < scene->getIllumNum(); i++)
        ui->listWidget->addItem(
                    QString::number(count + i + 1)                       + ". Источ. света (" +
                    QString::number(scene->getIlluminant(i).getXAngle()) + "°; " +
                    QString::number(scene->getIlluminant(i).getYAngle()) + "°)");
}

ObjectHangman::~ObjectHangman() { delete ui; }

void ObjectHangman::on_pushButton_clicked()
{
    size_t curRow = size_t(this->ui->listWidget->currentRow());
    if (curRow < 0)
        return;

    size_t modelsNum     = scene->getModelsNum();
//    size_t realModelsNum = scene->getRealModelsNum();
    PolModel model;
    if (curRow < modelsNum)
    {
        model = scene->getModel(curRow);
        scene->deleteModel(curRow);
        modelsNum--;

        recalculationModelsNum();
    }
    else
    {
        scene->deleteIlluminant(curRow - modelsNum);
    }

    close();
}

void ObjectHangman::recalculationModelsNum()
{
    size_t modelsNum = scene->getModelsNum();
    PolModel model;
    PolModel::model_t modelType_;
    int cur = 0, border = 0;

    for (size_t i = 0; i < modelsNum; i++)
    {
        model = scene->getModel(cur);
        modelType_ = model.getModelType();

//        if (modelType_ == PolModel::model_t::Board)
//        {
//            border = 2;
//        }
//       else
//        {
//            border = 2;
//        }

//        for (int j = 0; j < border; j++)
//        {
            scene->getModel(cur).setModelNum(i);
            cur++;
    }
}
