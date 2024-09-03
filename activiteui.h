#ifndef ACTIVITEUI_H
#define ACTIVITEUI_H

#include <QDialog>

#include "Formation.h"
#include "mainwindow.h"

class MainWindow;

namespace Ui {
class ActiviteUI;
}

class ActiviteUI : public QDialog
{
    Q_OBJECT

public:
    explicit ActiviteUI(MainWindow *mainWindow,QWidget *parent = nullptr);
    ~ActiviteUI();

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
    Ui::ActiviteUI *ui;

    QModelIndex selected;
    QAbstractItemModel* model;

    MainWindow* win;


    int mode;
};

#endif // ACTIVITEUI_H
