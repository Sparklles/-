#pragma once
#include"EventStorageInterface.h"
#include <QMainWindow>
#include "ui_EventManager.h"
#include"EventDialog.h"
#include"EventDetailDialog.h"

using namespace std;
class EventManager : public QMainWindow,public IEventStorage
{
	Q_OBJECT

public:
	EventManager(QWidget *parent = nullptr);
	~EventManager();
	// IEventStorage 接口实现
	bool addEvent(const Event& event);

    bool updateEvent(const Event& event) ;

	// 删除事件，根据事件的唯一ID删除
	bool deleteEvent(const int& eventId) ;

	//获取某一时期的所有时间
	 QList<Event> getEvents(const QDate& date) ;

	// 获取所有事件
	QList<Event> getAllEvents() ;
	void CreateButton();  //创建事件
	void loadEventsforDate(const QDate& d);  //展示选择日期的事件
	void show_event_detail(QListWidgetItem* item);  //显示事件的详细信息，同时支持编辑与删除
	int generateEventId();
private:
	Ui::EventManagerClass ui;
	// 本地存储数据，可以用内存或文件系统模拟存储
	QList<Event> eventlist;

};
