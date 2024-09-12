#include "formateur.h"

int Formateur::getId() const
{
    return id;
}

void Formateur::setId(int value)
{
    id = value;
}

QString Formateur::getNom() const
{
    return nom;
}

void Formateur::setNom(const QString &value)
{
    nom = value;
}

QDate Formateur::getDateNaissance() const
{
    return dateNaissance;
}

void Formateur::setDateNaissance(const QDate &value)
{
    dateNaissance = value;
}

QString Formateur::getEmail() const
{
    return email;
}

void Formateur::setEmail(const QString &value)
{
    email = value;
}

QString Formateur::getPrenom() const
{
    return prenom;
}

void Formateur::setPrenom(const QString &value)
{
    prenom = value;
}

QString Formateur::getMatricule() const
{
    return matricule;
}

void Formateur::setMatricule(const QString &value)
{
    matricule = value;
}

QString Formateur::getSexe() const
{
    return sexe;
}

void Formateur::setSexe(const QString &value)
{
    sexe = value;
}

Formateur::Formateur()
{
    // Constructor implementation
}

bool Formateur::ajouter()
{
    int atCount = email.count('@');
    if (atCount != 1) {
        return false;
    }

    int atIndex = email.indexOf('@');
    QString username = email.left(atIndex);
    QString domain = email.mid(atIndex + 1);

    if (username.isEmpty() || domain.isEmpty()) {
        return false;
    }

    if (domain.indexOf('.') == -1) {
        return false;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO FORMATEUR(MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL, SEXE) "
                  "VALUES(:matricule, :nom, :prenom, :date, :email, :sexe);");
    query.bindValue(":matricule", this->matricule);
    query.bindValue(":nom", this->nom);
    query.bindValue(":prenom", this->prenom);
    query.bindValue(":date", this->dateNaissance);
    query.bindValue(":email", this->email);
    query.bindValue(":sexe", this->sexe);

    return query.exec();
}

QSqlQueryModel * Formateur::afficher()
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL, SEXE FROM FORMATEUR");

    return modal;
}

bool Formateur::supprimer(QString matricule)
{
    QSqlQuery query;

    query.prepare("DELETE FROM FORMATEUR WHERE MATRICULE = :matricule");
    query.bindValue(":matricule", matricule);

    return query.exec();
}

bool Formateur::modifier(QString matricule)
{
    int atCount = email.count('@');
    if (atCount != 1) {
        return false;
    }

    int atIndex = email.indexOf('@');
    QString username = email.left(atIndex);
    QString domain = email.mid(atIndex + 1);

    if (username.isEmpty() || domain.isEmpty()) {
        return false;
    }

    if (domain.indexOf('.') == -1) {
        return false;
    }

    QSqlQuery query;

    query.prepare("UPDATE FORMATEUR SET "
                  "MATRICULE = :matricule, NOM = :nom, PRENOM = :prenom, "
                  "DATE_NAISSANCE = :date, EMAIL = :email, SEXE = :sexe "
                  "WHERE MATRICULE = :mat");
    query.bindValue(":matricule", this->matricule);
    query.bindValue(":nom", this->nom);
    query.bindValue(":prenom", this->prenom);
    query.bindValue(":date", this->dateNaissance);
    query.bindValue(":email", this->email);
    query.bindValue(":sexe", this->sexe);
    query.bindValue(":mat", matricule);

    return query.exec();
}

QSqlQueryModel* Formateur::rechercher(QString toSearch, QString type)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    QString query;

    if (type == "nom") {
        query = "SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL FROM FORMATEUR WHERE NOM LIKE '%" + toSearch + "%'";
    } else if (type == "prenom") {
        query = "SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL FROM FORMATEUR WHERE PRENOM LIKE '%" + toSearch + "%'";
    } else if (type == "email") {
        query = "SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL FROM FORMATEUR WHERE EMAIL LIKE '%" + toSearch + "%'";
    } else if (type == "matricule") {
        query = "SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL FROM FORMATEUR WHERE MATRICULE LIKE '%" + toSearch + "%'";
    }

    modal->setQuery(query);

    return modal;
}

QPieSeries* Formateur::statistique()
{
    QSqlQuery q1, q2, q3;
    qreal tot = 0, c1 = 0, c2 = 0;

    q1.prepare("SELECT * FROM FORMATEUR");
    q1.exec();

    q2.prepare("SELECT * FROM FORMATEUR WHERE SEXE = 'M'");
    q2.exec();

    q3.prepare("SELECT * FROM FORMATEUR WHERE SEXE = 'F'");
    q3.exec();

    while (q1.next()) { tot++; }
    while (q2.next()) { c1++; }
    while (q3.next()) { c2++; }

    c1 = c1 / tot;
    c2 = c2 / tot;

    QPieSeries *series = new QPieSeries();
    series->append("Garçon", c1);
    series->append("Fille", c2);

    return series;
}

QSqlQueryModel* Formateur::tri(QString type)
{
    QSqlQueryModel *modal = new QSqlQueryModel();
    modal->setQuery("SELECT MATRICULE, NOM, PRENOM, DATE_NAISSANCE, EMAIL FROM FORMATEUR ORDER BY " + type);

    return modal;
}

void Formateur::exporterCSV(QString fileName, QSqlQueryModel* model)
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

void Formateur::mailling(QString nom, QString mail)
{
    QString link = "https://mail.google.com/mail/?view=cm&ui=2&tf=0&fs=1&to=" + mail + "&body=Bonjour " + nom + "%0aCordialement";
    QDesktopServices::openUrl(QUrl(link));
}
