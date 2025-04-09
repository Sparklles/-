#pragma once

#include <QDialog>
#include "ui_EventDetailDialog.h"
#include"EventStorageInterface.h"
class EventDetailDialog : public QDialog
{
	Q_OBJECT

public:
	EventDetailDialog(const Event& e,QWidget *parent = nullptr);
	~EventDetailDialog();
	void onEditClicked();
	void onDeleteClicked();
	void onSaveClicked();
	void onCancelEditClicked();
signals:
	// 事件更新、删除信号，用于通知主界面刷新
	void eventUpdated(const Event& event);
	void eventDeleted(const int& eventId);

private:
	Ui::EventDetailDialogClass ui;
	Event currentEvent;  // 当前事件数据
	bool editingEnabled; // 标记是否处于编辑状态
	void setEditable(bool editable); // 设置控件是否可编辑

};
