#ifndef PLACECHOOSER_H
#define PLACECHOOSER_H

#include <QDialog>

namespace Ui
{
class PlaceBoardChooser;
class PlaceBedChooser;
class PlaceTableChooser;
class PlaceChairChooser;
class PlaceTorsherChooser;
class PlaceTvChooser;
}

class PlaceBoardChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceBoardChooser(QWidget *parent = nullptr);
    ~PlaceBoardChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();
    int getModelDirection();

    void setBoardHeight(int boardHeight_);
    int  getBoardHeight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceBoardChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 0;
    int modelHeight = 0;
    int modelDirection = 0;

    int boardHeight = 0;
};

class PlaceBedChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceBedChooser(QWidget *parent = nullptr);
    ~PlaceBedChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();
    int getModelDirection();

    void setBoardHeight(int boardHeight_);
    int  getBoardHeight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceBedChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 0;
    int modelHeight = 0;
    int modelDirection = 0;

    int boardHeight = 0;
};

class PlaceTableChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceTableChooser(QWidget *parent = nullptr);
    ~PlaceTableChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();
    int getModelDirection();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceTableChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 1;
    int modelHeight = 1;
    int modelDirection = 1;
};

class PlaceChairChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceChairChooser(QWidget *parent = nullptr);
    ~PlaceChairChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();
    int getModelDirection();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceChairChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 1;
    int modelHeight = 1;
    int modelDirection = 1;
};

class PlaceTorsherChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceTorsherChooser(QWidget *parent = nullptr);
    ~PlaceTorsherChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();

    void setBoardHeight(int boardHeight_);
    int  getBoardHeight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceTorsherChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 0;
    int modelHeight = 0;

    int boardHeight = 0;
};

class PlaceTvChooser : public QDialog
{
    Q_OBJECT

public:
    explicit PlaceTvChooser(QWidget *parent = nullptr);
    ~PlaceTvChooser();

    enum stat
    {
        CANCEL,
        OK
    };

    stat status;

    void setXCell(int xCell_);
    int  getXCell();

    void setYCell(int yCell_);
    int  getYCell();

    int getModelLength();
    int getModelHeight();
    int getModelDirection();

    void setBoardHeight(int boardHeight_);
    int  getBoardHeight();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::PlaceTvChooser *ui;

    int xCell = -1;
    int yCell = -1;

    int modelLength = 0;
    int modelHeight = 0;
    int modelDirection = 0;

    int boardHeight = 0;
};

#endif // PLACECHOOSER_H
