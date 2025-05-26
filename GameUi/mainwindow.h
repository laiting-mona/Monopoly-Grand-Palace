#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QStackedLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QFrame>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onStartButtonClicked();
    void onDiceAnimationFinished(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    QMediaPlayer *dicePlayer;
    QVideoWidget *videoWidget;
    QPushButton *startButton;
    QWidget *videoContainer;
    QStackedLayout *stackedLayout;
    QGraphicsView *graphicsView;
    QGraphicsScene *scene;
    QGraphicsVideoItem *videoItem;
    QGraphicsVideoItem *diceItem;
    QLabel *diceNumberLabel;
    bool gameStarted;
    bool canRollDice;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H
