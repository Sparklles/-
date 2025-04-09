#include "EventManager.h"

EventManager::EventManager(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.CreateButton->setIcon(QIcon("+.png"));//设置图标
	ui.CreateButton->setIconSize(QSize(30, 30));  //调整图标大小
    ui.CreateButton->setText("");  // 确保不设置文本
	ui.CreateButton->setFixedSize(40, 40); // 设置按钮尺寸
    ui.CreateButton->setStyleSheet(
        "QPushButton {"
        "    border: none;"
        "    border-radius: 20px;"  // 圆形按钮
        "    background-color: #0078D7;" // 颜色可修改
        "    color: white;"
        "}"
        "QPushButton:hover {"
        "    background-color: #005A9E;" // 悬停颜色
        "}"
        "QPushButton:pressed {"
        "    background-color: #003F7D;" // 按下颜色
        "}"
    );
    connect(ui.CreateButton,&QPushButton::clicked,this,&EventManager::CreateButton);
    connect(ui.calendarWidget, &QCalendarWidget::clicked, this, &EventManager::loadEventsforDate);
    connect(ui.listWidget, &QListWidget::itemClicked, this, &EventManager::show_event_detail);
}

EventManager::~EventManager()
{}

bool EventManager::addEvent(const Event & event)
{
    // 避免重复事件（假设 ID 是唯一的）
    for (const Event& e : eventlist) {
        if (e.id == event.id) {
            return false;  // ID 相同，拒绝添加
        }
    }
    eventlist.append(event);  // 添加事件
    return true;
}

bool EventManager::updateEvent(const Event& event)
{
    return false;
}

bool EventManager::deleteEvent(const int& eventId)
{
    for (int i = 0; i < eventlist.size(); ++i) {
        if (eventlist[i].id == eventId) {
            eventlist.removeAt(i);
            return true;
        }
    }
    return false;
}

QList<Event> EventManager::getEvents(const QDate& date)
{
    return QList<Event>();
}

QList<Event> EventManager::getAllEvents()
{
    return QList<Event>();
}

void EventManager::CreateButton() //事件创建
{
    QDate selectdate = ui.calendarWidget->selectedDate();
    EventDialog dialog(selectdate, this);
    if (dialog.exec() == QDialog::Accepted) {
        // 获取用户输入的数据
        QString title = dialog.getTitle();
        QString description = dialog.getDescription();
        QDateTime startTime = dialog.getStartTime();
        QDateTime endTime = dialog.getEndTime();
        QDateTime reminderTime = dialog.getreminderTime();
        QString  location = dialog.getlocation();
        // 根据获取的数据创建 Event 对象并存储（调用 IEventStorage 接口方法）
        Event event;
        event.id = generateEventId();
        event.title = title;
        event.description = description;
        event.startTime = startTime;
        event.finishTime = endTime;
        event.reminderTime = reminderTime;
        event.location = location;
        addEvent(event);
        //刷新主界面的事件显示
        loadEventsforDate(ui.calendarWidget->selectedDate());

    }

}

void EventManager::loadEventsforDate(const QDate& d)//展示
{
    ui.listWidget->clear();
    for (const Event& e : eventlist) {
        if (e.startTime.date() == d) {
            QString shortDescription = e.description;
            const int maxChars = 15;  //最大显示字数
            if (shortDescription.length() > maxChars) {
                shortDescription = shortDescription.left(maxChars) + "...";
            }
            QListWidgetItem* item = new QListWidgetItem(shortDescription, ui.listWidget);
            item->setData(Qt::UserRole, e.id);  //添加事件的id，方便后续查看详细信息时依id查询
            ui.listWidget->addItem(item);
        }
    }
}

void EventManager::show_event_detail(QListWidgetItem* item)//展示详细信息
{
    int curretn_id = item->data(Qt::UserRole).toInt();//获取事件的唯一id
    //查找该事件
    Event selectedEvent;
    bool found = false;
    for (const Event& e : eventlist) {
        if (e.id == curretn_id) {
            selectedEvent = e;
            found = true;
            break;
        }
    }
    if (!found) {
        return;
    }

    // 创建并显示事件详情对话框
    EventDetailDialog d(selectedEvent);
    connect(&d, &EventDetailDialog::eventUpdated, this, [&](const Event& updatedEvent) {
        // 更新 eventList 中的数据
        for (Event& e : eventlist) {
            if (e.id == updatedEvent.id) {
                e = updatedEvent;
                break;
            }
        }
        // 刷新当前日期的事件列表
        loadEventsforDate(ui.calendarWidget->selectedDate());
        });
    connect(&d, &EventDetailDialog::eventDeleted, this, [&](const int& deletedEventId) {
        // 删除对应事件
        deleteEvent(deletedEventId);
        // 刷新当前日期的事件列表
        loadEventsforDate(ui.calendarWidget->selectedDate());
        });
    d.exec();
}

int EventManager::generateEventId() {
    static int idCounter = 1; // 静态变量，程序运行期间保持值
    return idCounter++;
}
