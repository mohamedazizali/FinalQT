#ifndef ELEVE_AM_H
#define ELEVE_AM_H

#include <QDialog>

#include "eleve.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class eleve_am;
}

class eleve_am : public QDialog
{
    Q_OBJECT

public:
    explicit eleve_am(MainWindow *mainWindow,QWidget *parent = nullptr);
    ~eleve_am();

    int getMode() const;
    void setMode(int value);


    QModelIndex getSelected() const;
    void setSelected(const QModelIndex &value);

    QAbstractItemModel *getModel() const;
    void setModel(QAbstractItemModel *value);

    void initInput();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::eleve_am *ui;
    QModelIndex selected;
    QAbstractItemModel* model;


    MainWindow* win;
    int mode;
};

#endif // ELEVE_AM_H
