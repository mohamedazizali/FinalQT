#include "formation.h"

Formation::Formation()
{
}

int Formation::getId() const
{
    return id;
}

void Formation::setId(int value)
{
    id = value;
}

QString Formation::getMatricule() const
{
    return matricule;
}

void Formation::setMatricule(const QString &value)
{
    matricule = value;
}

QString Formation::getTitre() const
{
    return titre;
}

void Formation::setTitre(const QString &value)
{
    titre = value;
}

QString Formation::getType() const
{
    return type;
}

void Formation::setType(const QString &value)
{
    type = value;
}

QDate Formation::getDate_act() const
{
    return date_act;
}

void Formation::setDate_act(const QDate &value)
{
    date_act = value;
}

int Formation::getArchive() const
{
    return archive;
}

void Formation::setArchive(int value)
{
    archive = value;
}

bool Formation::ajouter()
{
    QSqlQuery query;

    query.prepare("Insert Into FORMATION(MATRICULE,TITRE,TYPE,DATE_FORMATION,ARCHIVE) Values(:matricule,:titre,:type,:date,0);");
    query.bindValue(":matricule", this->matricule);
    query.bindValue(":titre", this->titre);
    query.bindValue(":type", this->type);
    query.bindValue(":date", this->date_act);

    return query.exec();
}

QSqlQueryModel *Formation::afficher(int archive)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE,TITRE,TYPE,DATE_FORMATION FROM FORMATION WHERE ARCHIVE=" + QString::number(archive) + ";");

    return modal;
}

bool Formation::modifier(QString matricule)
{
    QSqlQuery query;

    query.prepare("UPDATE formation SET MATRICULE = :matricule, TITRE = :titre, TYPE = :type, DATE_FORMATION = :date WHERE MATRICULE = :mat");
    query.bindValue(":matricule", this->matricule);
    query.bindValue(":titre", this->titre);
    query.bindValue(":type", this->type);
    query.bindValue(":date", this->date_act);
    query.bindValue(":mat", matricule);

    return query.exec();
}

bool Formation::supprimer(QString matricule)
{
    QSqlQuery query;

    query.prepare("DELETE FROM formation WHERE matricule=:matricule");
    query.bindValue(":matricule", matricule);

    return query.exec();
}

QBarSeries* Formation::statistique()
{
    QSqlQuery q1, q2, q3, q4;
    qreal tot = 0, c1 = 0, c2 = 0, c3 = 0;

    q1.prepare("SELECT * FROM formation");
    q1.exec();

    q2.prepare("SELECT * FROM formation WHERE type='sportif'");
    q2.exec();

    q3.prepare("SELECT * FROM formation WHERE type='artistique'");
    q3.exec();

    q4.prepare("SELECT * FROM formation WHERE type='cultural'");
    q4.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }
    while (q4.next()) { c3++; }

    c1 = c1 / tot;
    c2 = c2 / tot;
    c3 = c3 / tot;

    QBarSet *set0 = new QBarSet("sportif");
    QBarSet *set1 = new QBarSet("artistique");
    QBarSet *set2 = new QBarSet("cultural");

    *set0 << c1;
    *set1 << c2;
    *set2 << c3;

    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);

    return series;
}

QSqlQueryModel* Formation::tri(QString type, int archive)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE,TITRE,TYPE,DATE_FORMATION FROM formation WHERE ARCHIVE = " + QString::number(archive) + " ORDER BY " + type + ";");

    return modal;
}

QSqlQueryModel* Formation::rechercher(QString toSearch, QString type, int archive)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QString query;

    if (type == "titre") {
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_FORMATION FROM formation WHERE ARCHIVE=" + QString::number(archive) + " and titre LIKE '%" + toSearch + "%';";
    }
    else if (type == "type") {
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_FORMATION FROM formation WHERE ARCHIVE=" + QString::number(archive) + " and type LIKE '%" + toSearch + "%';";
    }
    else if (type == "matricule") {
        query = "SELECT MATRICULE,TITRE,TYPE,DATE_FORMATION FROM formation WHERE ARCHIVE=" + QString::number(archive) + " and matricule LIKE '%" + toSearch + "%';";
    }

    modal->setQuery(query);

    return modal;
}

void Formation::exporterCSV(QString fileName, QSqlQueryModel* model)
{
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        for (int column = 0; column < model->columnCount(); ++column) {
            stream << model->headerData(column, Qt::Horizontal).toString();
            if (column < model->columnCount() - 1)
                stream << ",";
        }
        stream << "\n";

        for (int row = 0; row < model->rowCount(); ++row) {
            for (int column = 0; column < model->columnCount(); ++column) {
                stream << model->data(model->index(row, column)).toString();
                if (column < model->columnCount() - 1)
                    stream << ",";
            }
            stream << "\n";
        }

        file.close();
    }
}

QStringList Formation::notification()
{
    QSqlQuery s;
    QStringList queryResultArray;

    s.prepare("select titre from formation WHERE TRUNC(date_formation) = TRUNC(SYSDATE)");
    if (s.exec()) {
        while (s.next()) {
            QString columnData = s.value(0).toString();
            queryResultArray.append(columnData);
        }
    }

    return queryResultArray;
}

bool Formation::archiver(QString matricule, int archive)
{
    QSqlQuery query;

    query.prepare("UPDATE formation SET ARCHIVE=" + QString::number(archive) + " WHERE MATRICULE = :mat");
    query.bindValue(":mat", matricule);

    return query.exec();
}
