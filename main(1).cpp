#include "mainwindow.h"


#include <QApplication>
#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTimeEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>
#include <QProcess>
#include <QFile>
#include <QHeaderView>
#ifdef Q_OS_WIN
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#endif

struct Reminder {
    QDateTime time;
    QString message;
};

class ReminderScheduler : public QMainWindow {
    Q_OBJECT
public:
    ReminderScheduler(QWidget *parent = 0) : QMainWindow(parent) {
        setupUI();
        setupTrayIcon();
        checkTimer = new QTimer(this);
        connect(checkTimer, SIGNAL(timeout()), this, SLOT(checkReminders()));
        checkTimer->start(1000);
    }

private slots:
    void addReminder() {
        if(messageEdit->text().isEmpty()) {
            QMessageBox::warning(this, "错误", "请输入提醒内容");
            return;
        }

        Reminder newReminder;
        newReminder.time = timeEdit->dateTime();
        newReminder.message = messageEdit->text();

        if(newReminder.time <= QDateTime::currentDateTime()) {
            QMessageBox::warning(this, "错误", "请选择未来的时间");
            return;
        }

        reminders.append(newReminder);
        updateTable();
        messageEdit->clear();
    }

    void deleteReminder() {
        int row = table->currentRow();
        if(row >= 0 && row < reminders.size()) {
            reminders.removeAt(row);
            updateTable();
        }
    }

    void checkReminders() {
        QDateTime now = QDateTime::currentDateTime();
        for(int i = reminders.size()-1; i >= 0; --i) {
            if(reminders[i].time <= now) {
                showReminder(reminders[i]);
                reminders.removeAt(i);
                updateTable();
            }
        }
    }

private:
    void setupUI() {
        QWidget *centralWidget = new QWidget(this);
        QVBoxLayout *mainLayout = new QVBoxLayout;

        // 时间选择
        timeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addSecs(3600));
        timeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");

        // 内容输入
        messageEdit = new QLineEdit;
        messageEdit->setPlaceholderText("输入提醒内容");

        // 按钮
        QPushButton *addBtn = new QPushButton("添加提醒");
        QPushButton *delBtn = new QPushButton("删除选中");
        connect(addBtn, SIGNAL(clicked()), this, SLOT(addReminder()));
        connect(delBtn, SIGNAL(clicked()), this, SLOT(deleteReminder()));

        // 表格
        table = new QTableWidget(0, 2);
        table->setHorizontalHeaderLabels(QStringList() << "时间" << "内容");
        table->horizontalHeader()->setStretchLastSection(true);

        // 布局
        QHBoxLayout *inputLayout = new QHBoxLayout;
        inputLayout->addWidget(timeEdit);
        inputLayout->addWidget(messageEdit);
        inputLayout->addWidget(addBtn);

        mainLayout->addLayout(inputLayout);
        mainLayout->addWidget(table);
        mainLayout->addWidget(delBtn);

        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);
        resize(600, 400);
    }

    void setupTrayIcon() {
        trayIcon = new QSystemTrayIcon(QIcon("reminder.png"), this);
        QMenu *trayMenu = new QMenu;
        trayMenu->addAction("显示", this, SLOT(showNormal()));
        trayMenu->addAction("退出", qApp, SLOT(quit()));
        trayIcon->setContextMenu(trayMenu);
        trayIcon->show();
    }

    void updateTable() {
        table->setRowCount(reminders.size());
        for(int i = 0; i < reminders.size(); ++i) {
            table->setItem(i, 0, new QTableWidgetItem(reminders[i].time.toString("yyyy-MM-dd HH:mm")));
            table->setItem(i, 1, new QTableWidgetItem(reminders[i].message));
        }
    }

    void showReminder(const Reminder &reminder) {
        playAlertSound();
        QMessageBox::information(this, "提醒！",
            QString("时间：%1\n内容：%2").arg(reminder.time.toString()).arg(reminder.message));
    }

    void playAlertSound() {
        QString soundPath = "alert.wav";

        if(!QFile::exists(soundPath)) {
            QMessageBox::warning(this, "错误", "未找到提示音文件");
            return;
        }

        // Windows系统
        //#ifdef Q_OS_WIN
        //PlaySound(soundPath.toStdWString().c_str(), NULL, SND_FILENAME | SND_ASYNC);


        // 通用方案
        //#else
        //QProcess::startDetached("play", QStringList() << soundPath);
        //#endif
    }

private:
    QDateTimeEdit *timeEdit;
    QLineEdit *messageEdit;
    QTableWidget *table;
    QSystemTrayIcon *trayIcon;
    QTimer *checkTimer;
    QList<Reminder> reminders;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 设置界面风格兼容旧版本
    #if QT_VERSION < 0x050000
    QApplication::setStyle("plastique");
    #endif

    ReminderScheduler scheduler;
    scheduler.show();

    return app.exec();
}

#include "main.moc"
