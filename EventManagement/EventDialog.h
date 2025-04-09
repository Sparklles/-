#pragma once

#include <QDialog>
#include "ui_EventDialog.h"

class EventDialog : public QDialog
{
	Q_OBJECT

public:
	EventDialog(const QDate& selectedDate, QWidget *parent = nullptr);
	~EventDialog();
	QString getTitle() const {
		return ui.titleEdit->text();
	}

	QString getDescription() const {
		return ui.descriptionEdit->toPlainText();
	}

	QDateTime getStartTime() const {
		return ui.startTimeEdit->dateTime();
	}

	QDateTime getEndTime() const {
		return ui.endTimeEdit->dateTime();
	}
	QDateTime getreminderTime() const {
		return ui.reminderTime->dateTime();
	}
	QString getlocation() const {
		return ui.locationEdit->text();
	}

	void onAccept();
private:
	Ui::EventDialogClass ui;
};
