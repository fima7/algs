#ifndef NEWDIALOG_H
#define NEWDIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include "perctype.h"

using namespace std;

namespace Ui {
class NewDialog;
}

class NewDialog : public QDialog
{
    Q_OBJECT

public:
    // enum UFType {UFQuickFind, UFQuickUnion, UFWQuickUnion, UFWCQuickUnion};
    explicit NewDialog(QWidget *parent = 0);
    ~NewDialog();

    int getSimSize();
    bool getSilent();
    list<UFType>& getList();


private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::NewDialog *ui;
    // UFType m_ufType;
    // int m_simCount;
    int m_simSize;
    bool m_silent;

    list<UFType> m_list;

};

#endif // NEWDIALOG_H
