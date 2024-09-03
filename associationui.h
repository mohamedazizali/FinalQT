#ifndef ASSOCIATIONUI_H
#define ASSOCIATIONUI_H

#include <QDialog>
#include <QMessageBox>

#include "association.h"

namespace Ui {
class AssociationUI;
}

class AssociationUI : public QDialog
{
    Q_OBJECT

public:
    explicit AssociationUI(QWidget *parent = nullptr);
    ~AssociationUI();

    QString getMatricule() const;
    void setMatricule(const QString &value);

    void initialiser();

private slots:
    void on_pushButton_2_clicked();

    void on_inscrir_clicked();

private:
    Ui::AssociationUI *ui;

    Association As;

    QString matricule;
};

#endif // ASSOCIATIONUI_H
