#ifndef SUSPENDDLG_H
#define SUSPENDDLG_H

#include <QDialog>
#include <chat/view/module/suspendform.h>
#ifndef AWARDFORM_H
#include <chat/view/module/awardform.h>
#endif // AWARDFORM_H
namespace Ui {
class SuspendDlg;
}

class SuspendDlg : public QDialog
{
    Q_OBJECT

public:
    explicit SuspendDlg(QMap<QString ,QVariant>* coins,QWidget *parent = 0);
    explicit SuspendDlg(ShadowBridge *bridge,QWidget *parent = 0);
    ~SuspendDlg();
    void init();
private:

    Ui::SuspendDlg *ui;
    QWidget* aform;
    bool m_Drag;
    QPoint m_DragPosition;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * evt);
    void mouseMoveEvent(QMouseEvent * evt);
private slots:
    void on_quitBtn_clicked();
void on_minBtn_clicked();
};

#endif // SUSPENDDLG_H
