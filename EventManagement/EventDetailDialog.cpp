#include "EventDetailDialog.h"
#include<QMessageBox>
EventDetailDialog::EventDetailDialog(const Event& e,QWidget *parent)
	: QDialog(parent),currentEvent(e),editingEnabled(false)
{
	ui.setupUi(this);
	// 初始化控件，显示事件信息
	ui.titleEdit->setText(currentEvent.title);
	ui.descriptionEdit->setPlainText(currentEvent.description);
	ui.startTimeEdit->setDateTime(currentEvent.startTime);
	ui.endTimeEdit->setDateTime(currentEvent.finishTime);
	ui.reminderTime->setDateTime(currentEvent.reminderTime);
	ui.startTimeEdit->setCalendarPopup(true);
	ui.endTimeEdit->setCalendarPopup(true);
	ui.reminderTime->setCalendarPopup(true);
	ui.locationEdit->setText(currentEvent.location);
	// 默认只读
	setEditable(false);
	//qDebug() << "titleEdit read-only: " << ui.titleEdit->isReadOnly();
	//qDebug() << "descriptionEdit read-only: " << ui.descriptionEdit->isReadOnly();
	//qDebug() << "locationEdit read-only: " << ui.locationEdit->isReadOnly();
	// 按钮连接信号槽
	connect(ui.editButton, &QPushButton::clicked, this, &EventDetailDialog::onEditClicked);
	connect(ui.deleteButton, &QPushButton::clicked, this, &EventDetailDialog::onDeleteClicked);
	connect(ui.saveButton, &QPushButton::clicked, this, &EventDetailDialog::onSaveClicked);
	connect(ui.cancelEditButton, &QPushButton::clicked, this, &EventDetailDialog::onCancelEditClicked);
}

EventDetailDialog::~EventDetailDialog()
{}

void EventDetailDialog::onEditClicked()
{
	setEditable(true);
}

void EventDetailDialog::onDeleteClicked()
{
	// 弹出确认删除提示
	if (QMessageBox::question(this, "删除事件", "确认删除该事件？") == QMessageBox::Yes) {
		emit eventDeleted(currentEvent.id);
		accept(); // 删除后关闭对话框
	}
}

void EventDetailDialog::onSaveClicked()
{
	//检查输入是否有效，事件内容不能为空
	if (ui.descriptionEdit->toPlainText().trimmed().isEmpty()) {
		QMessageBox::warning(this, "错误", "事件内容不能为空！");
		return;
	}
	// 更新 currentEvent 信息
	currentEvent.title = ui.titleEdit->text();
	currentEvent.description = ui.descriptionEdit->toPlainText();
	currentEvent.startTime = ui.startTimeEdit->dateTime();
	currentEvent.finishTime = ui.endTimeEdit->dateTime();
	currentEvent.reminderTime = ui.reminderTime->dateTime();
	currentEvent.location = ui.locationEdit->text();
	// 发出更新信号
	emit eventUpdated(currentEvent);
	// 保存成功后恢复只读状态
	setEditable(false);
	// 可选：关闭对话框
	/*accept();*/
}

void EventDetailDialog::onCancelEditClicked()
{
	// 询问用户是否放弃未保存的更改
	if (editingEnabled && QMessageBox::question(this, "取消编辑", "您确定要放弃所有更改？") != QMessageBox::Yes) {
		return; // 用户取消放弃操作
	}
	// 恢复为原来的事件信息
	ui.titleEdit->setText(currentEvent.title);
	ui.descriptionEdit->setPlainText(currentEvent.description);
	ui.startTimeEdit->setDateTime(currentEvent.startTime);
	ui.endTimeEdit->setDateTime(currentEvent.finishTime);
	ui.reminderTime->setDateTime(currentEvent.reminderTime);
	ui.locationEdit->setText(currentEvent.location);
	// 退出编辑模式
	setEditable(false);
}

void EventDetailDialog::setEditable(bool editable)
{
	ui.titleEdit->setReadOnly(!editable);
	ui.descriptionEdit->setReadOnly(!editable);
	ui.startTimeEdit->setEnabled(editable);
	ui.endTimeEdit->setEnabled(editable);
	ui.reminderTime->setEnabled(editable);
	ui.locationEdit->setReadOnly(!editable);
	// 控制保存和退出编辑按钮，仅在编辑状态下可见
	ui.saveButton->setVisible(editable);
	ui.cancelEditButton->setVisible(editable);
	//控制 编辑 按钮，在编辑状态下不可见
	ui.editButton->setVisible(!editable);
	
	if (!editable) { // 只读模式时禁用输入焦点
		ui.titleEdit->setFocusPolicy(Qt::NoFocus);
		ui.descriptionEdit->setFocusPolicy(Qt::NoFocus);
		ui.locationEdit->setFocusPolicy(Qt::NoFocus);
	}
	else { // 编辑模式时恢复焦点
		ui.titleEdit->setFocusPolicy(Qt::StrongFocus);
		ui.descriptionEdit->setFocusPolicy(Qt::StrongFocus);
		ui.locationEdit->setFocusPolicy(Qt::StrongFocus);
	}
	editingEnabled = editable;
}
