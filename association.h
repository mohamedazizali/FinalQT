#ifndef ASSOCIATION_H
#define ASSOCIATION_H

#include <QString>

#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlRecord>

#include <QDebug>

class Association
{
public:
    Association();

    int getId_formateur() const;
    void setId_formateur(int value);

    int getId_formation() const;
    void setId_formation(int value);

    bool ajouter(QString matriculeFormateur, QString matriculeFormation);
    QSqlQueryModel* afficher_inscri(QString matriculeFormateur);
    QSqlQueryModel* afficher_non_inscri(QString matriculeFormateur);
    bool supprimer(QString matriculeFormateur, QString matriculeFormation);

private:
    int id_formateur;
    int id_formation;
};

#endif // ASSOCIATION_H
