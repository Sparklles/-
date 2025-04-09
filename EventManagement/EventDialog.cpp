#include "EventDialog.h"
#include <QMessageBox>

EventDialog::EventDialog(const QDate& selectedDate, QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowTitle("输入事件信息");
	ui.titleEdit->setPlaceholderText("请输入事件标题");
	ui.descriptionEdit->setPlaceholderText("请输入事件描述");
	// 设置默认开始时间为当前选中日期的固定时间点（例如 09:00）
	QDateTime defaultStart(selectedDate, QTime(9, 0));
	ui.startTimeEdit->setDateTime(defaultStart);
	ui.startTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
	ui.startTimeEdit->setCalendarPopup(true);
	// 默认结束时间为开始时间加固定时长（例如2小时）
	QDateTime defaultEnd = defaultStart.addSecs(2 * 3600); // 2 小时
	ui.endTimeEdit->setDateTime(defaultEnd);
	ui.endTimeEdit->setDisplayFormat("yyyy-MM-dd HH:mm");
	ui.endTimeEdit->setCalendarPopup(true);
	//提醒时间默认为结束时间的前10分钟
	QDateTime defaultre = defaultEnd.addSecs(-10 * 60); 
	ui.reminderTime->setDateTime(defaultre);
	ui.reminderTime->setDisplayFormat("yyyy-MM-dd HH:mm");
	ui.reminderTime->setCalendarPopup(true);
	connect(ui.okButton, &QPushButton::clicked, this, &EventDialog::onAccept);
	connect(ui.cancelButton, &QPushButton::clicked, this, &EventDialog::reject);

}

EventDialog::~EventDialog()
{}

void EventDialog::onAccept()
{
	QString des = ui.descriptionEdit->toPlainText();
	if (des.isEmpty()) {
		QMessageBox::warning(this, "输入错误", "事件内容不能为空！");
		return;
	}
	accept(); //关闭对话框

}
