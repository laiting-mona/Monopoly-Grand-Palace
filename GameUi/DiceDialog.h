#pragma once
#include <QDialog>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QObject>
class DiceDialog : public QDialog {
    Q_OBJECT
public:
    explicit DiceDialog(const QString &videoPath, QWidget *parent = nullptr);
signals:
    void videoFinished();
private:
    QMediaPlayer *player;
    QVideoWidget *videoWidget;
}; 
