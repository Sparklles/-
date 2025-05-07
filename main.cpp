#include "Data_analysis_display.h"
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QTabWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QDate>
#include <QRandomGenerator>
#include <QWidget>
#include <QTabWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QTableView>
#include <QSqlTableModel>
#include <QHeaderView>
#include <QMessageBox>
#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDateEdit>
#include <QDialogButtonBox>
#include <QStackedWidget>

#include <QMainWindow>
#include <QDateTime>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QTreeWidget>
#include <QDialog>
#include<QDateTimeEdit>

#include <QApplication>
#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTreeWidget>
#include <QTimer>
#include <QDateTime>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include<QGraphicsDropShadowEffect>
#include <QFormLayout>

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QDateTimeEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QPushButton>
#include <QFormLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVariant>
#include<QFileDialog>
#include <QDir>
#include <QDialog>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QPushButton>
#include <QFileDialog>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDir>
#include <QDebug>
#include<QColorDialog>
#include <QList>

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
QT_CHARTS_USE_NAMESPACE
#include "C:\Users\Administrator\Desktop\SQLtest\EventManagement/EventManager.h"
#include "C:\Users\Administrator\Desktop\SQLtest\EventManagement/EventDialog.h"
#include "C:\Users\Administrator\Desktop\SQLtest\EventManagement/EventDetailDialog.h"
#include "C:\Users\Administrator\Desktop\SQLtest\EventManagement/EventStorageInterface.h"
// AnalysisReportWidget：报表分析组件，展示任务完成情况与事件类别统计
class AnalysisReportWidget : public QWidget {
    Q_OBJECT
public:
    AnalysisReportWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        updateCharts();
    }

private:
    // 图表视图
    QChartView *taskPieChartView;   // 用于任务完成率饼图
    QChartView *taskBarChartView;   // 用于任务统计的柱状图（按时间聚合）
    QChartView *eventBarChartView;  // 用于事件统计的柱状图（按时间聚合）

    // 控件
    QPushButton *refreshButton;    // 刷新按钮
    QComboBox *periodComboBox;     // 时间粒度选择：日、周、月、年

    // 初始化界面布局
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 第一部分：时间粒度选择
        QHBoxLayout *topLayout = new QHBoxLayout();
        QLabel *periodLabel = new QLabel("时间粒度:", this);
        periodComboBox = new QComboBox(this);
        periodComboBox->addItem("日");
        periodComboBox->addItem("周");
        periodComboBox->addItem("月");
        periodComboBox->addItem("年");
        topLayout->addWidget(periodLabel);
        topLayout->addWidget(periodComboBox);
        topLayout->addStretch();

        // 第二部分：图表区域
        // 左侧显示饼图：任务整体完成率
        taskPieChartView = new QChartView(new QChart(), this);
        // 右侧显示柱状图：任务、事件按时间统计
        taskBarChartView = new QChartView(new QChart(), this);
        eventBarChartView = new QChartView(new QChart(), this);

        // 组合图表区域，采用垂直布局
        QVBoxLayout *chartLayout = new QVBoxLayout();
        chartLayout->addWidget(new QLabel("任务完成率", this));
        chartLayout->addWidget(taskPieChartView);
        chartLayout->addWidget(new QLabel("任务统计（按时间）", this));
        chartLayout->addWidget(taskBarChartView);
        chartLayout->addWidget(new QLabel("事件统计（按时间）", this));
        chartLayout->addWidget(eventBarChartView);

        // 第三部分：刷新按钮
        refreshButton = new QPushButton("刷新数据", this);

        // 整体布局组合
        mainLayout->addLayout(topLayout);
        mainLayout->addLayout(chartLayout);
        mainLayout->addWidget(refreshButton);
        setLayout(mainLayout);

        // 信号槽：当用户改变时间粒度或点击刷新按钮时更新图表
        connect(refreshButton, &QPushButton::clicked, this, &AnalysisReportWidget::updateCharts);
        connect(periodComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
                this, &AnalysisReportWidget::updateCharts);


        //-----------------------------------------------------------
        refreshButton->setStyleSheet(R"(
                QPushButton {
                    background-color: #2980b9;
                    color: #ffffff;
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                    padding: 8px 20px;
                    font-size: 16px;
                }

                QPushButton:hover {
                    background-color: #3498db;
                    border: 2px solid #1a5276;
                }

                QPushButton:pressed {
                    background-color: #1f618d;
                    padding: 9px 19px;
                }
        )");

        //-----------------------------------------------------------
    }

    // 更新所有图表
    void updateCharts() {
        updateTaskPieChart();   // 任务完成率饼图
        updateTaskBarChart();   // 任务统计柱状图（按时间聚合）
        updateEventBarChart();  // 事件统计柱状图（按时间聚合）
    }

    // ----------------------------
    // 1. 任务完成率饼图
    // ----------------------------
    void updateTaskPieChart() {
        QSqlQuery query;
        int completed = 0;
        int total = 0;
        // 查询任务已完成和总数（采用 ToDoTasks 表，IsCompleted 为 1 表示完成）
        if(query.exec("SELECT COALESCE(SUM(CASE WHEN IsCompleted = 1 THEN 1 ELSE 0 END),0) AS Completed, "
                      "COALESCE(COUNT(*),0) AS Total FROM ToDoTasks")) {
            if(query.next()){
                completed = query.value("Completed").toInt();
                total = query.value("Total").toInt();
            }
        } else {
            qDebug() << "查询任务数据错误:" << query.lastError().text();
        }
        int incomplete = total - completed;

        // 计算百分比（防止除以0）
        double percentCompleted = (total > 0) ? (static_cast<double>(completed) / total * 100.0) : 0;
        double percentIncomplete = (total > 0) ? (static_cast<double>(incomplete) / total * 100.0) : 0;

        // 构造饼图数据系列，并设置标签显示任务数与占比
        QPieSeries *series = new QPieSeries();
        series->append(QString("已完成: %1 (%2%)").arg(completed).arg(percentCompleted, 0, 'f', 1), completed);
        series->append(QString("未完成: %1 (%2%)").arg(incomplete).arg(percentIncomplete, 0, 'f', 1), incomplete);
        for(auto slice : series->slices()){
            slice->setLabelVisible();
        }

        // 更新图表
        QChart *chart = taskPieChartView->chart();
        chart->removeAllSeries();
        chart->addSeries(series);
        chart->setTitle(QString("任务完成率（总任务数: %1）").arg(total));
        chart->legend()->setAlignment(Qt::AlignRight);
        taskPieChartView->setRenderHint(QPainter::Antialiasing);
    }

    // ----------------------------
    // 2. 按时间统计任务的柱状图（展示每个时间段中已完成与未完成任务数）
    // ----------------------------
    void updateTaskBarChart() {
        // 根据选择的时间粒度生成不同的日期格式表达式（以任务创建时间为统计依据）
        QString period = periodComboBox->currentText();
        QString dateFormat;
        if (period == "日") {
            dateFormat = "CONVERT(VARCHAR(10), CreatedAt, 120)";
        } else if (period == "周") {
            dateFormat = "CAST(YEAR(CreatedAt) AS VARCHAR(4)) + '-W' + CAST(DATEPART(WEEK, CreatedAt) AS VARCHAR(2))";
        } else if (period == "月") {
            dateFormat = "CONVERT(VARCHAR(7), CreatedAt, 120)";
        } else if (period == "年") {
            dateFormat = "CAST(YEAR(CreatedAt) AS VARCHAR(4))";
        }

        // 构造查询：按时间段统计任务已完成数量及总数（后续计算未完成数）
        QSqlQuery query;
        QString sql = QString("SELECT %1 AS period, "
                              "SUM(CASE WHEN IsCompleted = 1 THEN 1 ELSE 0 END) AS Completed, "
                              "COUNT(*) AS Total "
                              "FROM ToDoTasks "
                              "GROUP BY %1 "
                              "ORDER BY period")
                              .arg(dateFormat);
        QMap<QString, int> periodCompleted;
        QMap<QString, int> periodTotal;
        if(query.exec(sql)) {
            while(query.next()){
                QString pLabel = query.value("period").toString();
                int comp = query.value("Completed").toInt();
                int tot = query.value("Total").toInt();
                periodCompleted[pLabel] = comp;
                periodTotal[pLabel] = tot;
            }
        } else {
            qDebug() << "查询任务数据错误:" << query.lastError().text();
        }

        // 构造柱状图数据系列：两个 BarSet 分别表示已完成与未完成任务数
        QBarSeries *series = new QBarSeries();
        QBarSet *completedSet = new QBarSet("已完成");
        QBarSet *incompletedSet = new QBarSet("未完成");

        QStringList categories;
        QList<QString> periods = periodCompleted.keys();
        std::sort(periods.begin(), periods.end());
        for (const QString &p : periods) {
            int comp = periodCompleted.value(p);
            int tot = periodTotal.value(p);
            int incomp = tot - comp;
            *completedSet << comp;
            *incompletedSet << incomp;
            categories << p;
        }
        series->append(completedSet);
        series->append(incompletedSet);

        // 构造图表
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle(QString("任务统计（按%1）").arg(period));
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // 设置 X 轴为时间段标签
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->createDefaultAxes();
        chart->setAxisX(axisX, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        taskBarChartView->setChart(chart);
        taskBarChartView->setRenderHint(QPainter::Antialiasing);
    }

    // ----------------------------
    // 3. 按时间统计事件的柱状图（展示每个时间段中各类别事件数量）
    // ----------------------------
    void updateEventBarChart() {
        // 根据选择的时间粒度生成对应的日期格式表达式（以事件发生时间为统计依据）
        QString period = periodComboBox->currentText();
        QString dateFormat;
        if (period == "日") {
            dateFormat = "CONVERT(VARCHAR(10), EventDate, 120)";
        } else if (period == "周") {
            dateFormat = "CAST(YEAR(EventDate) AS VARCHAR(4)) + '-W' + CAST(DATEPART(WEEK, EventDate) AS VARCHAR(2))";
        } else if (period == "月") {
            dateFormat = "CONVERT(VARCHAR(7), EventDate, 120)";
        } else if (period == "年") {
            dateFormat = "CAST(YEAR(EventDate) AS VARCHAR(4))";
        }

        // 查询：按时间段和事件类别统计事件数
        QSqlQuery query;
        QString sql = QString("SELECT %1 AS period, Category, COUNT(*) AS Count "
                              "FROM UserEvents "
                              "GROUP BY %1, Category "
                              "ORDER BY period")
                              .arg(dateFormat);
        // 嵌套 map：外层 key 为时间段，内层 key 为事件类别，值为数量
        QMap<QString, QMap<QString, int>> data;
        if(query.exec(sql)) {
            while(query.next()){
                QString pLabel = query.value("period").toString();
                QString category = query.value("Category").toString();
                int count = query.value("Count").toInt();
                data[pLabel][category] = count;
            }
        } else {
            qDebug() << "查询事件数据错误:" << query.lastError().text();
        }

        // 收集所有出现的类别（保证各时间段中系列一致）
        QSet<QString> allCategories;
        for(auto &catMap : data){
            for(auto category : catMap.keys()){
                allCategories.insert(category);
            }
        }
        QStringList categories = allCategories.values();
        categories.sort();

        // 对每个类别创建一个 BarSet
        QMap<QString, QBarSet*> categoryBarSets;
        for (const QString &cat : categories) {
            categoryBarSets[cat] = new QBarSet(cat);
        }

        // 获取所有时间段，并对每段添加对应各类别数据（没有数据时填0）
        QList<QString> periods = data.keys();
        std::sort(periods.begin(), periods.end());
        QStringList axisCategories;
        for (const QString &p : periods) {
            axisCategories << p;
            QMap<QString, int> catMap = data.value(p);
            for (const QString &cat : categories) {
                int value = catMap.value(cat, 0);
                categoryBarSets[cat]->append(value);
            }
        }

        // 构造柱状图系列，将所有 BarSet 加入
        QBarSeries *series = new QBarSeries();
        for (const QString &cat : categories) {
            series->append(categoryBarSets[cat]);
        }

        // 构造图表
        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setTitle(QString("事件统计（按%1）").arg(period));
        chart->setAnimationOptions(QChart::SeriesAnimations);

        // 设置 X 轴为时间段标签
        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(axisCategories);
        chart->createDefaultAxes();
        chart->setAxisX(axisX, series);

        chart->legend()->setVisible(true);
        chart->legend()->setAlignment(Qt::AlignBottom);

        eventBarChartView->setChart(chart);
        eventBarChartView->setRenderHint(QPainter::Antialiasing);
    }
};

//------------------------------------------------------------------------------
// ReportNotesWidget：实现心得笔记的增删改查以及详细信息查看
//------------------------------------------------------------------------------
class ReportNotesWidget : public QWidget {
    Q_OBJECT
public:
    ReportNotesWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        loadNotes();
    }

private:
    QTableView *notesView;           // 列表显示记录（使用 QSqlTableModel）
    QSqlTableModel *notesModel;
    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *deleteButton;
    QTextEdit *detailText;           // 详细信息显示区

    // 初始化界面：包含列表、按钮区及详细内容显示区
    void setupUI() {
        QVBoxLayout *layout = new QVBoxLayout(this);

        // 创建列表视图及模型
        notesView = new QTableView(this);
        notesModel = new QSqlTableModel(this);
        notesModel->setTable("ReportNotes");
        // 设置手动提交编辑（这里主要通过对话框修改）
        notesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
        notesModel->select();

        // 设置表格显示：选择行为为整行选择，单选
        notesView->setModel(notesModel);
        notesView->setSelectionBehavior(QAbstractItemView::SelectRows);
        notesView->setSelectionMode(QAbstractItemView::SingleSelection);
        notesView->horizontalHeader()->setStretchLastSection(true);

        // 这里可根据需要隐藏不显示的列（比如自动增长的 NoteID）
        notesView->hideColumn(notesModel->fieldIndex("NoteID"));
        // 可选择显示部分字段，例如只显示 ReportType、ReportDate、CreatedAt 等
        // 根据情况也可以添加对 NoteContent 的摘要显示

        // 连接点击事件：点击表中某一行时显示详细信息
        connect(notesView, &QTableView::clicked, this, &ReportNotesWidget::onNoteSelected);

        // 操作按钮：新增、编辑和删除
        QHBoxLayout *buttonsLayout = new QHBoxLayout;
        addButton = new QPushButton("新增", this);
        editButton = new QPushButton("编辑", this);
        deleteButton = new QPushButton("删除", this);


        connect(addButton, &QPushButton::clicked, this, &ReportNotesWidget::addNote);
        connect(editButton, &QPushButton::clicked, this, &ReportNotesWidget::editNote);
        connect(deleteButton, &QPushButton::clicked, this, &ReportNotesWidget::deleteNote);
        buttonsLayout->addWidget(addButton);
        buttonsLayout->addWidget(editButton);
        buttonsLayout->addWidget(deleteButton);

        // 详细信息显示区，用于查看完整的笔记内容，设置只读并使用不同背景色区分
        detailText = new QTextEdit(this);
        detailText->setReadOnly(true);
        //detailText->setStyleSheet("background-color: #000000;");


        // 将各区域添加到整体布局中
        layout->addWidget(notesView);
        layout->addLayout(buttonsLayout);
        layout->addWidget(new QLabel("详情:", this));
        layout->addWidget(detailText);
        setLayout(layout);


        //样式表设计
        //----------------------------------------------------------

        /*                QPushButton {
                    background-color: #2980b9;
                    color: #ffffff;
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                }

                QPushButton:hover {
                    background-color: #3498db;
                    border: 2px solid #1a5276;
                }

                QPushButton:pressed {
                    background-color: #1f618d;

                }*/

        setStyleSheet(R"(
                QTextEdit {
                background-color: #d0e0f0;
                border: 1px solid #b0c4de;
                border-radius: 3px;
                padding: 5px;
                }
        )");
        //-----------------------------------------------------------


    }

    // 从数据库加载最新的心得笔记记录
    void loadNotes() {
        notesModel->select();
    }

private slots:
    // 点击列表中一行时，将笔记内容显示到详细信息区域
    void onNoteSelected(const QModelIndex &index) {
        if(index.isValid()){
            int row = index.row();
            QString noteContent = notesModel->data(notesModel->index(row, notesModel->fieldIndex("NoteContent"))).toString();
            detailText->setText(noteContent);
        }
    }

    // 新增笔记操作：弹出对话框输入报告类型、报告日期和笔记内容
    void addNote() {
        QDialog dialog(this);
        dialog.setWindowTitle("新增心得笔记");
        QFormLayout form(&dialog);


        // ——— 将 QLineEdit 改成 QComboBox ———
        QComboBox *typeCombo = new QComboBox(&dialog);
        typeCombo->addItems(QStringList() << "daily" << "weekly" << "monthly");
        QDateEdit *dateEdit = new QDateEdit(QDate::currentDate(), &dialog);
        dateEdit->setCalendarPopup(true);
        QTextEdit *contentEdit = new QTextEdit(&dialog);

//        QComboBox *reportTypeCombo = new QComboBox(this);
//        reportTypeCombo->addItem("日报");
//        reportTypeCombo->addItem("周报");
//        reportTypeCombo->addItem("月报");

        form.addRow("报告类型:", typeCombo);
        form.addRow("报告日期:", dateEdit);
        form.addRow("笔记内容:", contentEdit);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                     Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if(dialog.exec() == QDialog::Accepted) {
            QString reportType = typeCombo->currentText();
            QDate reportDate = dateEdit->date();
            QString noteContent = contentEdit->toPlainText();
            QSqlQuery query;
            query.prepare(
                "INSERT INTO ReportNotes (ReportType, ReportDate, NoteContent) "
                "VALUES (?, ?, ?)"
            );
            // 按顺序绑定：第一个 ? -> reportType，第二个 ? -> reportDate，第三个 ? -> noteContent
            query.addBindValue(reportType);
            // 对于 SQL Server，你可以直接绑定 QDateTime，或者显式转成字符串：
            query.addBindValue(reportDate);
            query.addBindValue(noteContent);
            if(!query.exec()){
                QMessageBox::warning(this, "错误", "新增笔记失败: " + query.lastError().text());
            } else {
                loadNotes();
            }
        }
    }

    // 编辑操作：编辑选中记录，弹出对话框进行修改
    void editNote() {
        QModelIndex index = notesView->currentIndex();
        if(!index.isValid()){
            QMessageBox::information(this, "提示", "请先选择一条记录进行编辑");
            return;
        }
        int row = index.row();
        int noteID = notesModel->data(notesModel->index(row, notesModel->fieldIndex("NoteID"))).toInt();
        QString currentType = notesModel->data(notesModel->index(row, notesModel->fieldIndex("ReportType"))).toString();
        QDate currentDate = notesModel->data(notesModel->index(row, notesModel->fieldIndex("ReportDate"))).toDate();
        QString currentContent = notesModel->data(notesModel->index(row, notesModel->fieldIndex("NoteContent"))).toString();

        QDialog dialog(this);
        dialog.setWindowTitle("编辑心得笔记");
        QFormLayout form(&dialog);


        // ——— 用 ComboBox 并预先设置当前值 ———
        QComboBox *typeCombo = new QComboBox(&dialog);
        typeCombo->addItems(QStringList() << "daily" << "weekly" << "monthly");
        int idx = typeCombo->findText(currentType, Qt::MatchFixedString);
        if (idx >= 0) typeCombo->setCurrentIndex(idx);
        QDateEdit *dateEdit = new QDateEdit(currentDate, &dialog);
        dateEdit->setCalendarPopup(true);
        QTextEdit *contentEdit = new QTextEdit(currentContent, &dialog);

        form.addRow("报告类型:", typeCombo);
        form.addRow("报告日期:", dateEdit);
        form.addRow("笔记内容:", contentEdit);

        QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                                     Qt::Horizontal, &dialog);
        form.addRow(&buttonBox);
        connect(&buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
        connect(&buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);
        if(dialog.exec() == QDialog::Accepted) {
            QString reportType = typeCombo->currentText();
            QDate reportDate = dateEdit->date();
            QString noteContent = contentEdit->toPlainText();
            QSqlQuery query;
            query.prepare(
                "UPDATE ReportNotes "
                "SET ReportType = ?, ReportDate = ?, NoteContent = ?, UpdatedAt = ? "
                "WHERE NoteID = ?"
            );
            query.addBindValue(reportType);
            query.addBindValue(reportDate);
            query.addBindValue(noteContent);
            query.addBindValue(QDateTime::currentDateTime());
            query.addBindValue(noteID);
            if(!query.exec()){
                QMessageBox::warning(this, "错误", "编辑笔记失败: " + query.lastError().text());
            } else {
                loadNotes();
            }
        }
    }

    // 删除操作：删除选中记录，先进行确认
    void deleteNote() {
        QModelIndex index = notesView->currentIndex();
        if(!index.isValid()){
            QMessageBox::information(this, "提示", "请先选择一条记录进行删除");
            return;
        }
        int row = index.row();
        int noteID = notesModel->data(notesModel->index(row, notesModel->fieldIndex("NoteID"))).toInt();
        if(QMessageBox::question(this, "确认删除", "是否确定删除选中的笔记?") == QMessageBox::Yes) {
            QSqlQuery query;
            query.prepare("DELETE FROM ReportNotes WHERE NoteID = :id");
            query.bindValue(":id", noteID);
            if(!query.exec()){
                QMessageBox::warning(this, "错误", "删除笔记失败: " + query.lastError().text());
            } else {
                loadNotes();
                detailText->clear();
            }
        }
    }
};

// ReportWidget：生成每日、每周、每月工作/学习报告
class ReportWidget : public QWidget {
    Q_OBJECT
public:
    ReportWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setupUI();
        generateReports();
    }

private:
    QTabWidget *tabWidget;
    QTextEdit *dailyReportText;
    QTextEdit *weeklyReportText;
    QTextEdit *monthlyReportText;
    QPushButton *refreshButton;
    QDateEdit *dailyDateEdit;
    QDateEdit *weeklyDateEdit;
    QDateEdit *monthlyDateEdit;

    // 初始化界面：使用 QTabWidget 分别显示每日、每周、每月报告，以及新增心得笔记页签
    void setupUI() {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 日期选择控件
        QHBoxLayout *controlLayout = new QHBoxLayout;
        controlLayout->addWidget(new QLabel("日期:", this));
        dailyDateEdit = new QDateEdit(QDate::currentDate(), this);
        dailyDateEdit->setCalendarPopup(true);
        controlLayout->addWidget(dailyDateEdit);
        controlLayout->addSpacing(20);

        controlLayout->addWidget(new QLabel("周所属日期:", this));
        weeklyDateEdit = new QDateEdit(QDate::currentDate(), this);
        weeklyDateEdit->setCalendarPopup(true);
        controlLayout->addWidget(weeklyDateEdit);
        controlLayout->addSpacing(20);

        controlLayout->addWidget(new QLabel("月份:", this));
        monthlyDateEdit = new QDateEdit(QDate::currentDate(), this);
        monthlyDateEdit->setCalendarPopup(true);
        monthlyDateEdit->setDisplayFormat("yyyy-MM");
        controlLayout->addWidget(monthlyDateEdit);

        mainLayout->addLayout(controlLayout);

        // 报告标签页
        tabWidget = new QTabWidget(this);

        dailyReportText = new QTextEdit(this);
        dailyReportText->setReadOnly(true);
        weeklyReportText = new QTextEdit(this);
        weeklyReportText->setReadOnly(true);
        monthlyReportText = new QTextEdit(this);
        monthlyReportText->setReadOnly(true);

        tabWidget->addTab(dailyReportText, "每日报告");
        tabWidget->addTab(weeklyReportText, "每周报告");
        tabWidget->addTab(monthlyReportText, "每月报告");

        // 新增“心得笔记”页签，显示报告列表、添加、编辑、删除操作
        tabWidget->addTab(new class ReportNotesWidget(this), "心得笔记");

        mainLayout->addWidget(tabWidget);

        // 刷新按钮
        refreshButton = new QPushButton("刷新报告", this);
        connect(refreshButton, &QPushButton::clicked, this, &ReportWidget::generateReports);
        mainLayout->addWidget(refreshButton);

        setLayout(mainLayout);


        setStyleSheet(R"(
                QPushButton {
                    background-color: #2980b9;
                    color: #ffffff;
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                    padding: 8px 20px;
                    font-size: 14px;
                }

                QPushButton:hover {
                    background-color: #3498db;
                    border: 2px solid #1a5276;
                }

                QPushButton:pressed {
                    background-color: #1f618d;
                }

                QDateEdit {
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                }

            )");
    }

    // 生成所有报告
    void generateReports() {
        QDate dDate = dailyDateEdit->date();
        QDate wDate = weeklyDateEdit->date();
        QDate mDate = monthlyDateEdit->date();

        dailyReportText->setText(generateDailyReport(dDate));
        weeklyReportText->setText(generateWeeklyReport(wDate));
        monthlyReportText->setText(generateMonthlyReport(mDate));
    }

    // 生成“每日报告”内容
    QString generateDailyReport(const QDate &date) {
        QString report;
        QSqlQuery query;
        QString dateStr = date.toString("yyyy-MM-dd");

        // 今日任务统计
        QString dailyTaskQuery = QString(
            "SELECT COUNT(*) AS TotalTasks, "
            "COALESCE(SUM(CASE WHEN IsCompleted = 1 THEN 1 ELSE 0 END), 0) AS CompletedTasks "
            "FROM ToDoTasks "
            "WHERE CONVERT(date, DueDate) = '%1'")
            .arg(dateStr);
        if (query.exec(dailyTaskQuery) && query.next()) {
            int totalTasks = query.value("TotalTasks").toInt();
            int completedTasks = query.value("CompletedTasks").toInt();
            report += "【今日任务统计】\n";
            report += QString("总任务数: %1\n已完成: %2\n未完成: %3\n")
                          .arg(totalTasks)
                          .arg(completedTasks)
                          .arg(totalTasks - completedTasks);
            double percent = totalTasks > 0 ? (100.0 * completedTasks / totalTasks) : 0;
            report += QString("完成率: %1%\n\n").arg(percent, 0, 'f', 1);
        } else {
            qDebug() << "查询每日任务错误:" << query.lastError().text();
            report += "查询每日任务数据错误\n\n";
        }

        // 今日事件统计
        QString dailyEventQuery = QString(
            "SELECT COUNT(*) AS TotalEvents "
            "FROM UserEvents "
            "WHERE CONVERT(date, EventDate) = '%1'")
            .arg(dateStr);
        if (query.exec(dailyEventQuery) && query.next()) {
            int totalEvents = query.value("TotalEvents").toInt();
            report += "【今日事件统计】\n";
            report += QString("总事件数: %1\n").arg(totalEvents);
        } else {
            qDebug() << "查询每日事件错误:" << query.lastError().text();
            report += "查询每日事件数据错误\n";
        }

        return report;
    }

    QString generateWeeklyReport(const QDate &date) {
        QString report;
        QSqlQuery query;
        int week = date.weekNumber();
        int year = date.year();

        // 本周任务统计
        QString weeklyTaskQuery = QString(
            "SELECT COUNT(*) AS TotalTasks, "
            "COALESCE(SUM(CASE WHEN IsCompleted = 1 THEN 1 ELSE 0 END), 0) AS CompletedTasks "
            "FROM ToDoTasks "
            "WHERE DATEPART(week, DueDate) = %1 "
            "AND DATEPART(year, DueDate) = %2")
            .arg(week)
            .arg(year);
        if (query.exec(weeklyTaskQuery) && query.next()) {
            int totalTasks = query.value("TotalTasks").toInt();
            int completedTasks = query.value("CompletedTasks").toInt();
            report += "【本周任务统计】\n";
            report += QString("总任务数: %1\n已完成: %2\n未完成: %3\n")
                          .arg(totalTasks)
                          .arg(completedTasks)
                          .arg(totalTasks - completedTasks);
            double percent = totalTasks > 0 ? (100.0 * completedTasks / totalTasks) : 0;
            report += QString("完成率: %1%\n\n").arg(percent, 0, 'f', 1);
        } else {
            qDebug() << "查询每周任务错误:" << query.lastError().text();
            report += "查询每周任务数据错误\n\n";
        }

        // 本周事件统计
        QString weeklyEventQuery = QString(
            "SELECT COUNT(*) AS TotalEvents "
            "FROM UserEvents "
            "WHERE DATEPART(week, EventDate) = %1 "
            "AND DATEPART(year, EventDate) = %2")
            .arg(week)
            .arg(year);
        if (query.exec(weeklyEventQuery) && query.next()) {
            int totalEvents = query.value("TotalEvents").toInt();
            report += "【本周事件统计】\n";
            report += QString("总事件数: %1\n").arg(totalEvents);
        } else {
            qDebug() << "查询每周事件错误:" << query.lastError().text();
            report += "查询每周事件数据错误\n";
        }

        return report;
    }

    QString generateMonthlyReport(const QDate &date) {
        QString report;
        QSqlQuery query;
        int month = date.month();
        int year = date.year();

        // 本月任务统计
        QString monthlyTaskQuery = QString(
            "SELECT COUNT(*) AS TotalTasks, "
            "COALESCE(SUM(CASE WHEN IsCompleted = 1 THEN 1 ELSE 0 END), 0) AS CompletedTasks "
            "FROM ToDoTasks "
            "WHERE DATEPART(month, DueDate) = %1 "
            "AND DATEPART(year, DueDate) = %2")
            .arg(month)
            .arg(year);
        if (query.exec(monthlyTaskQuery) && query.next()) {
            int totalTasks = query.value("TotalTasks").toInt();
            int completedTasks = query.value("CompletedTasks").toInt();
            report += "【本月任务统计】\n";
            report += QString("总任务数: %1\n已完成: %2\n未完成: %3\n")
                          .arg(totalTasks)
                          .arg(completedTasks)
                          .arg(totalTasks - completedTasks);
            double percent = totalTasks > 0 ? (100.0 * completedTasks / totalTasks) : 0;
            report += QString("完成率: %1%\n\n").arg(percent, 0, 'f', 1);
        } else {
            qDebug() << "查询每月任务错误:" << query.lastError().text();
            report += "查询每月任务数据错误\n\n";
        }

        // 本月事件统计
        QString monthlyEventQuery = QString(
            "SELECT COUNT(*) AS TotalEvents "
            "FROM UserEvents "
            "WHERE DATEPART(month, EventDate) = %1 "
            "AND DATEPART(year, EventDate) = %2")
            .arg(month)
            .arg(year);
        if (query.exec(monthlyEventQuery) && query.next()) {
            int totalEvents = query.value("TotalEvents").toInt();
            report += "【本月事件统计】\n";
            report += QString("总事件数: %1\n").arg(totalEvents);
        } else {
            qDebug() << "查询每月事件错误:" << query.lastError().text();
            report += "查询每月事件数据错误\n";
        }

        return report;
    }
};



//#include "reportwidget.moc"

//*********************************ToDoList模块******************************************


// 任务录入对话框：用于添加或编辑任务
class TaskInputDialog : public QDialog {
    Q_OBJECT
public:
    explicit TaskInputDialog(QWidget *parent = nullptr) : QDialog(parent) {
        setWindowTitle("添加任务");
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 任务描述
        mainLayout->addWidget(new QLabel("任务描述:", this));
        descriptionEdit = new QLineEdit(this);
        mainLayout->addWidget(descriptionEdit);

        // 截止日期时间
        mainLayout->addWidget(new QLabel("截止日期时间:", this));
        dueDateEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
        dueDateEdit->setCalendarPopup(true);
        mainLayout->addWidget(dueDateEdit);

        // 优先级（1～5，数值越大优先级越高）
        mainLayout->addWidget(new QLabel("优先级 (1-5):", this));
        prioritySpin = new QSpinBox(this);
        prioritySpin->setRange(1, 5);
        prioritySpin->setValue(1);
        mainLayout->addWidget(prioritySpin);

        // 添加任务按钮
        QPushButton *submitBtn = new QPushButton("确定", this);
        mainLayout->addWidget(submitBtn);

        connect(submitBtn, &QPushButton::clicked, this, &TaskInputDialog::onSubmit);
        setLayout(mainLayout);
    }

    QString getDescription() const { return descriptionEdit->text(); }
    QDateTime getDueDate() const { return dueDateEdit->dateTime(); }
    int getPriority() const { return prioritySpin->value(); }

    // setter 方法，用于编辑时预填数据
    void setDescription(const QString &desc) { descriptionEdit->setText(desc); }
    void setDueDate(const QDateTime &dt) { dueDateEdit->setDateTime(dt); }
    void setPriority(int p) { prioritySpin->setValue(p); }

signals:
    void taskSubmitted();

private slots:
    void onSubmit() {
        if (descriptionEdit->text().isEmpty()) {
            QMessageBox::warning(this, "警告", "任务描述不能为空！");
            return;
        }
        emit taskSubmitted();
        accept();
    }
private:
    QLineEdit *descriptionEdit;
    QDateTimeEdit *dueDateEdit;
    QSpinBox *prioritySpin;
};

// 定义一个结构体，保存每个图片项的数据
struct ImageItem {
    QLabel* label;         // 用于显示图片的标签
    QPixmap original;      // 原始加载的图片
    double localScale;     // 局部缩放比例（默认为1.0）
};

// 待办事项模块：展示任务列表、任务提醒、状态更新、任务添加、删除及编辑功能
class ToDoModule : public QWidget {
    Q_OBJECT
public:
    explicit ToDoModule(QWidget *parent = nullptr) : QWidget(parent) {
        QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 任务列表展示（使用 QTreeWidget，显示：任务描述、截止时间、优先级、状态）
        taskList = new QTreeWidget(this);
        taskList->setHeaderLabels({ "任务描述", "截止时间", "优先级", "状态" });
        mainLayout->addWidget(taskList);

        // 按钮区域：添加、标记完成、标记未完成、编辑、删除及刷新
        QHBoxLayout *btnLayout = new QHBoxLayout();
        QPushButton *addTaskBtn = new QPushButton("添加任务", this);
        QPushButton *markCompleteBtn = new QPushButton("标记为完成", this);
        QPushButton *markIncompleteBtn = new QPushButton("标记为未完成", this);
        QPushButton *editTaskBtn = new QPushButton("编辑任务", this);
        QPushButton *deleteTaskBtn = new QPushButton("删除任务", this);
        QPushButton *addImageBtn = new QPushButton("添加图片", this);  // 新增的按钮
        QPushButton *refreshBtn = new QPushButton("刷新", this);
        btnLayout->addWidget(addTaskBtn);
        btnLayout->addWidget(markCompleteBtn);
        btnLayout->addWidget(markIncompleteBtn);
        btnLayout->addWidget(editTaskBtn);
        btnLayout->addWidget(deleteTaskBtn);
        btnLayout->addWidget(addImageBtn);
        btnLayout->addWidget(refreshBtn);
        mainLayout->addLayout(btnLayout);

        setLayout(mainLayout);

        // 信号与槽连接
        connect(addTaskBtn, &QPushButton::clicked, this, &ToDoModule::onAddTask);
        connect(markCompleteBtn, &QPushButton::clicked, this, &ToDoModule::onMarkComplete);
        connect(markIncompleteBtn, &QPushButton::clicked, this, &ToDoModule::onMarkIncomplete);
        connect(editTaskBtn, &QPushButton::clicked, this, &ToDoModule::onEditTask);
        connect(deleteTaskBtn, &QPushButton::clicked, this, &ToDoModule::onDeleteTask);
        connect(addImageBtn, &QPushButton::clicked, this, &ToDoModule::onAddImage);  // 连接添加图片槽
        connect(refreshBtn, &QPushButton::clicked, this, &ToDoModule::loadTasks);

        // 新增：双击任务项查看图片
        connect(taskList, &QTreeWidget::itemDoubleClicked, this, &ToDoModule::onViewImages);

        // 定时器：每分钟检查一次任务提醒
        QTimer *reminderTimer = new QTimer(this);
        connect(reminderTimer, &QTimer::timeout, this, &ToDoModule::checkReminders);
        reminderTimer->start(60000);

        // 初次加载任务
        loadTasks();


        //----------------------------------------------------------

        QString style = R"(
                QPushButton {
                    background-color: #2980b9;
                    color: #ffffff;
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                }

                QPushButton:hover {
                    background-color: #3498db;
                    border: 2px solid #1a5276;
                }

                QPushButton:pressed {
                    background-color: #1f618d;

                }
        )";

        setStyleSheet(style);
        //-----------------------------------------------------------
    }


private slots:
    // 添加任务：弹出任务录入对话框，并将任务插入数据库
    void onAddTask() {
        TaskInputDialog dialog(this);
        if (dialog.exec() == QDialog::Accepted) {
            QString description = dialog.getDescription();
            QDateTime dueDate = dialog.getDueDate();
            int priority = dialog.getPriority();
            bool isCompleted = false;

            QSqlQuery query;
            // 注意：如果 TaskID 为非自增，请使用下面方式自动生成 TaskID，否则可省略 TaskID 字段
            if (!query.exec("SELECT ISNULL(MAX(TaskID), 0) + 1 FROM ToDoTasks")) {
                qDebug() << "获取新 TaskID 失败:" << query.lastError().text();
                return;
            }
            query.next();
            int newTaskID = query.value(0).toInt();

            // 插入任务，同时默认 UserID 为 1
            QString sql = QString("INSERT INTO ToDoTasks (TaskID, TaskDescription, DueDate, Priority, IsCompleted, UserID) "
                                  "VALUES (%1, '%2', '%3', %4, %5, %6)")
                              .arg(newTaskID)
                              .arg(description)
                              .arg(dueDate.toString("yyyy-MM-dd HH:mm:ss"))
                              .arg(priority)
                              .arg(isCompleted ? 1 : 0)
                              .arg(1); // 默认 UserID 为 1
            if (query.exec(sql)) {
                qDebug() << "任务添加成功";
                loadTasks();
            } else {
                qDebug() << "添加任务失败:" << query.lastError().text();
            }

        }
    }

    // 标记选中的任务为完成
    void onMarkComplete() {
        QList<QTreeWidgetItem*> selected = taskList->selectedItems();
        if (selected.isEmpty()) return;
        for (QTreeWidgetItem *item : selected) {
            QString taskId = item->data(0, Qt::UserRole).toString();
            QSqlQuery query;
            QString sql = QString("UPDATE ToDoTasks SET IsCompleted = 1 WHERE TaskID = %1").arg(taskId);
            if (query.exec(sql)) {
                item->setText(3, "完成");
            } else {
                qDebug() << "更新任务状态失败:" << query.lastError().text();
            }
        }
        loadTasks();
    }

    // 标记选中的任务为未完成
    void onMarkIncomplete() {
        QList<QTreeWidgetItem*> selected = taskList->selectedItems();
        if (selected.isEmpty()) return;
        for (QTreeWidgetItem *item : selected) {
            QString taskId = item->data(0, Qt::UserRole).toString();
            QSqlQuery query;
            QString sql = QString("UPDATE ToDoTasks SET IsCompleted = 0 WHERE TaskID = %1").arg(taskId);
            if (query.exec(sql)) {
                item->setText(3, "未完成");
            } else {
                qDebug() << "更新任务状态失败:" << query.lastError().text();
            }
        }
        loadTasks();
    }

    // 编辑任务：允许修改任务描述、截止时间和优先级
    void onEditTask() {
        QList<QTreeWidgetItem*> selected = taskList->selectedItems();
        if (selected.isEmpty()) {
            QMessageBox::information(this, "提示", "请先选择要编辑的任务。");
            return;
        }
        // 此处仅允许编辑单个任务
        QTreeWidgetItem *item = selected.first();
        QString taskId = item->data(0, Qt::UserRole).toString();
        QString currentDescription = item->text(0);
        QString currentDueDateStr = item->text(1);
        QDateTime currentDueDate = QDateTime::fromString(currentDueDateStr, "yyyy-MM-dd HH:mm");
        int currentPriority = item->text(2).toInt();

        TaskInputDialog dialog(this);
        dialog.setWindowTitle("编辑任务");
        dialog.setDescription(currentDescription);
        dialog.setDueDate(currentDueDate);
        dialog.setPriority(currentPriority);

        if (dialog.exec() == QDialog::Accepted) {
            QString newDescription = dialog.getDescription();
            QDateTime newDueDate = dialog.getDueDate();
            int newPriority = dialog.getPriority();

            QSqlQuery query;
            QString sql = QString("UPDATE ToDoTasks SET TaskDescription = '%1', DueDate = '%2', Priority = %3 "
                                  "WHERE TaskID = %4")
                              .arg(newDescription)
                              .arg(newDueDate.toString("yyyy-MM-dd HH:mm:ss"))
                              .arg(newPriority)
                              .arg(taskId);
            if (query.exec(sql)) {
                qDebug() << "任务编辑成功:" << taskId;
                loadTasks();
            } else {
                qDebug() << "任务编辑失败:" << query.lastError().text();
            }
        }

    }

    // 删除选中的任务
    void onDeleteTask() {
        QList<QTreeWidgetItem*> selected = taskList->selectedItems();
        if (selected.isEmpty()) return;
        for (QTreeWidgetItem *item : selected) {
            QString taskId = item->data(0, Qt::UserRole).toString();
            QSqlQuery query;
            QString sql = QString("DELETE FROM ToDoTasks WHERE TaskID = %1").arg(taskId);
            if (query.exec(sql)) {
                qDebug() << "删除任务成功:" << taskId;
            } else {
                qDebug() << "删除任务失败:" << query.lastError().text();
            }
        }
        loadTasks();
    }

    // 检查任务提醒：查询未来 10 分钟内未完成的任务，并弹出提醒
    void checkReminders() {
        QSqlQuery query;
        // 使用 SQL Server 的 DATEADD 获取当前时间加 10 分钟
        QString sql = "SELECT TaskID, TaskDescription, DueDate FROM ToDoTasks WHERE IsCompleted = 0 AND DueDate <= DATEADD(minute, 10, GETDATE())";
        if (query.exec(sql)) {
            while (query.next()) {
                int taskId = query.value("TaskID").toInt();
                QString description = query.value("TaskDescription").toString();
                QDateTime dueDate = query.value("DueDate").toDateTime();
                QMessageBox::information(this, "任务提醒",
                                         QString("任务：%1\n截止时间：%2")
                                         .arg(description)
                                         .arg(dueDate.toString("yyyy-MM-dd HH:mm")));
            }
        } else {
            qDebug() << "检查任务提醒失败:" << query.lastError().text();
        }
    }

    // 加载任务列表：从数据库查询所有任务，并刷新列表显示
    void loadTasks() {
        taskList->clear();
        QSqlQuery query;
        QString sql = "SELECT TaskID, TaskDescription, DueDate, Priority, IsCompleted FROM ToDoTasks ORDER BY DueDate";
        if (query.exec(sql)) {
            while (query.next()) {
                int taskId = query.value("TaskID").toInt();
                QString description = query.value("TaskDescription").toString();
                QDateTime dueDate = query.value("DueDate").toDateTime();
                int priority = query.value("Priority").toInt();
                bool isCompleted = query.value("IsCompleted").toBool();

                QTreeWidgetItem *item = new QTreeWidgetItem(taskList);
                // 将 TaskID 保存在 UserRole 中，便于后续操作
                item->setData(0, Qt::UserRole, taskId);
                item->setText(0, description);
                item->setText(1, dueDate.toString("yyyy-MM-dd HH:mm"));
                item->setText(2, QString::number(priority));
                item->setText(3, isCompleted ? "完成" : "未完成");
                taskList->addTopLevelItem(item);
            }
        } else {
            qDebug() << "加载任务失败:" << query.lastError().text();
        }
    }

    // 新增添加图片功能槽
    void onAddImage() {
        // 首先确认选择了一个任务
        QList<QTreeWidgetItem*> selected = taskList->selectedItems();
        if (selected.isEmpty()) {
            QMessageBox::information(this, "提示", "请先选择一个任务以添加图片。");
            return;
        }
        // 只允许为单个任务添加图片
        QTreeWidgetItem *item = selected.first();
        int taskId = item->data(0, Qt::UserRole).toInt();

        // 弹出文件对话框选择图片
        QString imagePath = QFileDialog::getOpenFileName(this,
                                                         "选择图片",
                                                         QDir::homePath(),
                                                         "图片文件 (*.png *.jpg *.jpeg *.bmp)");
        if (imagePath.isEmpty()) {
            return; // 用户取消
        }

        // 此处可按需求将图片复制至指定位置或上传到服务器，并获得最终的图片URL，当前示例直接存储本地路径

        QSqlQuery query;
        // 假设 TaskImages 表中的 ImageID 为自动增长字段，此处只需要插入 TaskID 和 ImagePath 信息
        QString sql = QString("INSERT INTO TaskImages (TaskID, ImagePath) VALUES (%1, '%2')")
                          .arg(taskId)
                          .arg(imagePath.replace("'", "''")); // 处理单引号转义
        if (query.exec(sql)) {
            QMessageBox::information(this, "成功", "图片已成功添加到任务中。");
        } else {
            QMessageBox::warning(this, "错误", "添加图片失败: " + query.lastError().text());
        }
    }

    void onViewImages(QTreeWidgetItem *item, int column){
        // 获取任务的 TaskID（假设保存在 UserRole 中）
            int taskId = item->data(0, Qt::UserRole).toInt();

            // 查询该任务的所有图片记录，同时获取 ImageID 用于后续删除和替换
            QSqlQuery query;
            QString sql = QString("SELECT ImageID, ImagePath, Description, UploadedAt FROM TaskImages WHERE TaskID = %1")
                                .arg(taskId);
            if (!query.exec(sql)) {
                qDebug() << "查询任务图片失败:" << query.lastError().text();
                return;
            }

            // 创建对话框展示所有图片
            QDialog *imagesDialog = new QDialog(this);
            imagesDialog->setWindowTitle("任务图片");
            // 设置一个初始大小
            imagesDialog->resize(800, 600);

            QVBoxLayout *dialogLayout = new QVBoxLayout(imagesDialog);

            // 添加全局控制区域：全局放大、恢复原始大小、全屏显示按钮
            QHBoxLayout *globalBtnLayout = new QHBoxLayout();
            QPushButton *globalZoomInBtn = new QPushButton("全局放大", imagesDialog);
            QPushButton *globalResetBtn = new QPushButton("恢复原始大小", imagesDialog);
            QPushButton *fullScreenBtn = new QPushButton("全屏显示", imagesDialog);
            globalBtnLayout->addWidget(globalZoomInBtn);
            globalBtnLayout->addWidget(globalResetBtn);
            globalBtnLayout->addWidget(fullScreenBtn);
            dialogLayout->addLayout(globalBtnLayout);

            // 使用 QScrollArea 使内容可滚动
            QScrollArea *scrollArea = new QScrollArea(imagesDialog);
            scrollArea->setWidgetResizable(true);
            QWidget *container = new QWidget();
            QVBoxLayout *containerLayout = new QVBoxLayout(container);
            container->setLayout(containerLayout);

            // 保存所有图片项到列表中，便于全局缩放时迭代更新
            QList<ImageItem*> imageItems;

            bool hasImages = false;
            // 遍历查询结果，将每个图片创建一个容器（包括图片显示和控制按钮）
            while (query.next()) {
                hasImages = true;
                int imageID = query.value("ImageID").toInt();
                QString imagePath = query.value("ImagePath").toString();
                QString desc = query.value("Description").toString();

                // 构造图片项信息
                ImageItem* itemData = new ImageItem;
                itemData->localScale = 1.0; // 初始局部比例为1.0

                // 用一个 QWidget 包含图片及其操作按钮
                QWidget *imageWidget = new QWidget(container);
                QVBoxLayout *imageLayout = new QVBoxLayout(imageWidget);

                // 创建用于显示图片的 QLabel
                QLabel *imgLabel = new QLabel(imageWidget);
                imgLabel->setAlignment(Qt::AlignCenter);
                QPixmap pixmap;
                if (!pixmap.load(imagePath)) {
                    imgLabel->setText("无法加载图片: " + imagePath);
                } else {
                    // 默认显示尺寸：这里设为 400x300（后续将乘以全局缩放因子）
                    imgLabel->setPixmap(pixmap.scaled(400, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
                // 保存原始 pixmap，并保存 label 指针
                itemData->original = pixmap;
                itemData->label = imgLabel;

                imageLayout->addWidget(imgLabel);

                // 如果有说明信息，添加一个描述标签
                if (!desc.isEmpty()) {
                    QLabel *descLabel = new QLabel("说明：" + desc, imageWidget);
                    imageLayout->addWidget(descLabel);
                }

                // 添加局部操作按钮：局部放大、局部缩小、替换和删除
                QHBoxLayout *btnLayout = new QHBoxLayout();
                QPushButton *zoomInBtn = new QPushButton("放大", imageWidget);
                QPushButton *zoomOutBtn = new QPushButton("缩小", imageWidget);
                QPushButton *replaceBtn = new QPushButton("替换", imageWidget);
                QPushButton *deleteBtn = new QPushButton("删除", imageWidget);
                btnLayout->addWidget(zoomInBtn);
                btnLayout->addWidget(zoomOutBtn);
                btnLayout->addWidget(replaceBtn);
                btnLayout->addWidget(deleteBtn);
                imageLayout->addLayout(btnLayout);

                // 保存到列表中
                imageItems.append(itemData);

                // 局部“放大”操作（局部比例增加，更新显示）
                connect(zoomInBtn, &QPushButton::clicked, imageWidget, [=]() mutable {
                    itemData->localScale += 0.2;
                    // 更新当前图片显示，根据全局缩放因子和局部缩放
                    double finalScale = itemData->localScale *
                                        imagesDialog->property("globalScaleFactor").toDouble();
                    QSize targetSize = itemData->original.size() * finalScale;
                    itemData->label->setPixmap(itemData->original.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                });

                // 局部“缩小”操作（局部比例减小，更新显示）
                connect(zoomOutBtn, &QPushButton::clicked, imageWidget, [=]() mutable {
                    if (itemData->localScale > 0.4) {
                        itemData->localScale -= 0.2;
                        double finalScale = itemData->localScale *
                                            imagesDialog->property("globalScaleFactor").toDouble();
                        QSize targetSize = itemData->original.size() * finalScale;
                        itemData->label->setPixmap(itemData->original.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                    }
                });

                // “替换”按钮：选择新图片后，更新数据库和显示
                connect(replaceBtn, &QPushButton::clicked, imageWidget, [=]() mutable {
                    QString newImagePath = QFileDialog::getOpenFileName(imageWidget,
                                                                         "选择新图片",
                                                                         QDir::homePath(),
                                                                         "图片文件 (*.png *.jpg *.jpeg *.bmp)");
                    if(newImagePath.isEmpty())
                        return;
                    QSqlQuery updateQuery;
                    QString updateSql = QString("UPDATE TaskImages SET ImagePath = '%1' WHERE ImageID = %2")
                                        .arg(newImagePath.replace("'", "''"))
                                        .arg(imageID);
                    if (!updateQuery.exec(updateSql)) {
                        QMessageBox::warning(imageWidget, "错误", "图片替换失败：" + updateQuery.lastError().text());
                        return;
                    }
                    QPixmap newPixmap;
                    if(!newPixmap.load(newImagePath)) {
                        QMessageBox::warning(imageWidget, "错误", "无法加载新图片：" + newImagePath);
                        return;
                    }
                    // 更新原始图片、重置局部比例
                    itemData->original = newPixmap;
                    itemData->localScale = 1.0;
                    double finalScale = itemData->localScale *
                                        imagesDialog->property("globalScaleFactor").toDouble();
                    QSize targetSize = newPixmap.size() * finalScale;
                    itemData->label->setPixmap(newPixmap.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                });

                // “删除”按钮：删除数据库记录，并从界面中移除该图片控件
                connect(deleteBtn, &QPushButton::clicked, imageWidget, [=, &containerLayout]() mutable {
                    if (QMessageBox::question(imageWidget, "确认删除", "确定删除该图片吗？") == QMessageBox::Yes) {
                        QSqlQuery delQuery;
                        QString delSql = QString("DELETE FROM TaskImages WHERE ImageID = %1").arg(imageID);
                        if(!delQuery.exec(delSql)) {
                            QMessageBox::warning(imageWidget, "删除失败", "删除图片失败：" + delQuery.lastError().text());
                            return;
                        }
                        containerLayout->removeWidget(imageWidget);
                        imageWidget->deleteLater();
                    }
                });

                // 将每个图片项添加到容器布局中
                containerLayout->addWidget(imageWidget);
            }

            if (!hasImages) {
                QLabel *noImgLabel = new QLabel("该任务没有关联的图片。", container);
                containerLayout->addWidget(noImgLabel);
            }

            scrollArea->setWidget(container);
            dialogLayout->addWidget(scrollArea);

            // 设置初始全局缩放因子属性到对话框（全局比例默认为1.0）
            imagesDialog->setProperty("globalScaleFactor", 1.0);

            // 全局“放大”按钮：增加全局缩放因子后，更新所有图片
            connect(globalZoomInBtn, &QPushButton::clicked, imagesDialog, [=]() mutable {
                double globalScale = imagesDialog->property("globalScaleFactor").toDouble();
                globalScale *= 1.2;  // 每次放大 1.2 倍
                imagesDialog->setProperty("globalScaleFactor", globalScale);
                // 依次更新每个图片项
                for (ImageItem* itemData : imageItems) {
                    double finalScale = itemData->localScale * globalScale;
                    QSize targetSize = itemData->original.size() * finalScale;
                    itemData->label->setPixmap(itemData->original.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
                // 可选：同时调整对话框尺寸（例如放大 1.2 倍）
                imagesDialog->resize(imagesDialog->size() * 1.2);
            });

            // 全局“恢复原始大小”按钮：将全局缩放因子恢复为1.0，并更新所有图片与对话框尺寸
            connect(globalResetBtn, &QPushButton::clicked, imagesDialog, [=]() mutable {
                imagesDialog->setProperty("globalScaleFactor", 1.0);
                for (ImageItem* itemData : imageItems) {
                    double finalScale = itemData->localScale * 1.0;
                    QSize targetSize = itemData->original.size() * finalScale;
                    itemData->label->setPixmap(itemData->original.scaled(targetSize, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                }
                // 恢复对话框至预设大小
                imagesDialog->resize(800, 600);
            });

            // 全屏按钮：切换全屏显示与正常窗口（例如双击按钮实现切换，可根据实际需求改进）
            connect(fullScreenBtn, &QPushButton::clicked, imagesDialog, [=]() mutable {
                if (imagesDialog->windowState() & Qt::WindowFullScreen)
                    imagesDialog->setWindowState(Qt::WindowNoState);
                else
                    imagesDialog->setWindowState(Qt::WindowFullScreen);
            });

            // 添加关闭按钮
            QPushButton *closeBtn = new QPushButton("关闭", imagesDialog);
            dialogLayout->addWidget(closeBtn);
            connect(closeBtn, &QPushButton::clicked, imagesDialog, &QDialog::accept);

            imagesDialog->setLayout(dialogLayout);
            imagesDialog->exec();

            // 注意：对话框关闭后，释放创建的 ImageItem 内存（实际项目中请采用智能指针或封装类管理）
            qDeleteAll(imageItems);
    }

private:
    QTreeWidget *taskList;
};
//**********************************主页面展示*******************************************

//集成其他功能的按钮
class OtherFunctionsWidget : public QWidget {
    Q_OBJECT
public:
    OtherFunctionsWidget(QWidget *parent = nullptr) : QWidget(parent) {

          setWindowTitle("其他功能");
          resize(800, 600);
          setMinimumSize(800, 880);

          this->setStyleSheet(R"(
             background-color: #c2e9fb;
            )");

          QVBoxLayout *layout = new QVBoxLayout(this);
          QTabWidget *tabWidget = new QTabWidget(this);
          //-----------------------------------------------------------
          tabWidget->setStyleSheet(R"(
                QTabWidget::pane {
                    border: 2px solid #3498db;
                    border-radius: 8px;
                    margin: 2px;
                }

                QTabBar::tab {
                    background: #ecf0f1;
                    border: 1px solid #3498db;
                    border-radius: 5px;
                    margin-right: 2px;
                }

                QTabBar::tab:selected {
                    background: #3498db;
                    color: white;
                }
            )");
          //-----------------------------------------------------------
          tabWidget->addTab(new AnalysisReportWidget(this), "报表分析");
          tabWidget->addTab(new ReportWidget(this), "工作/学习报告");
          tabWidget->addTab(new ToDoModule(this), "待办事项");//todolist

          QPushButton *returnButton = new QPushButton("返回", this);
          connect(returnButton, &QPushButton::clicked, this, &OtherFunctionsWidget::returnToMain);

          //-----------------------------------------------------------
          returnButton->setStyleSheet(R"(
                QPushButton {
                    background-color: #2980b9;
                    color: #ffffff;
                    border: 1px solid #1a5276;
                    border-radius: 5px;
                    padding: 10px 20px;
                    font-size: 16px;
                }

                QPushButton:hover {
                    background-color: #3498db;
                    border: 2px solid #1a5276;
                }

                QPushButton:pressed {
                    background-color: #1f618d;
                    padding: 9px 19px;
                }
            )");
          //-----------------------------------------------------------
          layout->addWidget(tabWidget);
          layout->addWidget(returnButton);
          setLayout(layout);
    }
signals:
    void returnToMain(); // 发送返回信号
};

struct Reminder {
    QDateTime time;
    QString message;
};


#include <QLabel>
#include <QString>
#include <QMouseEvent>

class ThumbnailLabel : public QLabel {
    Q_OBJECT
public:
    explicit ThumbnailLabel(const QString &imagePath, QWidget *parent = nullptr)
        : QLabel(parent), m_imagePath(imagePath)
    {
        setContextMenuPolicy(Qt::CustomContextMenu);
    }

    const QString& imagePath() const { return m_imagePath; }

signals:
    void doubleClicked(const QString &imagePath);

protected:
    void mouseDoubleClickEvent(QMouseEvent *event) override {
        if (event->button() == Qt::LeftButton) {
            emit doubleClicked(m_imagePath);
        }
        // 不要忘记让基类处理其它逻辑
        QLabel::mouseDoubleClickEvent(event);
    }

private:
    QString m_imagePath;
};

//*************************************************************************
#include<QGroupBox>
#include<QStackedLayout>
// 用于区分记录类型
enum RecordType {
    ToDoTask,
    UserEvent
};

class TaskDetailDialog : public QDialog {
    Q_OBJECT
public:
    /**
     * @brief 构造函数
     * @param recordID 待显示记录的ID（TaskID或EventID）
     * @param type 记录类型：待办任务或事件
     * @param parent 父窗口
     */
    explicit TaskDetailDialog(int recordID, RecordType type, QWidget *parent = nullptr)
        : QDialog(parent), m_recordID(recordID), m_recordType(type) {
        setWindowTitle("详情");
        QVBoxLayout *mainLayout = new QVBoxLayout(this);


        // 按钮与缩放条
                QHBoxLayout *btnLayout = new QHBoxLayout;
                m_addImageBtn = new QPushButton("添加图片", this);
                btnLayout->addWidget(m_addImageBtn);
                connect(m_addImageBtn, &QPushButton::clicked, this, &TaskDetailDialog::onAddImage);

                m_pickColorBtn = new QPushButton(tr("设置详情页面颜色"), this);
                btnLayout->addWidget(m_pickColorBtn);
                connect(m_pickColorBtn, &QPushButton::clicked, this, &TaskDetailDialog::onPickColor);

                m_setCardColorBtn = new QPushButton(tr("设置主页面卡片颜色"), this);
                btnLayout->addWidget(m_setCardColorBtn);
                connect(m_setCardColorBtn, &QPushButton::clicked, this, &TaskDetailDialog::onSetCardColor);


                btnLayout->addStretch();
                btnLayout->addWidget(new QLabel("缩放:", this));
                m_zoomSlider = new QSlider(Qt::Horizontal, this);
                m_zoomSlider->setRange(10, 200);
                m_zoomSlider->setValue(100);
                btnLayout->addWidget(m_zoomSlider);
                connect(m_zoomSlider, &QSlider::valueChanged, this, &TaskDetailDialog::onZoomChanged);

                mainLayout->addLayout(btnLayout);

                // 内容区作为 proxy widget
                m_contentWidget = new QWidget;
                m_contentLayout = new QVBoxLayout(m_contentWidget);
                m_contentLayout->setSpacing(10);
                m_thumbnailLayout = new QHBoxLayout;
                m_contentLayout->addLayout(m_thumbnailLayout);
                m_contentLayout->addStretch();

                // 场景与视图
                m_scene = new QGraphicsScene(this);
                QGraphicsProxyWidget *proxy = m_scene->addWidget(m_contentWidget);
                m_view = new QGraphicsView(m_scene, this);
                m_view->setRenderHint(QPainter::Antialiasing);
                mainLayout->addWidget(m_view);

        QFormLayout *formLayout = new QFormLayout();



        if (m_recordType == UserEvent) {
            // 为事件记录创建控件
            m_eventTitleEdit = new QLineEdit(this);
            m_eventDescriptionEdit = new QTextEdit(this);
            m_eventDateEdit = new QDateTimeEdit(this);
            m_eventDateEdit->setCalendarPopup(true);
            m_eventLocationEdit = new QLineEdit(this);
            m_eventCategoryEdit = new QLineEdit(this);
            m_createdAtLabel = new QLabel(this);

            formLayout->addRow("事件标题:", m_eventTitleEdit);
            formLayout->addRow("事件描述:", m_eventDescriptionEdit);
            formLayout->addRow("事件发生时间:", m_eventDateEdit);
            formLayout->addRow("事件地点:", m_eventLocationEdit);
            formLayout->addRow("事件类别:", m_eventCategoryEdit);
            formLayout->addRow("记录创建时间:", m_createdAtLabel);
        } else { // 待办任务
            m_taskDescriptionEdit = new QLineEdit(this);
            m_dueDateEdit = new QDateTimeEdit(this);
            m_dueDateEdit->setCalendarPopup(true);
            m_priorityEdit = new QLineEdit(this);
            m_isCompletedCheck = new QCheckBox(this);
            m_taskCreatedAtLabel = new QLabel(this);

            formLayout->addRow("待办事项描述:", m_taskDescriptionEdit);
            formLayout->addRow("截止日期:", m_dueDateEdit);
            formLayout->addRow("任务优先级:", m_priorityEdit);
            formLayout->addRow("是否完成:", m_isCompletedCheck);
            formLayout->addRow("记录创建时间:", m_taskCreatedAtLabel);
        }

        mainLayout->addLayout(formLayout);

        // 底部按钮
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        m_saveButton = new QPushButton("保存", this);
        m_deleteButton = new QPushButton("删除", this);
        m_cancelButton = new QPushButton("取消", this);

        buttonLayout->addWidget(m_saveButton);
        buttonLayout->addWidget(m_deleteButton);
        buttonLayout->addWidget(m_cancelButton);

        mainLayout->addLayout(buttonLayout);

        // 信号槽连接
        connect(m_saveButton, &QPushButton::clicked, this, &TaskDetailDialog::saveRecord);
        connect(m_deleteButton, &QPushButton::clicked, this, &TaskDetailDialog::deleteRecord);
        connect(m_cancelButton, &QPushButton::clicked, this, &QDialog::reject);


        // 从数据库加载记录数据
        loadRecord();

        // //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
        // setStyleSheet(R"(
        //         QTextEdit {
        //         background-color: #d0e0f0;
        //         border: 1px solid #b0c4de;
        //         border-radius: 3px;
        //         padding: 5px;
        //         }

        //         QLineEdit {
        //         background-color: #d0e0f0;
        //         border: 1px solid #b0c4de;
        //         border-radius: 3px;
        //         padding: 5px;
        //         }
        // )");
        // //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️

    }

private slots:
    // 加载记录信息
    void loadRecord() {
        QSqlQuery query;
        QSqlQuery cq;
        if (m_recordType == UserEvent) {
            query.prepare("SELECT EventTitle, EventDescription, EventDate, EventLocation, Category, CreatedAt FROM UserEvents WHERE EventID = ?");
            query.addBindValue(m_recordID);
            cq.prepare("SELECT BackgroundColor FROM EventCardColors WHERE EventID = ?");
            if (query.exec() && query.next()) {
                // 填充事件数据
                m_eventTitleEdit->setText(query.value(0).toString());
                m_eventDescriptionEdit->setText(query.value(1).toString());
                m_eventDateEdit->setDateTime(query.value(2).toDateTime());
                m_eventLocationEdit->setText(query.value(3).toString());
                m_eventCategoryEdit->setText(query.value(4).toString());
                m_createdAtLabel->setText(query.value(5).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            } else {
                qDebug() << "错误信息:" << query.lastError().text();
                QMessageBox::warning(this, "错误", "加载事件数据失败！");
            }
        } else {  // 待办任务
            query.prepare("SELECT TaskDescription, DueDate, Priority, IsCompleted, CreatedAt FROM ToDoTasks WHERE TaskID = ?");
            query.addBindValue(m_recordID);
            cq.prepare("SELECT BackgroundColor FROM TaskCardColors WHERE TaskID = ?");
            if (query.exec() && query.next()) {
                // 填充待办任务数据
                m_taskDescriptionEdit->setText(query.value(0).toString());
                m_dueDateEdit->setDateTime(query.value(1).toDateTime());
                m_priorityEdit->setText(query.value(2).toString());
                m_isCompletedCheck->setChecked(query.value(3).toBool());
                m_taskCreatedAtLabel->setText(query.value(4).toDateTime().toString("yyyy-MM-dd HH:mm:ss"));
            } else {
                qDebug() << "错误信息:" << query.lastError().text();
                QMessageBox::warning(this, "错误", "加载待办任务数据失败！");
            }
        }

        cq.addBindValue(m_recordID);
        if (cq.exec() && cq.next()) {
            QColor c(cq.value(0).toString());
            if (c.isValid()) {
                m_selectedColor = c;
                this->setStyleSheet(QString(R"(
                    QDialog{ background:%1; }

                    QDialog QTextEdit {
                        background-color: rgba(255, 255, 255, 150);
                        border: 1px solid #cccccc;
                        padding: 5px;
                        color: #333333;
                        border-radius: 5px;
                    }

                    QDialog QTextEdit:focus {
                        border: 1px solid #999999;
                    }

                    QDialog QLineEdit {
                        background-color: rgba(255, 255, 255, 150);
                        border: 1px solid #cccccc;
                        padding: 5px;
                        color: #333333;
                        border-radius: 5px;
                    }

                    QDialog QLineEdit:focus {
                        border: 1px solid #999999;
                    }
                                )").arg(c.name()));
                            }
        }
        //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
        else{
            this->setStyleSheet(R"(
                    QDialog {
                        background: qlineargradient(x1:0, y1:1, x2:0, y2:0, stop:0 #D9AFD9, stop:1 #97D9E1);
                    }

                    QTextEdit {
                                background-color: rgba(255, 255, 255, 150);
                                border: 1px solid #cccccc;
                                padding: 5px;
                                color: #333333;
                                border-radius: 5px;
                            }

                    QTextEdit:focus {
                                border: 1px solid #999999;
                            }

                    QLineEdit {
                                background-color: rgba(255, 255, 255, 150);
                                border: 1px solid #cccccc;
                                padding: 5px;
                                color: #333333;
                                border-radius: 5px;
                    }

                    QLineEdit:focus {
                                border: 1px solid #999999;
                            }

                    QDateTimeEdit{
                                background-color: rgba(255, 255, 255, 150);
                                border: 1px solid #cccccc;
                                padding: 5px;
                                color: #333333;
                                border-radius: 5px;
                    }
                )");
        }

        //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️


        //加载时，如果在表中已有映射，则读取并同步到 m_customCardColor
        QSqlQuery rq;
        rq.prepare("SELECT BackgroundColor FROM RecordCustomColors WHERE RecordType=? AND RecordID=?");
        rq.addBindValue(m_recordType==UserEvent?"Event":"Task");
        rq.addBindValue(m_recordID);
        if (rq.exec() && rq.next()) {
            QColor c(rq.value(0).toString());
            if (c.isValid()) {
                m_customCardColor = c;
                this->setStyleSheet(QString("QDialog{ background:%1; }").arg(c.name()));
                m_setCardColorBtn->setStyleSheet(
                    QString("background-color:%1").arg(c.name())
                );
            }
        }

        loadImages();
    }

    void loadImages() {
        // 清空旧的缩略图
        QLayoutItem *child;
        while ((child = m_thumbnailLayout->takeAt(0))) {
            delete child->widget();
            delete child;
        }

        QSqlQuery query;
            if (m_recordType == ToDoTask)
                query.prepare("SELECT ImageID, ImagePath FROM TaskImages WHERE TaskID = ?");
            else
                query.prepare("SELECT ImageID, ImagePath FROM EventImages WHERE EventID = ?");
            query.addBindValue(m_recordID);
            query.exec();

            while (query.next()) {
                int imgID    = query.value(0).toInt();
                QString path = query.value(1).toString();

                // 使用自定义的 ThumbnailLabel
                ThumbnailLabel *thumb = new ThumbnailLabel(path, this);
                QPixmap pix(path);
                thumb->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                thumb->setFrameShape(QFrame::Box);

                // 连接双击信号
                connect(thumb, &ThumbnailLabel::doubleClicked,
                        this, &TaskDetailDialog::showImageFull);

                // 右键菜单保留不变
                connect(thumb, &QLabel::customContextMenuRequested, this,
                        [=](const QPoint &) {
                            QMenu menu;
                            QAction *del = menu.addAction(tr("删除"));
                            QAction *rep = menu.addAction(tr("替换"));
                            QAction *act = menu.exec(QCursor::pos());
                            if (act == del) onDeleteImage(imgID);
                            if (act == rep) onReplaceImage(imgID);
                        });

                m_thumbnailLayout->addWidget(thumb);
            }
            m_thumbnailLayout->addStretch();
        }

        void onAddImage() {
            QString file = QFileDialog::getOpenFileName(this, "选择图片", {}, "Images (*.png *.jpg *.jpeg *.bmp)");
            if (file.isEmpty()) return;
            QSqlQuery iq;
            if (m_recordType == ToDoTask) {
                iq.prepare("INSERT INTO TaskImages (TaskID, ImagePath) VALUES (?,?)");
            } else {
                iq.prepare("INSERT INTO EventImages (EventID, ImagePath) VALUES (?,?)");
            }
            iq.addBindValue(m_recordID);
            iq.addBindValue(file);
            if (!iq.exec()) {
                QMessageBox::warning(this, "错误", "保存图片失败: " + iq.lastError().text());
                return;
            }
            loadImages();
        }

        void onDeleteImage(int imgID) {
            // 构造删除语句
               QSqlQuery dq;
               if (m_recordType == ToDoTask) {
                   dq.prepare("DELETE FROM TaskImages WHERE ImageID = ?");
               } else {
                   dq.prepare("DELETE FROM EventImages WHERE ImageID = ?");
               }
               dq.addBindValue(imgID);

               // 执行并检查错误
               if (!dq.exec()) {
                   QMessageBox::warning(this,
                                        tr("错误"),
                                        tr("删除图片失败: %1").arg(dq.lastError().text()));
                   return;
               }

               // 重新加载缩略图
               loadImages();
        }

        void onReplaceImage(int imgID) {
            // 打开文件对话框让用户选择新图片
                QString file = QFileDialog::getOpenFileName(this,
                                                            tr("选择新图片"),
                                                            QString(),
                                                            tr("Images (*.png *.jpg *.jpeg *.bmp)"));
                if (file.isEmpty())
                    return;

                // 构造更新语句
                QSqlQuery uq;
                if (m_recordType == ToDoTask) {
                    uq.prepare("UPDATE TaskImages SET ImagePath = ? WHERE ImageID = ?");
                } else {
                    uq.prepare("UPDATE EventImages SET ImagePath = ? WHERE ImageID = ?");
                }
                uq.addBindValue(file);
                uq.addBindValue(imgID);

                // 执行并检查错误
                if (!uq.exec()) {
                    QMessageBox::warning(this,
                                         tr("错误"),
                                         tr("替换图片失败: %1").arg(uq.lastError().text()));
                    return;
                }

                // 重新加载缩略图
                loadImages();
        }

        void onZoomChanged(int value) {
            qreal scale = value / 100.0;
            QTransform t;
            t.scale(scale, scale);
            m_view->setTransform(t);
        }


    // 保存修改后的记录信息
    void saveRecord() {
        QSqlQuery query;
        QSqlQuery uq;
        if (m_recordType == UserEvent) {
            query.prepare("UPDATE UserEvents SET EventTitle = ?, EventDescription = ?, EventDate = ?, EventLocation = ?, Category = ? WHERE EventID = ?");
            query.addBindValue(m_eventTitleEdit->text());
            query.addBindValue(m_eventDescriptionEdit->toPlainText());
            query.addBindValue(m_eventDateEdit->dateTime());
            query.addBindValue(m_eventLocationEdit->text());
            query.addBindValue(m_eventCategoryEdit->text());
            query.addBindValue(m_recordID);

            uq.prepare(
                "IF EXISTS (SELECT 1 FROM EventCardColors WHERE EventID=?) "
                " UPDATE EventCardColors SET BackgroundColor=? WHERE EventID=? "
                "ELSE "
                " INSERT INTO EventCardColors(EventID,BackgroundColor) VALUES(?,?)"
            );
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_selectedColor.name());
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_selectedColor.name());

            if (!query.exec()) {
                QMessageBox::warning(this, "错误", "保存事件数据失败！");
                return;
            }
        } else {
            query.prepare("UPDATE ToDoTasks SET TaskDescription = ?, DueDate = ?, Priority = ?, IsCompleted = ? WHERE TaskID = ?");
            query.addBindValue(m_taskDescriptionEdit->text());
            query.addBindValue(m_dueDateEdit->dateTime());
            query.addBindValue(m_priorityEdit->text().toInt());
            query.addBindValue(m_isCompletedCheck->isChecked());
            query.addBindValue(m_recordID);

            uq.prepare(
                "IF EXISTS (SELECT 1 FROM TaskCardColors WHERE TaskID=?) "
                " UPDATE TaskCardColors SET BackgroundColor=? WHERE TaskID=? "
                "ELSE "
                " INSERT INTO TaskCardColors(TaskID,BackgroundColor) VALUES(?,?)"
            );
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_selectedColor.name());
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_recordID);
            uq.addBindValue(m_selectedColor.name());

            if (!query.exec()) {
                QMessageBox::warning(this, "错误", "保存待办任务数据失败！");
                return;
            }
        }
        if (!uq.exec()) {
           QMessageBox::warning(this, tr("错误"), tr("保存卡片颜色失败：") + uq.lastError().text());
        }
        QMessageBox::information(this, "成功", "保存成功！");
        accept();
    }

    // 删除当前记录
    void deleteRecord() {
        int ret = QMessageBox::question(this, "确认删除", "确认删除当前记录吗？", QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::Yes) {
            QSqlQuery query;
            if (m_recordType == UserEvent) {
                query.prepare("DELETE FROM UserEvents WHERE EventID = ?");
                query.addBindValue(m_recordID);
            } else {
                query.prepare("DELETE FROM ToDoTasks WHERE TaskID = ?");
                query.addBindValue(m_recordID);
            }
            if (!query.exec()) {
                QMessageBox::warning(this, "错误", "删除记录失败！");
                return;
            }
            QMessageBox::information(this, "成功", "删除成功！");
            accept();
        }
    }

    void onPickColor() {
        QColor color = QColorDialog::getColor(
            m_selectedColor.isValid() ? m_selectedColor : Qt::white,
            this,
            tr("选择背景颜色")
        );
        if (!color.isValid()) return;
        m_selectedColor = color;
        // 将按钮背景同步为选中颜色
        QString btnStyle = QString("background-color:%1").arg(color.name());
        m_pickColorBtn->setStyleSheet(btnStyle);
    }

    void onSetCardColor() {
        // 弹出颜色对话框
        QColor color = QColorDialog::getColor(
            m_customCardColor.isValid() ? m_customCardColor : Qt::white,
            this,
            tr("设置主页面卡片背景色")
        );
        if (!color.isValid())
            return;

        m_customCardColor = color;
        // 实时预览：将对话框背景设为所选颜色
        this->setStyleSheet(QString("QDialog{ background:%1; }").arg(color.name()));
        // 刷新按钮背景，自动调整文字颜色
        m_setCardColorBtn->setStyleSheet(
            QString("background-color:%1; color:%2;")
                .arg(color.name())
                .arg(color.lightness() < 128 ? "#FFF" : "#000")
        );

        // 保存到数据库：先尝试 UPDATE，再根据受影响行数决定是否 INSERT
        QString typeStr = (m_recordType == UserEvent ? "Event" : "Task");
        QSqlQuery q;

        // 1) UPDATE
        q.prepare("UPDATE RecordCustomColors "
                  "SET BackgroundColor = ? "
                  "WHERE RecordType = ? AND RecordID = ?");
        q.addBindValue(color.name());
        q.addBindValue(typeStr);
        q.addBindValue(m_recordID);
        if (!q.exec()) {
            QMessageBox::warning(this,
                                 tr("错误"),
                                 tr("更新自定义卡片颜色失败: %1").arg(q.lastError().text()));
            return;
        }

        // 2) 如果没有行被更新，则 INSERT
        if (q.numRowsAffected() == 0) {
            QSqlQuery iq;
            iq.prepare("INSERT INTO RecordCustomColors (RecordType, RecordID, BackgroundColor) "
                       "VALUES (?, ?, ?)");
            iq.addBindValue(typeStr);
            iq.addBindValue(m_recordID);
            iq.addBindValue(color.name());
            if (!iq.exec()) {
                QMessageBox::warning(this,
                                     tr("错误"),
                                     tr("插入自定义卡片颜色失败: %1").arg(iq.lastError().text()));
            }
        }
    }

    void showImageFull(const QString &imagePath){
        // 创建弹窗
        QDialog *dlg = new QDialog(this);
        dlg->setWindowTitle(tr("查看图片"));
        dlg->setAttribute(Qt::WA_DeleteOnClose);  // 关窗时自动 delete

        // 2. 原始图片和显示控件
        QPixmap origPix(imagePath);
        QLabel *lbl = new QLabel;
        lbl->setAlignment(Qt::AlignCenter);
        lbl->setPixmap(origPix);

        QScrollArea *scroll = new QScrollArea;
        scroll->setWidget(lbl);
        scroll->setWidgetResizable(true);

        // 3. 初始化状态
        qreal scaleFactor = 1.0;
        int rotationAngle = 0;

        // 4. 更新显示的函数
        auto updateImage = [lbl, origPix, &scaleFactor, &rotationAngle]() {
            QTransform t;
            t.rotate(rotationAngle);
            QPixmap tmp = origPix.transformed(t, Qt::SmoothTransformation);
            lbl->setPixmap(tmp.scaled(tmp.size() * scaleFactor,
                                      Qt::KeepAspectRatio,
                                      Qt::SmoothTransformation));
        };

        // 5. 创建控制按钮
        QPushButton *zoomInBtn  = new QPushButton(tr("放大"));
        QPushButton *zoomOutBtn = new QPushButton(tr("缩小"));
        QPushButton *rotLeftBtn  = new QPushButton(tr("向左旋转"));
        QPushButton *rotRightBtn = new QPushButton(tr("向右旋转"));

        // 6. 连接按钮信号
        connect(zoomInBtn, &QPushButton::clicked, dlg, [=, &scaleFactor]() {
            scaleFactor *= 1.25;
            updateImage();
        });
        connect(zoomOutBtn, &QPushButton::clicked, dlg, [=, &scaleFactor]() {
            scaleFactor /= 1.25;
            updateImage();
        });
        connect(rotLeftBtn, &QPushButton::clicked, dlg, [=, &rotationAngle]() {
            rotationAngle -= 90;
            updateImage();
        });
        connect(rotRightBtn, &QPushButton::clicked, dlg, [=, &rotationAngle]() {
            rotationAngle += 90;
            updateImage();
        });

        // 7. 布局：先控制栏，再滚动区，最后关闭按钮
        QHBoxLayout *ctrlLayout = new QHBoxLayout;
        ctrlLayout->addWidget(zoomInBtn);
        ctrlLayout->addWidget(zoomOutBtn);
        ctrlLayout->addWidget(rotLeftBtn);
        ctrlLayout->addWidget(rotRightBtn);
        ctrlLayout->addStretch();

        QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Close);
        connect(buttons, &QDialogButtonBox::rejected, dlg, &QDialog::accept);

        QVBoxLayout *vLayout = new QVBoxLayout(dlg);
        vLayout->addLayout(ctrlLayout);
        vLayout->addWidget(scroll);
        vLayout->addWidget(buttons);

        // 8. 初次显示完整尺寸
        updateImage();

        // 9. 最大化打开
        dlg->showMaximized();
        dlg->exec();
    }

private:
    int m_recordID;
    RecordType m_recordType;

    // UserEvents 对应的控件
    QLineEdit *m_eventTitleEdit = nullptr;
    QTextEdit *m_eventDescriptionEdit = nullptr;
    QDateTimeEdit *m_eventDateEdit = nullptr;
    QLineEdit *m_eventLocationEdit = nullptr;
    QLineEdit *m_eventCategoryEdit = nullptr;
    QLabel *m_createdAtLabel = nullptr;

    // ToDoTasks 对应的控件
    QLineEdit *m_taskDescriptionEdit = nullptr;
    QDateTimeEdit *m_dueDateEdit = nullptr;
    QLineEdit *m_priorityEdit = nullptr;
    QCheckBox *m_isCompletedCheck = nullptr;
    QLabel *m_taskCreatedAtLabel = nullptr;

    // 底部按钮
    QPushButton *m_saveButton = nullptr;
    QPushButton *m_deleteButton = nullptr;
    QPushButton *m_cancelButton = nullptr;

    // —— 新增图片相关控件 ——
   QGraphicsView   *m_view;
   QGraphicsScene  *m_scene;
   QWidget         *m_contentWidget;
   QVBoxLayout     *m_contentLayout;
   QHBoxLayout     *m_thumbnailLayout;
   QPushButton     *m_addImageBtn;
   QSlider         *m_zoomSlider;
   QPushButton *m_pickColorBtn;
   QColor m_selectedColor;
   QPushButton *m_setCardColorBtn;   // 按钮：设置主页面卡片颜色
   QColor       m_customCardColor;    // 记录自定义卡片颜色
};

// 在 WeekViewWidget.h 中：
// --- 新增一个自定义卡片类 ---
// 在 WeekViewWidget.h 中：
// --- 新增一个自定义卡片类 ---
class RecordCard : public QFrame {
    Q_OBJECT
public:
    enum Type { Task, Event };

    RecordCard(int recordID,
                   Type type,
                   const QString &timeText,
                   const QString &title,
                   const QString &detailInfo = QString(),
                   QWidget *parent = nullptr)
            : QFrame(parent),
              m_recordID(recordID),
              m_type(type){
        setObjectName("recordCard");
        setFrameShape(QFrame::Box);
        setFrameShadow(QFrame::Raised);
        setLineWidth(1);
        setMidLineWidth(0);
        setCursor(Qt::PointingHandCursor);

        // 布局
        auto *h = new QHBoxLayout(this);
        // 左侧图标
        m_icon = new QLabel(this);
        m_icon->setFixedSize(24,24);
        m_icon->setPixmap(m_type==Task
            ? QPixmap(":/icons/task.svg").scaled(24,24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
            : QPixmap(":/icons/event.svg").scaled(24,24, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
        h->addWidget(m_icon);

        // 中间文字：时间+标题
        auto *v = new QVBoxLayout;
        m_timeLabel = new QLabel(timeText, this);
        m_timeLabel->setObjectName("timeLabel");
        m_titleLabel = new QLabel(title, this);
        m_titleLabel->setObjectName("titleLabel");
        v->addWidget(m_timeLabel);
        v->addWidget(m_titleLabel);
        // 如果有 detailInfo，就多加一行
        if (!detailInfo.isEmpty()) {
            m_detailLabel = new QLabel(detailInfo, this);
            m_detailLabel->setObjectName("detailLabel");
            // 样式可自行调整
            m_detailLabel->setStyleSheet("color:#555; font-size:12px;");
            v->addWidget(m_detailLabel);
        }
        h->addLayout(v);
        h->addStretch();

        // 设置默认背景色
        if (m_type == Task)         setStyleSheet("QFrame#recordCard{ background:#E3F2FD; border-radius:4px; }");
        else /*Event*/              setStyleSheet("QFrame#recordCard{ background:#FFF3E0; border-radius:4px; }");

        // 点击时间或标题时，弹出文件选择
        m_timeLabel->installEventFilter(this);
        m_titleLabel->installEventFilter(this);
    }

signals:
    void requestSetImage(int id, RecordCard::Type type);
     void activated(int recordID, RecordType type);

protected:
    bool eventFilter(QObject *watched, QEvent *ev) override {
        if (ev->type()==QEvent::MouseButtonRelease) {
            if (watched==m_timeLabel || watched==m_titleLabel) {
                emit requestSetImage(m_id, m_type);
                return true;
            }
        }
        return QFrame::eventFilter(watched, ev);
    }

    void mousePressEvent(QMouseEvent *event) override {
            QFrame::mousePressEvent(event);
            emit activated(m_recordID, static_cast<RecordType>(m_type));
        }

private:
    int m_id;
    Type m_type;
    QLabel *m_icon;
    QLabel *m_timeLabel;
    QLabel *m_titleLabel;
    int   m_recordID;
    QLabel *m_detailLabel;  // 新增
    //Type   m_type;
};



// WeekViewWidget 用于展示一周的任务与事件，按照时间段分组
class WeekViewWidget : public QWidget {
    Q_OBJECT
public:
    explicit WeekViewWidget(QWidget *parent = nullptr)
        : QWidget(parent), m_currentWeekStart(getWeekStart(QDate::currentDate()))
    {
        setupUI();
        updateWeekView();
    }

private:
    QDate m_currentWeekStart; // 本周起始日期（假定以星期一为一周第一天）
    QLabel *weekLabel;
    QPushButton *prevWeekButton;
    QPushButton *nextWeekButton;
    QHBoxLayout *daysLayout; // 存放7个天的视图
    QPushButton *otherButton; // 其他功能按钮
    QPushButton *refreshButton; // 刷新按钮
    QList<Event> m_eventList;//创建事件管理
    QPushButton *reminderButton;

    // 新增：显示当前详细时间并支持修改
    QDateTimeEdit *dateTimeEdit;

    // 存放每天的视图，每个视图由一个 QWidget 构成：标题（日期）、任务/事件列表（QTreeWidget）和“+”按钮
    //QList<QWidget*> dayWidgets; 还原

    QList<QPair<QLabel*, QVBoxLayout*>> dayWidgets;

    // 返回给定日期所在周的星期一
    QDate getWeekStart(const QDate &date) {
        int dayOfWeek = date.dayOfWeek(); // 1=Monday, 7=Sunday
        return date.addDays(1 - dayOfWeek);
    }

    // 初始化页面 UI
    void setupUI() {

        //**********************************
        // 在 setupUI() 开头替换 this 布局为一个 QFrame 容器
        auto *outerFrame = new QFrame(this);
        outerFrame->setObjectName("mainContainer");
        outerFrame->setContentsMargins(0,0,0,0);
        outerFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

        // 圆角白底 + 半透
        outerFrame->setStyleSheet(R"(
            QFrame#mainContainer {
                background: transparent;  /* 完全透明 */
                border: none;             /* 如果也不想要边框的话 */
            }
        )");


        // 投影效果
        auto *shadow = new QGraphicsDropShadowEffect(outerFrame);
        shadow->setBlurRadius(24);
        shadow->setOffset(0, 4);
        shadow->setColor(QColor(0,0,0,80));
        outerFrame->setGraphicsEffect(shadow);

        auto *mainLayout = new QVBoxLayout(outerFrame);
        mainLayout->setContentsMargins(20,20,20,20);

        //***********************************

        //QVBoxLayout *mainLayout = new QVBoxLayout(this);

        // 顶部导航：上一周、显示当前周日期范围、下一周
        QHBoxLayout *navLayout = new QHBoxLayout();
        prevWeekButton = new QPushButton("<< 上一周", this);
        nextWeekButton = new QPushButton("下一周 >>", this);
        otherButton = new QPushButton("其他", this);
        refreshButton = new QPushButton("刷新", this); // 刷新按钮
        weekLabel = new QLabel(this);

        //*****************************************************
        // 新增：QDateTimeEdit 用于显示并修改当前详细时间
        dateTimeEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
        dateTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm:ss");
        dateTimeEdit->setCalendarPopup(true);
        // 当用户修改时间时，可调用槽函数进行相关操作（例如更新其他部件的时间显示）
        connect(dateTimeEdit, &QDateTimeEdit::dateTimeChanged, this, &WeekViewWidget::onDateTimeChanged);

        // 新增：提醒按钮 —— 点击后打开 ReminderScheduler
        reminderButton = new QPushButton("提醒", this);
        connect(reminderButton, &QPushButton::clicked, this, &WeekViewWidget::showReminderDialog);

        //*****************************************************

        navLayout->addWidget(prevWeekButton);
        navLayout->addStretch();
        navLayout->addWidget(weekLabel);
        navLayout->addStretch();
        navLayout->addWidget(refreshButton); // 添加刷新按钮
        navLayout->addWidget(nextWeekButton);
        navLayout->addWidget(otherButton);

        //******************************
        navLayout->addSpacing(20);
        navLayout->addWidget(new QLabel("当前时间:", this));
        navLayout->addWidget(dateTimeEdit);
        //*************************************
        navLayout->addSpacing(20);
        navLayout->addWidget(reminderButton);  // 添加提醒按钮
        //******************************

        connect(otherButton, &QPushButton::clicked, this, &WeekViewWidget::openOtherFunctions);

        connect(prevWeekButton, &QPushButton::clicked, this, &WeekViewWidget::onPrevWeek);
        connect(nextWeekButton, &QPushButton::clicked, this, &WeekViewWidget::onNextWeek);
        connect(refreshButton, &QPushButton::clicked, this, &WeekViewWidget::updateWeekView); // 绑定刷新功能


        mainLayout->addLayout(navLayout);

        // 存放7天视图的横向布局
        daysLayout = new QHBoxLayout();

        for (int i = 0; i < 7; ++i) {
                QWidget *dayWidget = new QWidget(this);
                QVBoxLayout *dayLayout = new QVBoxLayout(dayWidget);
                QLabel *dateLabel = new QLabel(dayWidget);
                dateLabel->setObjectName("dateLabel");
                dateLabel->setAlignment(Qt::AlignCenter);
                dayLayout->addWidget(dateLabel);


                QScrollArea *scroll = new QScrollArea(dayWidget);
                scroll->setWidgetResizable(true);
                QWidget *container = new QWidget;

                //------------------------------------------------
                // container->setStyleSheet(R"(
                //         QWidget{
                //             background-color(255,255,255,0.5);
                //             border: 1px solid rgba(255,255,255,0.4);
                //             border-radius: 5px;
                //         })");
                //-------------------------------------------------
                auto *vbox = new QVBoxLayout(container);
                vbox->setSpacing(6);
                scroll->setWidget(container);

                // “+”按钮（后续扩展添加任务/事件功能）
                QPushButton *addButton = new QPushButton("+", dayWidget);
                dayLayout->addWidget(addButton);
                //dayWidget->setLayout(dayLayout);//**********************
                QDate currentDate = m_currentWeekStart.addDays(i);

                // 连接“+”按钮：点击后弹出 EventDialog，录入事件信息
                connect(addButton, &QPushButton::clicked, this, [this, currentDate]() {
                    // 弹出事件录入对话框，传入当前日期（可以设置默认时间等）
                    EventDialog dialog(currentDate, this);
                    if (dialog.exec() == QDialog::Accepted) {

                        QSqlQuery query;
                        // 注意：如果 TaskID 为非自增，请使用下面方式自动生成 EventID，否则可省略 EventID 字段
                        if (!query.exec("SELECT ISNULL(MAX(EventID), 0) + 1 FROM UserEvents")) {
                            qDebug() << "获取新 EventID 失败:" << query.lastError().text();
                            return;
                        }
                        query.next();
                        int newEventID = query.value(0).toInt();

                        // 获取用户输入的事件信息
                        Event event;
                        event.Eventid = newEventID;
                        event.title = dialog.getTitle();
                        event.description = dialog.getDescription();
                        event.eventDate = dialog.getEventDate();
                        event.category = dialog.getCategory();
                        event.location = dialog.getlocation();
                        // 将事件添加到事件列表中
                        m_eventList.append(event);


                        // 插入 UserEvents 表
                        query.prepare("INSERT INTO UserEvents (EventID, UserID, EventTitle, EventDescription, EventDate, EventLocation, Category, CreatedAt) "
                                      "VALUES (:EventID, :UserID, :EventTitle, :EventDescription, :EventDate, :EventLocation, :Category, GETDATE())");
                        query.bindValue(":EventID", newEventID);
                        query.bindValue(":UserID", 1);  // 假定当前用户ID为1，根据实际情况修改
                        query.bindValue(":EventTitle", event.title);
                        query.bindValue(":EventDescription", event.description);
                        query.bindValue(":EventDate", event.eventDate);
                        query.bindValue(":EventLocation", event.location);
                        query.bindValue(":Category", event.category);  // 如有类别信息，可修改

                        if (!query.exec()) {
                            qDebug() << "插入 UserEvents 失败:" << query.lastError().text();
                        }

                }
                });
                dayLayout->addWidget(scroll);
                dayWidgets.append(qMakePair(dateLabel, vbox));
                daysLayout->addWidget(dayWidget);
            }

        //ui设计
        // 先用一个 QFrame 包裹 daysLayout
        auto *daysContainer = new QFrame(outerFrame);/* 或者 this，如果你去掉了 outerFrame */
        daysContainer->setObjectName("daysContainer");
        daysContainer->setFrameShape(QFrame::NoFrame);

        // 给容器留点内边距
        auto *daysContainerLayout = new QHBoxLayout(daysContainer);
        daysContainerLayout->setContentsMargins(12, 12, 12, 12);
        daysContainerLayout->setSpacing(20);             // 列间距
        daysContainerLayout->addLayout(daysLayout);

        // 把这个容器加到主布局
        mainLayout->addWidget(daysContainer);

        //mainLayout->addLayout(daysLayout);
        setLayout(mainLayout);

        //界面优化
        this->setObjectName("WeekViewWidget");
        prevWeekButton->setObjectName("prevWeekButton");
        nextWeekButton->setObjectName("nextWeekButton");
        otherButton->setObjectName("otherButton");
        refreshButton->setObjectName("refreshButton");
        reminderButton->setObjectName("reminderButton");
        // 如果 you want 给“+”按钮也单独样式化：
        for (int i = 0; i < daysLayout->count(); ++i) {
            QWidget *dayW = daysLayout->itemAt(i)->widget();
            if (auto btn = dayW->findChild<QPushButton *>()) {
                btn->setObjectName("addButton");
            }
        }

        QString style = R"(
        /* 一周视图背景：淡紫到天蓝的温柔渐变 */
        QWidget#WeekViewWidget {
            background: qlineargradient(
                x1: 0, y1: 0, x2: 1, y2: 1,
                stop: 0 #CE93D8,    /* 淡紫 */
                stop: 1 #81D4FA     /* 天蓝 */
            );
        }

        /* 通用按钮圆角：12px，内边距加大，字体加粗 */
        QPushButton {
            border-radius: 12px;
            padding: 8px 16px;
            font-weight: 600;
            transition: background-color 150ms ease;
        }

        /* 导航按钮（上一周/下一周）——粉嫩配色 */
        QPushButton#prevWeekButton, QPushButton#nextWeekButton {
            background-color: #F48FB1;  /* 粉色 */
            color: white;
        }

        /* 其他操作按钮（“其他”/“刷新”/“提醒”）——橙调活力 */
        QPushButton#otherButton, QPushButton#refreshButton, QPushButton#reminderButton {
            background-color: #FF8A65;  /* 橙色 */
            color: white;
        }

        /* “+” 添加按钮——清新绿 */
        QPushButton#addButton {
            background-color: #AED581;  /* 浅绿 */
            color: white;
            min-width: 32px;
            min-height: 32px;
            font-size: 18px;
            font-weight: bold;
        }

        /* 悬停与按下状态微调 */
        QPushButton:hover {
            background-color: rgba(255,255,255,0.15);
        }
        QPushButton:pressed {
            background-color: rgba(0,0,0,0.1);
        }

        /* 时间编辑器边框圆角 + 取色 */
        QDateTimeEdit {
            border: 2px solid #4FC3F7;   /* 浅天蓝 */
            border-radius: 8px;
            padding: 4px 8px;
            background: white;
        }

        /* 天数标签高亮时不用改动，这里保持已有逻辑 */

        /* 7 天视图容器背景：微透白 + 横向渐变 + 中心透光 */
        QFrame#daysContainer {
            background:
                /* 底层：横向轻微渐变 */
                qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0   rgba(255,255,255,0.20),
                    stop:0.5 rgba(255,255,255,0.12),
                    stop:1   rgba(255,255,255,0.20)
                ),
                /* 叠层：中心径向高光 */
                qradialgradient(cx:0.5, cy:0.5, radius:1.0,
                    fx:0.5, fy:0.5,
                    stop:0   rgba(255,255,255,0.25),
                    stop:1   transparent
                );
            border: 1px solid rgba(255,255,255,0.4);
            border-radius: 16px;
        }
        )";
        this->setStyleSheet(style);
        //********************************************
        // 最后把 outerFrame 加到 this 上
        auto *wrapper = new QVBoxLayout(this);
        wrapper->setContentsMargins(40,40,40,40);   // 再留点边距
        wrapper->addWidget(outerFrame);

        // 同时把外面 wrapper 的边距去掉或调小：
        wrapper->setContentsMargins(0, 0, 0, 0);
        setLayout(wrapper);


    }

    // 根据 m_currentWeekStart 更新界面显示内容
    void updateWeekView() {
        QDate highlightedDate = dateTimeEdit->date();

            // 更新顶部周范围
            QDate weekEnd = m_currentWeekStart.addDays(6);
            weekLabel->setText(QString("%1 - %2")
                               .arg(m_currentWeekStart.toString("yyyy-MM-dd"))
                               .arg(weekEnd.toString("yyyy-MM-dd")));


        // 对每一天进行更新
        for (int i = 0; i < 7; ++i) {
                const QDate date = m_currentWeekStart.addDays(i);
                auto [dateLabel, listLayout] = dayWidgets[i];

                QWidget *dayWidget = dateLabel->parentWidget();

                // 1. 更新日期文字
                dateLabel->setText(date.toString("ddd\nyyyy‑MM‑dd"));

                // 2. 先清除上次的高亮样式
                dateLabel->setStyleSheet("");
                dayWidget  ->setStyleSheet("");
                dayWidget  ->setGraphicsEffect(nullptr);



                // 3. 如果是“当前详细时间”所在的日期，就加高亮
                if (date == highlightedDate) {
                    // —— 你可以任选下面两种效果之一 —— //

                    // 方案 A：仅给标签加背景色
                    dateLabel->setStyleSheet(R"(
                        background-color: #FFEB3B;
                        color: #212121;
                        font-weight: bold;
                        border-radius: 6px;
                        padding: 4px;
                    )");

                    // 方案 B：给整列加渐变 + 边框
                    dayWidget->setStyleSheet(R"(
                        background-color: qlineargradient(
                            x1:0, y1:0, x2:0, y2:1,
                            stop:0 #FFF9C4, stop:1 #FFECB3
                        );
                        border: 2px solid #FFC107;
                        border-radius: 8px;
                    )");
                }
                //---------------------------------------------
                // else{
                //     dayWidget->setStyleSheet(R"(
                //         QWidget{

                //             border-radius: 10px;
                //             border: 2px solid #333;
                //         })");
                // }
                //-----------------------------------------------


                dateLabel->setText(date.toString("ddd\nyyyy-MM-dd"));
                // 清空旧卡片
                QLayoutItem *child;
                while ((child = listLayout->takeAt(0))) {
                    delete child->widget();
                    delete child;
                }
                // 查询任务
                QSqlQuery q1;
                q1.exec(QString(
                    "SELECT TaskID, "
                    "       CONVERT(varchar(5), DueDate, 108) AS t, "
                    "       TaskDescription, "
                    "       Priority, "
                    "       IsCompleted "
                    "FROM ToDoTasks "
                    "WHERE CONVERT(date, DueDate)='%1'")
                    .arg(date.toString("yyyy-MM-dd"))
                );
                while (q1.next()) {
                    int    id         = q1.value("TaskID").toInt();
                    QString t         = q1.value("t").toString();
                    QString desc      = q1.value("TaskDescription").toString();
                    int    priority   = q1.value("Priority").toInt();
                    bool   completed  = q1.value("IsCompleted").toBool();

                    // 组装 extra detail 字符串
                    QString detail = QString("优先级: %1   %2")
                                     .arg(priority)
                                     .arg(completed ? "已完成" : "未完成");

                    auto *card = new RecordCard(
                        id,
                        RecordCard::Task,
                        t,
                        desc,
                        detail,       // 传入 detailInfo
                        this
                    );

                    QSqlQuery mq;
                    mq.prepare("SELECT BackgroundColor FROM RecordCustomColors WHERE RecordType=? AND RecordID=?");
                    mq.addBindValue("Task");
                    mq.addBindValue(id);
                    if (mq.exec() && mq.next()) {
                        QString bg = mq.value(0).toString();
                        card->setStyleSheet(
                            QString("QFrame#recordCard{ background:%1; border-radius:4px; }").arg(bg)
                        );
                    }


                    listLayout->addWidget(card);
                    connect(card, &RecordCard::activated, this, [=](int recordID, RecordType type){
                        TaskDetailDialog dlg(recordID, type, this);
                        dlg.exec();
                    });
                }
                // 查询事件
                QSqlQuery q2;
                q2.exec(QString(
                    "SELECT EventID, "
                    "       CONVERT(varchar(5), EventDate, 108) AS t, "
                    "       EventTitle, "
                    "       EventLocation, "
                    "       Category "
                    "FROM UserEvents "
                    "WHERE CONVERT(date, EventDate)='%1'")
                    .arg(date.toString("yyyy-MM-dd"))
                );
                while (q2.next()) {
                    int    id        = q2.value("EventID").toInt();
                    QString t        = q2.value("t").toString();
                    QString title    = q2.value("EventTitle").toString();
                    QString location = q2.value("EventLocation").toString();
                    QString category = q2.value("Category").toString();

                    // 只在有值时拼接
                    QString detail;
                    if (!location.isEmpty())
                        detail += QString("地点: %1").arg(location);
                    if (!category.isEmpty()) {
                        if (!detail.isEmpty()) detail += "   ";
                        detail += QString("类别: %1").arg(category);
                    }

                    auto *card = new RecordCard(
                        id,
                        RecordCard::Event,
                        t,
                        title,
                        detail,      // 传入 detailInfo（可能为空）
                        this
                    );

                    QSqlQuery mq;
                    mq.prepare("SELECT BackgroundColor FROM RecordCustomColors WHERE RecordType=? AND RecordID=?");
                    mq.addBindValue("Event");
                    mq.addBindValue(id);
                    if (mq.exec() && mq.next()) {
                        QString bg = mq.value(0).toString();
                        card->setStyleSheet(
                            QString("QFrame#recordCard{ background:%1; border-radius:4px; }").arg(bg)
                        );
                    }

                    listLayout->addWidget(card);
                    connect(card, &RecordCard::activated, this, [=](int recordID, RecordType type){
                        TaskDetailDialog dlg(recordID, type, this);
                        dlg.exec();
                    });
                }
                listLayout->addStretch();
            }

    }

    void paintEvent(QPaintEvent *event) {
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing);

        // —— 1. 大面积背景渐变 ——
        QLinearGradient bgGrad(0, 0, width(), height());
        bgGrad.setColorAt(0, QColor("#CE93D8"));
        bgGrad.setColorAt(1, QColor("#81D4FA"));
        p.fillRect(rect(), bgGrad);

        // —— 2. 半透明大圆 ——
        p.setPen(Qt::NoPen);
        QColor c1(255, 255, 255, 30);
        p.setBrush(c1);
        p.drawEllipse(QPointF(width()*0.3, height()*0.2), width()*0.6, width()*0.6);

        // —— 3. 半透明小圆 ——
        QColor c2(255, 255, 255, 20);
        p.setBrush(c2);
        p.drawEllipse(QPointF(width()*0.75, height()*0.8), width()*0.5, width()*0.5);

        // —— 4. 底部波浪曲线装饰 ——
        QPainterPath wave;
        const int h = height();
        wave.moveTo(0, h * 0.85);
        wave.cubicTo(width()*0.25, h*0.7, width()*0.75, h*1.0, width(), h*0.85);
        wave.lineTo(width(), h);
        wave.lineTo(0, h);
        wave.closeSubpath();
        QColor waveColor(255,255,255, 40);
        p.setBrush(waveColor);
        p.drawPath(wave);

        // 保持父类绘制其余控件
        QWidget::paintEvent(event);
    }


    // 点击“提醒”按钮时，弹出提醒设置对话框
    void showReminderDialog() {
           QDialog *dialog = new QDialog(this);
           dialog->setWindowTitle("提醒设置");
           dialog->setModal(false);
           QVBoxLayout *dLayout = new QVBoxLayout(dialog);

           // 设置提醒时间的编辑控件（默认设为当前时间后一小时）
           QDateTimeEdit *timeEdit = new QDateTimeEdit(QDateTime::currentDateTime().addSecs(3600), dialog);
           timeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
           timeEdit->setCalendarPopup(true);

           // 输入提醒内容
           QLineEdit *messageEdit = new QLineEdit(dialog);
           messageEdit->setPlaceholderText("请输入提醒内容");

           // 添加提醒按钮
           QPushButton *addBtn = new QPushButton("添加提醒", dialog);
           // 删除提醒按钮
           QPushButton *delBtn = new QPushButton("删除选中", dialog);

           // 表格用于显示已添加的提醒
           QTableWidget *table = new QTableWidget(dialog);
           table->setColumnCount(2);
           table->setHorizontalHeaderLabels(QStringList() << "时间" << "内容");
           table->horizontalHeader()->setStretchLastSection(true);
           table->setSelectionBehavior(QAbstractItemView::SelectRows);

           // 将各控件添加到对话框中
           QHBoxLayout *inputLayout = new QHBoxLayout;
           inputLayout->addWidget(timeEdit);
           inputLayout->addWidget(messageEdit);
           inputLayout->addWidget(addBtn);
           dLayout->addLayout(inputLayout);
           dLayout->addWidget(table);
           dLayout->addWidget(delBtn);

           // 刷新表格：从数据库中查询当前启用的提醒信息
           auto refreshReminderTable = [=]() {
               table->clearContents();
               QSqlQuery query;
               // 查询 Reminders 与 UserEvents 联表以获取提醒时间和提醒内容（假设当前用户 UserID=1）
               QString sql = "SELECT R.ReminderID, R.ReminderTime, UE.EventTitle FROM Reminders R JOIN UserEvents UE ON R.EventID = UE.EventID "
                             "WHERE R.IsActive = 1 AND UE.UserID = 1 ORDER BY R.ReminderTime";
               if (!query.exec(sql)) {
                   qDebug() << "查询提醒数据错误:" << query.lastError().text();
                   return;
               }
               int row = 0;
               table->setRowCount(0);
               while (query.next()) {
                   table->insertRow(row);
                   QDateTime rTime = query.value("ReminderTime").toDateTime();
                   QString title = query.value("EventTitle").toString();
                   // 将 ReminderID 存入第一列项的 UserRole 中，便于删除操作使用
                   QTableWidgetItem *timeItem = new QTableWidgetItem(rTime.toString("yyyy-MM-dd HH:mm"));
                   timeItem->setData(Qt::UserRole, query.value("ReminderID"));
                   QTableWidgetItem *titleItem = new QTableWidgetItem(title);
                   table->setItem(row, 0, timeItem);
                   table->setItem(row, 1, titleItem);
                   ++row;
               }
           };

           // 初次刷新表格
           refreshReminderTable();

           // 定时器：每秒检查数据库中是否有到时的提醒
           // 定时器：每秒检测数据库中是否有到时提醒，并刷新表格（增加检查表格焦点状态，防止刷新导致用户选中状态被清除）
           QTimer *checkTimer = new QTimer(dialog);
           checkTimer->start(1000);
           connect(checkTimer, &QTimer::timeout, dialog, [=]() {
               // 如果用户正在操作表格（表格获得焦点），则不执行刷新和检查提醒的操作
               if (table->hasFocus())
                   return;

               // 查询数据库中到时的提醒记录
               QSqlQuery checkQuery;
               QString checkSql = "SELECT R.ReminderID, R.ReminderTime, UE.EventTitle "
                                  "FROM Reminders R JOIN UserEvents UE ON R.EventID = UE.EventID "
                                  "WHERE R.IsActive = 1 AND R.ReminderTime <= GETDATE() AND UE.UserID = 1";
               if (!checkQuery.exec(checkSql)) {
                   qDebug() << "检查提醒错误:" << checkQuery.lastError().text();
                   return;
               }
               while (checkQuery.next()) {
                   int remID = checkQuery.value("ReminderID").toInt();
                   QDateTime rTime = checkQuery.value("ReminderTime").toDateTime();
                   QString title = checkQuery.value("EventTitle").toString();
                   // 弹窗提示该提醒信息
                   QMessageBox::information(dialog, "提醒",
                       QString("时间：%1\n内容：%2").arg(rTime.toString("yyyy-MM-dd HH:mm")).arg(title));
                   // 标记该提醒为已处理（或禁用提醒）
                   QSqlQuery updateQuery;
                   updateQuery.prepare("UPDATE Reminders SET IsActive = 0 WHERE ReminderID = :rid");
                   updateQuery.bindValue(":rid", remID);
                   if (!updateQuery.exec())
                       qDebug() << "更新提醒状态失败:" << updateQuery.lastError().text();
               }
               // 刷新表格显示（只有当表格没有焦点时才会执行刷新）
               refreshReminderTable();
           });

           // 添加提醒按钮槽：将提醒信息存入数据库
           connect(addBtn, &QPushButton::clicked, dialog, [=]() {
               if (messageEdit->text().isEmpty()) {
                   QMessageBox::warning(dialog, "错误", "请输入提醒内容");
                   return;
               }
               QDateTime rTime = timeEdit->dateTime();
               if (rTime <= QDateTime::currentDateTime()) {
                   QMessageBox::warning(dialog, "错误", "请选择未来的时间");
                   return;
               }

               // 先在 UserEvents 表中插入提醒事件
               QSqlQuery query;
               if (!query.exec("SELECT ISNULL(MAX(EventID), 0) + 1 FROM UserEvents")) {
                   qDebug() << "获取新 EventID 失败:" << query.lastError().text();
                   return;
               }
               query.next();
               int newEventID = query.value(0).toInt();
               query.prepare("INSERT INTO UserEvents (EventID, UserID, EventTitle, EventDescription, EventDate, EventLocation, Category, CreatedAt) "
                             "VALUES (:EventID, :UserID, :EventTitle, :EventDescription, :EventDate, '', '', GETDATE())");
               query.bindValue(":EventID", newEventID);
               query.bindValue(":UserID", 1);  // 假定当前用户为1
               query.bindValue(":EventTitle", messageEdit->text());
               query.bindValue(":EventDescription", "提醒事件");
               query.bindValue(":EventDate", rTime);
               if (!query.exec()) {
                   qDebug() << "插入 UserEvents 失败:" << query.lastError().text();
                   return;
               }

               // 再在 Reminders 表中插入提醒记录
               if (!query.exec("SELECT ISNULL(MAX(ReminderID), 0) + 1 FROM Reminders")) {
                   qDebug() << "获取新 ReminderID 失败:" << query.lastError().text();
                   return;
               }
               query.next();
               int newReminderID = query.value(0).toInt();
               query.prepare("INSERT INTO Reminders (ReminderID, EventID, ReminderTime, ReminderMethod, IsActive, CreatedAt) "
                             "VALUES (:ReminderID, :EventID, :ReminderTime, :ReminderMethod, 1, GETDATE())");
               query.bindValue(":ReminderID", newReminderID);
               query.bindValue(":EventID", newEventID);
               query.bindValue(":ReminderTime", rTime);
               query.bindValue(":ReminderMethod", "APP");
               if (!query.exec()) {
                   qDebug() << "插入 Reminders 失败:" << query.lastError().text();
                   return;
               }
               QMessageBox::information(dialog, "提示", "提醒添加成功！");
               refreshReminderTable();
               messageEdit->clear();
           });

           // 删除提醒按钮槽：删除数据库中对应的提醒记录
           connect(delBtn, &QPushButton::clicked, dialog, [=]() {
               int row = table->currentRow();
               if (row < 0) return;
               // 通过第一列中存储的 ReminderID 获取数据
               QVariant ridVar = table->item(row, 0)->data(Qt::UserRole);
               if (!ridVar.isValid()) return;
               int remID = ridVar.toInt();
               QSqlQuery query;
               query.prepare("DELETE FROM Reminders WHERE ReminderID = :rid");
               query.bindValue(":rid", remID);
               if (!query.exec()) {
                   qDebug() << "删除提醒失败:" << query.lastError().text();
               } else {
                   QMessageBox::information(dialog, "提示", "删除提醒成功！");
               }
               refreshReminderTable();
           });

           dialog->resize(500, 300);
           dialog->show();


           //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
           dialog->setStyleSheet(R"(
                    QDialog {
                        background: qlineargradient(x1:0, y1:1, x2:0, y2:0, stop:0 #D9AFD9, stop:1 #97D9E1);
                    }

                    QDialog QPushButton {
                        background-color: #D9AFD9;   /* 正常状态：浅紫色 */ !important
                        border: 1px solid #cccccc;
                        padding: 5px;
                        color: #333333;
                        border-radius: 5px;
                            }
                   QDialog QPushButton:hover {
                        background-color: #C99FC9;  /* 悬浮状态：稍深紫色 */
                            }
                    QDialog QPushButton:pressed {
                        background-color: #B98FB9;  /* 点击状态：更深紫色 */
                            }
            )");
           //⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️⚠️
       }


private slots:
    void onPrevWeek() {
        m_currentWeekStart = m_currentWeekStart.addDays(-7);
        updateWeekView();
    }

    void onNextWeek() {
        m_currentWeekStart = m_currentWeekStart.addDays(7);
        updateWeekView();
    }
    void openOtherFunctions() {//新加

        //this->hide(); // 隐藏主窗口
        QWidget *mainWindow = this->window(); // 获取主窗口（顶层窗口）
        if (mainWindow) {
            mainWindow->hide(); // 隐藏整个主窗口（包括框架）
        }

        OtherFunctionsWidget *widget = new OtherFunctionsWidget(nullptr); // 让它成为独立窗口
        widget->setAttribute(Qt::WA_DeleteOnClose);
        widget->resize(800, 600); // 适当调整窗口大小
        widget->show();

        /*connect(widget, &OtherFunctionsWidget::returnToMain, this, [=]() {
                this->show(); // 重新显示主窗口
                widget->close(); // 关闭 OtherFunctionsWidget
            });*/
        connect(widget, &OtherFunctionsWidget::returnToMain, this, [=]() {
                if (mainWindow) {
                    mainWindow->show(); // 重新显示主窗口（包括框架）
                }
                widget->close(); // 关闭 OtherFunctionsWidget
            });
    }
    void onTaskClicked(QTreeWidgetItem *item, int column) {
        // 如果该项没有父项，说明它是顶层项，不是任务数据，直接返回
        if (!item->parent()) {
            qDebug() << "点击的是分组项，不是任务数据";
            return;
        }
        // 获取存储在 UserRole 中的 TaskID，如果没有则返回0
        int recordID = item->data(0, Qt::UserRole).toInt();
        int recType = item->data(0, Qt::UserRole + 1).toInt();
        if(recordID == 0) {
            qDebug() << "该项没有有效的记录ID";
            return;
        }
        //TaskDetailDialog *dialog = new TaskDetailDialog(recordID, ToDoTask, this);
        TaskDetailDialog *dialog = new TaskDetailDialog(recordID, RecordType(recType), this);
        dialog->exec();
    }

    // 当用户修改 QDateTimeEdit 时调用的槽函数
    void onDateTimeChanged(const QDateTime &newDateTime) {
        // 示例操作：打印新时间，实际中可以做同步更新
        qDebug() << "当前详细时间被修改为:" << newDateTime.toString("yyyy-MM-dd HH:mm:ss");
        // 如果需要，也可以更新 m_currentWeekStart，例如调整为 newDateTime 所在周的第一天
        m_currentWeekStart = getWeekStart(newDateTime.date());
        updateWeekView();
    }



};



// 主窗口，设置 WeekViewWidget 为中心窗口
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr): QMainWindow(parent) {


        //****************
        WeekViewWidget *weekView = new WeekViewWidget(this);
        setCentralWidget(weekView);
        setWindowTitle("大学生时间管理系统");

        resize(1200, 600);


    }
private slots:

};

#include "main.moc"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    // 连接数据库（使用 QODBC 驱动连接 SQL Server 数据库）
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("DRIVER={SQL Server};SERVER=localhost;DATABASE=TimeManagement;UID=sa;PWD=123123;");
    if(!db.open()){
         qDebug() << "无法连接数据库:" << db.lastError().text();
         return -1;
    }
    /*
    //显示图表、表格
    AnalysisReportWidget reportWidget;
    reportWidget.resize(800, 600);
    reportWidget.show();

    // 显示报告组件
    ReportWidget report;
    report.resize(600, 400);
    report.show();
    */

    app.setWindowIcon(QIcon("C:\\Users\\Administrator\\Desktop\\SQLtest\\TimeManagementSystem\\TimeManagementSystem\\229155190229177130-1.ico"));
    //显示主页面
    MainWindow mainWindow;
    mainWindow.show();

    //添加功能高亮显示当天

    return app.exec();


}

