#include "placechooser.h"
#include "ui_placeboardchooser.h"
#include "ui_placetablechooser.h"
#include "ui_placebedchooser.h"
#include "ui_placechairchooser.h"
#include "ui_placetorsherchooser.h"
#include "ui_placetvchooser.h"
//#include "ui_placeroadсhooser.h"
//#include "ui_placecarсhooser.h"

#include <QErrorMessage>
#include <QDebug>


PlaceBoardChooser::PlaceBoardChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceBoardChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения шкафа");
}

PlaceBoardChooser::~PlaceBoardChooser() { delete ui; }


void PlaceBoardChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceBoardChooser::getXCell() { return xCell; }

void PlaceBoardChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceBoardChooser::getYCell() { return yCell; }

int PlaceBoardChooser:: getModelLength() { return modelLength; }

int PlaceBoardChooser::getModelHeight() { return modelHeight; }


void PlaceBoardChooser::setBoardHeight(int boardHeight_) { boardHeight = boardHeight_; }

int PlaceBoardChooser::getBoardHeight() { return boardHeight; }

int PlaceBoardChooser::getModelDirection() { return modelDirection; }

//PlaceChooser::checkBox PlaceChooser::getDirection() { return direction; }

void PlaceBoardChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    gotText = ui->lineEdit_3->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelLength = gotText.toInt();

    gotText = ui->lineEdit_4->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelHeight = gotText.toInt();

    gotText = ui->lineEdit_5->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    boardHeight = gotText.toInt();

    gotText = this->ui->lineEdit_6->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelDirection = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else if (modelLength <= 0 || modelHeight <= 0 || boardHeight <=0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Размеры шкафа - целые положительные числа.");
        return;
    }
    else if (modelDirection <= 0 || modelDirection > 4)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Направление шкафа - целое положительное число от 1 до 4.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceBoardChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}





PlaceTableChooser::PlaceTableChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceTableChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения стола");
}

PlaceTableChooser::~PlaceTableChooser() { delete ui; }


void PlaceTableChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceTableChooser::getXCell() { return xCell; }

void PlaceTableChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceTableChooser::getYCell() { return yCell; }

int PlaceTableChooser:: getModelLength() { return modelLength; }

int PlaceTableChooser::getModelHeight() { return modelHeight; }


void PlaceTableChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceTableChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}
/////

PlaceChairChooser::PlaceChairChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceChairChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения стула");
}

PlaceChairChooser::~PlaceChairChooser() { delete ui; }


void PlaceChairChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceChairChooser::getXCell() { return xCell; }

void PlaceChairChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceChairChooser::getYCell() { return yCell; }

int PlaceChairChooser:: getModelLength() { return modelLength; }

int PlaceChairChooser::getModelHeight() { return modelHeight; }

int PlaceChairChooser::getModelDirection() { return modelDirection; }

void PlaceChairChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    gotText = this->ui->lineEdit_3->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelDirection = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else if (modelDirection <= 0 || modelDirection > 4)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Направление стула - целое положительное число от 1 до 4.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceChairChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}


PlaceBedChooser::PlaceBedChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceBedChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения кровати");
}

PlaceBedChooser::~PlaceBedChooser() { delete ui; }


void PlaceBedChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceBedChooser::getXCell() { return xCell; }

void PlaceBedChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceBedChooser::getYCell() { return yCell; }

int PlaceBedChooser:: getModelLength() { return modelLength; }

int PlaceBedChooser::getModelHeight() { return modelHeight; }

int PlaceBedChooser::getModelDirection() { return modelDirection; }


void PlaceBedChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    gotText = this->ui->lineEdit_3->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelDirection = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else if (modelDirection <= 0 || modelDirection > 4)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Направление кровати - целое положительное число от 1 до 4.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceBedChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}

PlaceTorsherChooser::PlaceTorsherChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceTorsherChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения торшера");
}

PlaceTorsherChooser::~PlaceTorsherChooser() { delete ui; }


void PlaceTorsherChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceTorsherChooser::getXCell() { return xCell; }

void PlaceTorsherChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceTorsherChooser::getYCell() { return yCell; }

int PlaceTorsherChooser:: getModelLength() { return modelLength; }

int PlaceTorsherChooser::getModelHeight() { return modelHeight; }

void PlaceTorsherChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceTorsherChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}

PlaceTvChooser::PlaceTvChooser(QWidget *parent) : QDialog(parent), ui(new Ui::PlaceTvChooser)
{
    ui->setupUi(this);
    this->setWindowTitle("Выбор расположения телевизора");
}

PlaceTvChooser::~PlaceTvChooser() { delete ui; }


void PlaceTvChooser::setXCell(int xCell_) { xCell = xCell_; }

int PlaceTvChooser::getXCell() { return xCell; }

void PlaceTvChooser::setYCell(int yCell_) { yCell = yCell_; }

int PlaceTvChooser::getYCell() { return yCell; }

int PlaceTvChooser:: getModelLength() { return modelLength; }

int PlaceTvChooser::getModelHeight() { return modelHeight; }


void PlaceTvChooser::setBoardHeight(int boardHeight_) { boardHeight = boardHeight_; }

int PlaceTvChooser::getBoardHeight() { return boardHeight; }

int PlaceTvChooser::getModelDirection() { return modelDirection; }

//PlaceChooser::checkBox PlaceChooser::getDirection() { return direction; }

void PlaceTvChooser::on_buttonBox_accepted()
{
    status = CANCEL;

    QString gotText = this->ui->lineEdit->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    xCell = gotText.toInt();

    gotText = this->ui->lineEdit_2->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    yCell = gotText.toInt();

    gotText = ui->lineEdit_3->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelLength = gotText.toInt();

    gotText = ui->lineEdit_4->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelHeight = gotText.toInt();

    gotText = ui->lineEdit_5->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    boardHeight = gotText.toInt();

    gotText = this->ui->lineEdit_6->text();
    if (gotText == "")
    {
        this->close();
        return;
    }
    modelDirection = gotText.toInt();

    if (xCell <= 0 || yCell <= 0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Номера ячеек - целые положительные числа.");
        return;
    }
    else if (modelLength <= 0 || modelHeight <= 0 || boardHeight <=0)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Размеры телевизора - целые положительные числа.");
        return;
    }
    else if (modelDirection <= 0 || modelDirection > 2)
    {
        this->close();
        QErrorMessage *err = new QErrorMessage();
        err->showMessage("Ошибка. Неверно введены данные.\n"
                         "Направление телевизора - целое положительное число от 1 до 2.");
        return;
    }
    else
        status = OK;

    this->close();
}

void PlaceTvChooser::on_buttonBox_rejected()
{
    status = CANCEL;
    this->close();
}
