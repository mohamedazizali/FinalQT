#ifndef FORMATEUR_H
#define FORMATEUR_H

#include <QString>
#include <QDate>
#include <QUrl>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>

#include <QDesktopServices>

#include <QFile>
#include <QTextStream>

QT_CHARTS_USE_NAMESPACE

class Formateur
{
private:

    int id;
    QString matricule;
    QString nom;
    QString prenom;
    QDate dateNaissance;
    QString email;
    QString sexe;

public:
    Formateur();

    int getId() const;
    void setId(int value);

    QString getNom() const;
    void setNom(const QString &value);

    QDate getDateNaissance() const;
    void setDateNaissance(const QDate &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getPrenom() const;
    void setPrenom(const QString &value);

    QString getMatricule() const;
    void setMatricule(const QString &value);

    QString getSexe() const;
    void setSexe(const QString &value);

    bool ajouter();
    bool modifier(QString matricule);
    QSqlQueryModel * afficher();
    bool supprimer(QString matricule);

    QSqlQueryModel* tri(QString type);
    QSqlQueryModel* rechercher(QString toSearch,QString type);
    QPieSeries* statistique();
    void exporterCSV(QString fileName,QSqlQueryModel* model);

    void mailling(QString nom,QString mail);
};

#endif // FORMATEUR_H
