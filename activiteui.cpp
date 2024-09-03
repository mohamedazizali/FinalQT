#include "activiteui.h"
#include "ui_activiteui.h"

ActiviteUI::ActiviteUI(MainWindow *mainWindow,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ActiviteUI),
    win(mainWindow)
{
    ui->setupUi(this);

    ui->type->addItem("sportif");
    ui->type->addItem("artistique");
    ui->type->addItem("cultural");
}

ActiviteUI::~ActiviteUI()
{
    delete ui;
}

void ActiviteUI::on_buttonBox_accepted()
{
    Activite A;

    A.setMatricule(ui->matricule->text());
    A.setTitre(ui->titre->text());
    A.setDate_act(ui->date->date());
    A.setType(ui->type->currentText());

    if(mode==0){
        A.ajouter();
    }

    else if(mode==1){
        A.modifier(model->data(model->index(this->selected.row(),0)).toString());
    }

    win->initialiser();
}

void ActiviteUI::initInput(){
    if(mode==1){
        ui->matricule->setText(model->data(model->index(this->selected.row(),0)).toString());
        ui->titre->setText(model->data(model->index(this->selected.row(),1)).toString());
        ui->type->setCurrentText(model->data(model->index(this->selected.row(),2)).toString());
        ui->date->setDate(model->data(model->index(this->selected.row(),3)).toDate());
    }

}

QAbstractItemModel *ActiviteUI::getModel() const
{
    return model;
}

void ActiviteUI::setModel(QAbstractItemModel *value)
{
    model = value;
}

QModelIndex ActiviteUI::getSelected() const
{
    return selected;
}

void ActiviteUI::setSelected(const QModelIndex &value)
{
    selected = value;
}

int ActiviteUI::getMode() const
{
    return mode;
}

void ActiviteUI::setMode(int value)
{
    mode = value;
}
