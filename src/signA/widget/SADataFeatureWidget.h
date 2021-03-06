﻿#ifndef SADATAFEATUREWIDGET_H
#define SADATAFEATUREWIDGET_H

#include <QWidget>
#include <QProcess>
#include <QMap>
#include "../global/SAGlobals.h"
#include <memory>
#include <QTimer>
#include <QDateTime>
#include "SADataClient.h"


class QwtPlotItem;
class QMdiSubWindow;
class QAbstractItemModel;
class SAFigureWindow;
class DataFeatureTreeModel;
class SAChart2D;
class SAFigureSetWidget;


namespace Ui {
class SADataFeatureWidget;
}

/**
 * @brief 数据属性显示窗口
 */
class SADataFeatureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SADataFeatureWidget(QWidget *parent = 0);
    ~SADataFeatureWidget();
public slots:
    //子窗口激活槽
    void mdiSubWindowActived(QMdiSubWindow *arg1);
    //子窗口关闭槽
    void mdiSubWindowClosed(QMdiSubWindow *arg1);
signals:
    //显示消息
    void showMessageInfo(const QString& info,SA::MeaasgeType messageType = SA::NormalMessage);
private slots:
    //树形控件点击
    void onTreeViewClicked(const QModelIndex &index);
    //点击清除属性按钮
    void onToolButtonClearDataFeatureClicked();
    //图片隐藏触发的槽，隐藏绘图需要对显示的信息也隐藏
    void onChartHide();
    //绘图销毁触发的槽，绘图销毁，对数据进行销毁
    void onChartDestroy();
    //fig窗口销毁
    void onFigureDestroy();
    //心跳超时
    void onHeartbeatCheckerTimerout();
private:
    //对MdiSubWindow进行绑定
    void bindMdiSubWindow(QMdiSubWindow *w);
    //对已经绑定的MdiSubWindow进行解绑
    void unbindMdiSubWindow(QMdiSubWindow *w);
    //获取mdisubwindow的FigureWindow
    SAFigureWindow* getFigureFromSubWindow(QMdiSubWindow* sub);
    //计算绘图窗口的dataFeature
    void callCalcFigureWindowFeature(SAFigureWindow* figure);
    //检测model是否需要重新计算datafeature
    void checkModelItem(QAbstractItemModel* baseModel,QMdiSubWindow *subWndPtr);
private:
    //计算一个plot item
    void calc2DPlotItemDataInfo(const QwtPlotItem* plotitem,const QMdiSubWindow *midwidget,const SAChart2D* chartptr);
public://数据接收相关的类型
    class _DataInfo{
    public:
        _DataInfo();
        QAbstractItemModel* model;
    };
private:
    Ui::SADataFeatureWidget *ui;
    QMdiSubWindow* m_lastActiveSubWindow;///< 记录最后激活的子窗口
    QMap<QMdiSubWindow*,_DataInfo> m_subWindowToDataInfo;///< 记录子窗口对应的数据属性表上显示的model
    SADataClient m_client;
    QHash<_DataInfo,_DataInfo> m_key2wndPtr;
};

uint qHash(const SADataFeatureWidget::_DataInfo &key, uint seed);

#endif // DATAFEATUREWIDGET_H
