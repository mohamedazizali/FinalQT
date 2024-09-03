#include "eleve_am.h"
#include "ui_eleve_am.h"

eleve_am::eleve_am(MainWindow *mainWindow,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::eleve_am),
    win(mainWindow)
{
    ui->setupUi(this);

    ui->sexe->addItem("M");
    ui->sexe->addItem("F");



}

eleve_am::~eleve_am()
{
    delete ui;
}

void eleve_am::initInput(){
    if(mode==1){
        ui->matricule->setText(model->data(model->index(this->selected.row(),0)).toString());
        ui->nom->setText(model->data(model->index(this->selected.row(),1)).toString());
        ui->prenom->setText(model->data(model->index(this->selected.row(),2)).toString());
        ui->date->setDate(model->data(model->index(this->selected.row(),3)).toDate());
        ui->email->setText(model->data(model->index(this->selected.row(),4)).toString());
        ui->sexe->setCurrentText(model->data(model->index(this->selected.row(),5)).toString());
    }

}

int eleve_am::getMode() const
{
    return mode;
}

void eleve_am::setMode(int value)
{
    mode = value;
}

void eleve_am::on_buttonBox_accepted()
{
    Eleve E;


    E.setMatricule(ui->matricule->text());

    E.setNom(ui->nom->text());
    E.setPrenom(ui->prenom->text());
    E.setDateNaissance(ui->date->date());
    E.setEmail(ui->email->text());
    E.setSexe(ui->sexe->currentText());

    if(mode==0){


        bool a = E.ajouter();

        if(a){
            QMessageBox::information(nullptr, QObject::tr("success"),
                        QObject::tr("un nouveau eleve est ajoute"), QMessageBox::Cancel);
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("echec"),
                        QObject::tr("verifier les donnée entré"), QMessageBox::Cancel);
        }
    }

    else if(mode==1){

        bool a=E.modifier(model->data(model->index(this->selected.row(),0)).toString());

        if(a){
            QMessageBox::information(nullptr, QObject::tr("success"),
                        QObject::tr("un nouveau eleve est modifié"), QMessageBox::Cancel);
        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("echec"),
                        QObject::tr("verifier les donnée entré"), QMessageBox::Cancel);
        }
    }

    win->initialiser();

}

QAbstractItemModel *eleve_am::getModel() const
{
    return model;
}

void eleve_am::setModel(QAbstractItemModel *value)
{
    model = value;
}

QModelIndex eleve_am::getSelected() const
{
    return selected;
}

void eleve_am::setSelected(const QModelIndex &value)
{
    selected = value;
}


