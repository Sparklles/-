#pragma once
#include<QString>
#include<QDate>
#include<Qlist>
struct Event {
	int id;            // 事件 ID
	QString title;        //事件标题
	QString description; //事件描述
	QDateTime startTime;     // 事件开始时间（包括时分秒）
	QDateTime finishTime;    // 事件结束时间
	QDateTime reminderTime;  // 提醒时间（也包括时分秒）
	QString location;        // 事件地点
};
class IEventStorage {
public:
	virtual ~IEventStorage() {}
	// 添加事件，返回是否成功
	virtual bool addEvent(const Event& event) = 0;

	// 更新事件
	virtual bool updateEvent(const Event& event) = 0;

	// 删除事件，根据事件的唯一ID删除
	virtual bool deleteEvent(const int& eventId) = 0;

	//获取某一时期的所有时间
	virtual QList<Event> getEvents(const QDate& date) = 0;

	// 获取所有事件
	virtual QList<Event> getAllEvents() = 0;
};