#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include <QMouseEvent>
#include <QAction>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QMessageBox>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>

#include "weatherdata.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#define INCREMENT 3//温度每升高/降低1°C，y轴坐标的增量
#define POINT_RADIUS 3//曲线描点的大小
#define TEXT_OFFSET_X 12
#define TEXT_OFFSET_Y 12

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void contextMenuEvent(QContextMenuEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void getWeatherInfo(QString cityCode);
    void parseJson(QByteArray &byteArray);
    void updateUI();

    //重写过滤器
    bool eventFilter(QObject *watched,QEvent *event) override;

    //绘制高低温曲线
    void paintHighCurve();
    void paintLowCurve();

private slots:
    void onReplied(QNetworkReply *reply);
    void on_btnSearch_clicked();


private:
    Ui::MainWindow *ui;

    QMenu *mExitMenu;//右键退出的菜单项
    QAction *mExitAct;//退出的行为-菜单项

    QPoint mOffset;//窗口移动时与左上角的偏移量

    QNetworkAccessManager *mNetAccessManager;

    Today mToday;
    Day mDay[6];
    //星期和日期
    QList<QLabel*>mWeekList;
    QList<QLabel*>mDateList;
    //天气和天气图标
    QList<QLabel*>mTypeList;
    QList<QLabel*>mTypeIconList;
    //天气污染指数
    QList<QLabel*>mAqiList;
    //风力和风向
    QList<QLabel*>mFxList;
    QList<QLabel*>mFlList;

    QMap<QString,QString>mTypeMap;
};
#endif // MAINWINDOW_H
