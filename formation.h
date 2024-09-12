#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QDate>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>

#include <QFile>
#include <QTextStream>

QT_CHARTS_USE_NAMESPACE

class Formation
{
public:
    Formation();

    int getId() const;
    void setId(int value);

    QString getMatricule() const;
    void setMatricule(const QString &value);

    QString getTitre() const;
    void setTitre(const QString &value);

    QString getType() const;
    void setType(const QString &value);

    QDate getDate_act() const;
    void setDate_act(const QDate &value);

    int getArchive() const;
    void setArchive(int value);

    bool ajouter();
    bool modifier(QString matricule);
    QSqlQueryModel * afficher(int archive);
    bool supprimer(QString matricule);

    QSqlQueryModel* tri(QString type, int archive);
    QSqlQueryModel* rechercher(QString toSearch, QString type, int archive);
    QBarSeries* statistique();
    void exporterCSV(QString fileName, QSqlQueryModel* model);

    QStringList notification();
    bool archiver(QString matricule, int archive);

private:
    int id;
    QString matricule;
    QString titre;
    QString type;
    QDate date_act;
    int archive;
};

#endif // FORMATION_H
