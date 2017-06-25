#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QObject>
#include <QMediaPlayer>
#include <QWidget>
#include <QDebug>
#include <QEvent>
class MediaPlayer_1 : public QMediaPlayer
{
    Q_OBJECT
public:
    explicit MediaPlayer_1(QWidget *parent = 0);
    ~MediaPlayer_1();
//private slots:
//    void StateChangedSolt(QMediaPlayer::MediaStatus state);
};

#endif // MEDIAPLAYER_H
