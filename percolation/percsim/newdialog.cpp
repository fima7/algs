#include "newdialog.h"
#include "ui_newdialog.h"
#include <QDebug>

using namespace std;

NewDialog::NewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewDialog)
{
    ui->setupUi(this);
}

NewDialog::~NewDialog()
{
    delete ui;
}

void NewDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    qDebug() << "Clicked";
}

list<UFType>& NewDialog::getList()
{
    return m_list;
}

void NewDialog::on_buttonBox_accepted()
{
    qDebug() << "Accepted";

    for (int i = 0; i < ui->spinBoxSimCount->value(); i++) {

        if (ui->quickFindBox->isChecked() == true ) {
            m_list.push_back(ufTypeQuickFind);
            // qDebug() << "ufTypeQuickFind";
        }

        if (ui->quickUnionBox->isChecked() == true ) {
            m_list.push_back(ufTypeQuickUnion);
            // qDebug() << "ufTypeQuickUnion";
        }

        if (ui->wquickUnionBox->isChecked() == true ) {
            m_list.push_back(ufTypeWQuickUnion);
            // qDebug() << "ufTypeWQuickUnion";
        }

        if (ui->cquickUnionBox->isChecked() == true){
            m_list.push_back(ufTypeCQuickUnion);
            // qDebug() << "ufTypeCQuickUnion";
        }

        if (ui->wcquickUnionBox->isChecked() == true) {
            m_list.push_back(ufTypeWCQuickUnion);
            // qDebug() << "ufTypeWCQuickUnion";
        }
    }

    if (ui->silentBox->isChecked() == true)
        m_silent = true;
    else
        m_silent = false;

    m_simSize = ui->spinBoxSimSize->value();
    // ui->spinBoxSimSize->setValue(m_simSize);
}

void NewDialog::on_buttonBox_rejected()
{
    qDebug() << "Rejected";
}

bool NewDialog::getSilent()
{
    return m_silent;
}

int NewDialog::getSimSize()
{
    return m_simSize;
}
