/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     xuwenw <xuwenw@xuwenw.so>
 *
 * Maintainer:  <@xuwenw.so>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MAINPANELCONTROL_H
#define MAINPANELCONTROL_H

#include "constants.h"

#include <QWidget>
#include <QBoxLayout>

using namespace Dock;

class MainPanelDelegate
{
public:
    virtual bool appIsOnDock(const QString &appDesktop) = 0;
};

class DockItem;
class PlaceholderItem;
class AppDragWidget;
class MainPanelControl : public QWidget
{
    Q_OBJECT
public:
    MainPanelControl(QWidget *parent = 0);
    ~MainPanelControl();

    void addFixedAreaItem(int index, QWidget *wdg);
    void addAppAreaItem(int index, QWidget *wdg);
    void addTrayAreaItem(int index, QWidget *wdg);
    void addPluginAreaItem(int index, QWidget *wdg);
    void removeFixedAreaItem(QWidget *wdg);
    void removeAppAreaItem(QWidget *wdg);
    void removeTrayAreaItem(QWidget *wdg);
    void removePluginAreaItem(QWidget *wdg);
    void setPositonValue(Position position);
    void setDisplayMode(DisplayMode m_displayMode);

    MainPanelDelegate *delegate() const;
    void setDelegate(MainPanelDelegate *delegate);

signals:
    void itemMoved(DockItem *sourceItem, DockItem *targetItem);
    void itemAdded(const QString &appDesktop, int idx);
    void displayModeChanged();
    void positionChanged();

private:
    void resizeEvent(QResizeEvent *event) override;

    void init();
    void updateAppAreaSonWidgetSize();
    void updateMainPanelLayout();
    void updateDisplayMode();
    void moveAppSonWidget();

    void dragMoveEvent(QDragMoveEvent *e) override;
    void dragEnterEvent(QDragEnterEvent *e) override;
    void dragLeaveEvent(QDragLeaveEvent *e) override;
    void dropEvent(QDropEvent *) override;
    bool eventFilter(QObject *watched, QEvent *event) override;

    void startDrag(DockItem *);
    DockItem *dropTargetItem(DockItem *sourceItem, QPoint point);
    void moveItem(DockItem *sourceItem, DockItem *targetItem);
    void handleDragMove(QDragMoveEvent *e, bool isFilter);

public slots:
    void insertItem(const int index, DockItem *item);
    void removeItem(DockItem *item);
    void onDisplayModeChanged();
    void onPositionChanged();

private:
    QBoxLayout *m_mainPanelLayout;
    QWidget *m_fixedAreaWidget;
    QWidget *m_appAreaWidget;
    QWidget *m_trayAreaWidget;
    QWidget *m_pluginAreaWidget;
    QBoxLayout *m_fixedAreaLayout;
    QBoxLayout *m_trayAreaLayout;
    QBoxLayout *m_pluginLayout;
    QWidget *m_appAreaSonWidget;
    QBoxLayout *m_appAreaSonLayout;
    Position m_position;
    QPointer<PlaceholderItem> m_placeholderItem;
    MainPanelDelegate *m_delegate;
    QString m_draggingMimeKey;
    AppDragWidget *m_appDragWidget;
    DisplayMode m_dislayMode;
};

#endif // MAINPANELCONTROL_H
