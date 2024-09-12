#include "association.h"

Association::Association()
{
    // Constructor body (if needed)
}

int Association::getId_formateur() const
{
    return id_formateur;
}

void Association::setId_formateur(int value)
{
    id_formateur = value;
}

int Association::getId_formation() const
{
    return id_formation;
}

void Association::setId_formation(int value)
{
    id_formation = value;
}

bool Association::ajouter(QString matriculeFormateur, QString matriculeFormation)
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    // Fetch ID of the formation based on the matricule
    modal->setQuery("SELECT ID FROM formation WHERE Matricule='" + matriculeFormation + "';");
    int id_formation = modal->record(0).value("ID").toInt();

    // Fetch ID of the formateur based on the matricule
    modal->setQuery("SELECT ID FROM formateur WHERE Matricule='" + matriculeFormateur + "';");
    int id_formateur = modal->record(0).value("ID").toInt();

    QSqlQuery query;
    query.prepare("INSERT INTO association (ID_FORMATION, ID_FORMATEUR) VALUES (:formation, :formateur);");
    query.bindValue(":formation", id_formation);
    query.bindValue(":formateur", id_formateur);

    return query.exec();
}

bool Association::supprimer(QString matriculeFormateur, QString matriculeFormation)
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    // Fetch ID of the formation based on the matricule
    modal->setQuery("SELECT ID FROM formation WHERE Matricule='" + matriculeFormation + "';");
    int id_formation = modal->record(0).value("ID").toInt();

    // Fetch ID of the formateur based on the matricule
    modal->setQuery("SELECT ID FROM formateur WHERE Matricule='" + matriculeFormateur + "';");
    int id_formateur = modal->record(0).value("ID").toInt();

    QSqlQuery query;
    query.prepare("DELETE FROM association WHERE ID_FORMATEUR = :formateur AND ID_FORMATION = :formation");
    query.bindValue(":formateur", id_formateur);
    query.bindValue(":formation", id_formation);

    return query.exec();
}

QSqlQueryModel* Association::afficher_inscri(QString matriculeFormateur)
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    // Fetch ID of the formateur based on the matricule
    modal->setQuery("SELECT ID FROM formateur WHERE Matricule='" + matriculeFormateur + "';");
    QString id_formateur = modal->record(0).value("ID").toString();

    // Fetch formations where the formateur is already associated
    modal->setQuery("SELECT formation.MATRICULE, formation.TITRE, formation.TYPE, formation.DATE_FORMATION FROM formation "
                    "JOIN association ON association.ID_FORMATION = formation.ID "
                    "WHERE formation.ARCHIVE = 0 AND association.ID_FORMATEUR = " + id_formateur + ";");

    return modal;
}

QSqlQueryModel* Association::afficher_non_inscri(QString matriculeFormateur)
{
    QSqlQueryModel *modal = new QSqlQueryModel();

    // Fetch ID of the formateur based on the matricule
    modal->setQuery("SELECT ID FROM formateur WHERE Matricule='" + matriculeFormateur + "';");
    QString id_formateur = modal->record(0).value("ID").toString();

    // Fetch formations where the formateur is not associated
    modal->setQuery("SELECT formation.MATRICULE, formation.TITRE, formation.TYPE, formation.DATE_FORMATION FROM formation "
                    "LEFT JOIN association ON association.ID_FORMATION = formation.ID AND association.ID_FORMATEUR = " + id_formateur + " "
                    "WHERE association.ID_FORMATEUR IS NULL AND formation.ARCHIVE = 0;");

    return modal;
}
