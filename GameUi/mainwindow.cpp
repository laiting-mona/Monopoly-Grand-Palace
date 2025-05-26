#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QFrame>
#include <QTime>
#include <QRandomGenerator>
#include <QtGlobal>
#include "DiceDialog.h"
#include <QStandardPaths>
#include <QFileInfo>
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , gameStarted(false)
    , canRollDice(false)
{
    ui->setupUi(this);

    // 建立 QGraphicsView 架構
    graphicsView = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    videoItem = new QGraphicsVideoItem();
    diceItem = new QGraphicsVideoItem();
    scene->addItem(videoItem);
    scene->addItem(diceItem);
    diceItem->setVisible(false);
    graphicsView->setScene(scene);
    graphicsView->setFrameShape(QFrame::NoFrame);
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

    // 影片播放器
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(videoItem);

    // 骰子播放器
    dicePlayer = new QMediaPlayer(this);
    dicePlayer->setVideoOutput(diceItem);
    connect(dicePlayer, &QMediaPlayer::mediaStatusChanged, this, &MainWindow::onDiceAnimationFinished);

    // 骰子點數標籤
    diceNumberLabel = new QLabel(graphicsView);
    diceNumberLabel->setStyleSheet("QLabel { background: rgba(0,0,0,0.7); color: white; font-size: 48px; border-radius: 20px; padding: 20px; }");
    diceNumberLabel->setAlignment(Qt::AlignCenter);
    diceNumberLabel->setFixedSize(200, 200);
    diceNumberLabel->setVisible(false);

    // 按鈕
    startButton = new QPushButton("開始遊戲", graphicsView);
    startButton->setStyleSheet("QPushButton { background: rgba(0,0,0,0.6); color: white; font-size: 20px; border-radius: 10px; padding: 10px 30px; }");
    startButton->setFixedWidth(200);
    startButton->setFixedHeight(50);
    startButton->raise();
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStartButtonClicked);

    // 主視窗 layout
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(graphicsView);

    QWidget *central = new QWidget(this);
    central->setLayout(mainLayout);
    setCentralWidget(central);

    // 設定影片來源
    QString resourcePath = ":/video/大富翁.mp4";
    QString fileName = QFileInfo(resourcePath).fileName();
    QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + fileName;
    if (!QFile::exists(tempPath)) {
        QFile::copy(resourcePath, tempPath);
    }
    if (QFile::exists(tempPath)) {
        mediaPlayer->setSource(QUrl::fromLocalFile(tempPath));
        mediaPlayer->play();
    } else {
        QMessageBox::warning(this, "警告", "找不到影片檔案！請確認路徑：" + tempPath);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (graphicsView && videoItem && scene && startButton) {
        QSizeF viewSize = graphicsView->viewport()->size();
        videoItem->setSize(viewSize);
        diceItem->setSize(viewSize);
        scene->setSceneRect(QRectF(QPointF(0, 0), viewSize));
        graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatioByExpanding);

        // 讓按鈕永遠在下方中央
        int btnW = startButton->width();
        int btnH = startButton->height();
        int x = (graphicsView->width() - btnW) / 2;
        int y = graphicsView->height() - btnH - 30;
        startButton->move(x, y);

        // 讓骰子點數標籤在中央
        int labelX = (graphicsView->width() - diceNumberLabel->width()) / 2;
        int labelY = (graphicsView->height() - diceNumberLabel->height()) / 2;
        diceNumberLabel->move(labelX, labelY);
    }
}

void MainWindow::onStartButtonClicked()
{
    gameStarted = true;
    canRollDice = true;
    startButton->setVisible(false);
    QMessageBox::information(this, "遊戲開始", "遊戲已開始！按 T 鍵擲骰子。");
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_T && gameStarted && canRollDice) {
        canRollDice = false;

        int dice1 = QRandomGenerator::global()->bounded(1, 7);
        int dice2 = QRandomGenerator::global()->bounded(1, 7);
        int minDice = qMin(dice1, dice2);
        int maxDice = qMax(dice1, dice2);
        QString diceFileName = QString("%1+%2.mp4").arg(minDice).arg(maxDice);
        QString resourcePath = QString(":/video/") + diceFileName;
        QString tempPath = QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/" + diceFileName;
        if (!QFile::exists(tempPath)) {
            QFile::copy(resourcePath, tempPath);
        }
        DiceDialog *dialog = new DiceDialog(tempPath, this);
        connect(dialog, &DiceDialog::videoFinished, this, [=](){
            int sum = dice1 + dice2;
            diceNumberLabel->setText(QString::number(sum));
            diceNumberLabel->setVisible(true);
            QTimer::singleShot(3000, [this]() {
                diceNumberLabel->setVisible(false);
                canRollDice = true;
            });
        });
        dialog->exec();
        dialog->deleteLater();
    }
}

void MainWindow::onDiceAnimationFinished(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::EndOfMedia) {
        diceItem->setVisible(false);
        
        // 取得剛剛儲存的點數
        int dice1 = diceNumberLabel->property("dice1").toInt();
        int dice2 = diceNumberLabel->property("dice2").toInt();
        diceNumberLabel->setText(QString::number(dice1) + " + " + QString::number(dice2));
        diceNumberLabel->setVisible(true);
        
        // 3秒後隱藏點數
        QTimer::singleShot(3000, [this]() {
            diceNumberLabel->setVisible(false);
            canRollDice = true;
        });
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mediaPlayer;
    delete dicePlayer;
    // 其他 Qt 會自動釋放
}
