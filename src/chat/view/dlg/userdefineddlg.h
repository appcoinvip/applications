#ifndef USERDEFINEDDLG_H
#define USERDEFINEDDLG_H

#include <QDialog>
#include <chat/view/module/browserform.h>
#include <chat/view/module/widget.h>
#include <QPoint>
namespace Ui {
class UserDefinedDlg;
}

class UserDefinedDlg : public QDialog
{
    Q_OBJECT

public:
    //    static UserDefinedDlg* getInstance(QString username ,
    //                                       QString usrInfoStr,
    //                                       QWidget *parent = 0 )
    //    {
    //        if(uDlg == NULL)  //判断是否第一次调用
    //            uDlg = new UserDefinedDlg(username ,usrInfoStr,parent );
    //        return uDlg;
    //    }
    //    static UserDefinedDlg *uDlg;
    explicit UserDefinedDlg(QWidget *parent);
    explicit UserDefinedDlg(QString username ,
                            QString usrInfoStr,
                            QWidget *parent = 0);
    explicit UserDefinedDlg(ShadowBridge *bridge,QWidget *parent = 0);
    ~UserDefinedDlg();

private:
    void Init();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent * evt);
    void mouseMoveEvent(QMouseEvent * evt);
private slots:

    void on_minBtn_clicked();

    void on_maxBtn_clicked();

    void on_quitBtn_clicked();

private:
    Ui::UserDefinedDlg *ui;
    bool m_Drag;
    QPoint m_DragPosition;
    QWidget *widg;
};

#endif // USERDEFINEDDLG_H
