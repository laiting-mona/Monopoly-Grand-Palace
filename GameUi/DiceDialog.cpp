#include "DiceDialog.h"
#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>

DiceDialog::DiceDialog(const QString &videoPath, QWidget *parent)
    : QDialog(parent)
{
    setWindowFlags(windowFlags() | Qt::FramelessWindowHint);
    setModal(true);
    resize(600, 400);

    videoWidget = new QVideoWidget(this);
    player = new QMediaPlayer(this);
    player->setVideoOutput(videoWidget);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(videoWidget);
    setLayout(layout);

    connect(player, &QMediaPlayer::mediaStatusChanged, this, [this](QMediaPlayer::MediaStatus status){
        if (status == QMediaPlayer::EndOfMedia) {
            emit videoFinished();
            this->accept();
        }
    });

    if (QFile::exists(videoPath)) {
        player->setSource(QUrl::fromLocalFile(videoPath));
        player->play();
    } else {
        QMessageBox::warning(this, "錯誤", "找不到骰子動畫檔案！");
        this->accept();
    }
}
