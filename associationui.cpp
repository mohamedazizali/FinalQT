#include "associationui.h"
#include "ui_associationui.h"

AssociationUI::AssociationUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AssociationUI)
{
    ui->setupUi(this);
}

AssociationUI::~AssociationUI()
{
    delete ui;
}

void AssociationUI::initialiser(){


    ui->inscription->setModel(As.afficher_inscri(matricule));
    ui->desinscription->setModel(As.afficher_non_inscri(matricule));
}

QString AssociationUI::getMatricule() const
{
    return matricule;
}

void AssociationUI::setMatricule(const QString &value)
{
    matricule = value;
}

void AssociationUI::on_pushButton_2_clicked()
{
    QAbstractItemModel *model  = ui->inscription->model();

    QModelIndexList selected_indexes = ui->inscription->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        QString matricule_activite = model->data(model->index(selected_index.row(),0)).toString();

        As.supprimer(matricule,matricule_activite);

        this->initialiser();

     }
}

void AssociationUI::on_inscrir_clicked()
{
    QAbstractItemModel *model  = ui->desinscription->model();

    QModelIndexList selected_indexes = ui->desinscription->selectionModel()->selectedRows();


     if (selected_indexes.isEmpty()) {
        QMessageBox::critical(nullptr, QObject::tr("error"),
                   QObject::tr("selectionné un element de la list"), QMessageBox::Cancel);
     }
     else{

        QModelIndex selected_index = selected_indexes.at(0);

        QString matricule_activite = model->data(model->index(selected_index.row(),0)).toString();

        As.ajouter(matricule,matricule_activite);

        this->initialiser();
     }
}
