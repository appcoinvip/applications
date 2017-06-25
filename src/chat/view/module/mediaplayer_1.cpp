#include "mediaplayer_1.h"

MediaPlayer_1::MediaPlayer_1(QWidget *parent) :
    QMediaPlayer(parent)
{
//    connect(this, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(StateChangedSolt(QMediaPlayer::MediaStatus)));
}

MediaPlayer_1::~MediaPlayer_1()
{
//    disconnect(this, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),0,0);
}

//void MediaPlayer_1::StateChangedSolt(QMediaPlayer::MediaStatus state){
//    if(state == QMediaPlayer::EndOfMedia && isAudioAvailable()){
//        play();
//    }
//}
