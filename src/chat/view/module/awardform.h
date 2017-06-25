#ifndef AWARDFORM_H
#define AWARDFORM_H

#include <QWidget>
#include <chat/control/define_1.h>
#include <QDir>
#include "shadowbridge.h"
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QMimeData>
#ifndef SUSPENDDLG_H
#include <chat/view/dlg/suspenddlg.h>
#endif // SUSPENDDLG_H
namespace Ui {
class AwardForm;
}

class AwardForm : public QWidget
{
    Q_OBJECT

public:
    explicit AwardForm(ShadowBridge *bridge,QWidget *parent = 0);
    ~AwardForm();

    bool sendCoins(QMap<QString ,QVariant>* coins);
private slots:

    void mySelectionChanged(QClipboard::Mode mode);

    void on_toolButton_2_clicked();

    void on_toolButton_clicked();

private:
    ShadowBridge *bridge;
    Ui::AwardForm *ui;
    QString payTo;
    QClipboard *clipboard;

};

#endif // AWARDFORM_H
