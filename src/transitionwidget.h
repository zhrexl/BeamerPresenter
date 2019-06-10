/*
 * This file is part of BeamerPresenter.
 * Copyright (C) 2019  stiglers-eponym

 * BeamerPresenter is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * BeamerPresenter is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with BeamerPresenter. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef TRANSITIONWIDGET_H
#define TRANSITIONWIDGET_H

#include <QObject>
#include <QPainter>
#include <QOpenGLWidget>
#include <QDebug>
#include <QTimer>
#include <poppler-page-transition.h>
#include "pagelabel.h"

class TransitionWidget : public PageLabel
{
    Q_OBJECT

private:
    int elapsed = 0;  // in ms
    int transition_duration = 0; // in ms
    int dt = 25;      // in ms
    int n_blinds = 8;
    int picwidth;
    int picheight;
    QTimer timer;
    QPainter painter;
    void (TransitionWidget::*paint)();

protected:
    QPixmap picinit;
    void paintEvent(QPaintEvent* event) override;
    void animate() override;

public:
    TransitionWidget(QWidget* parent=nullptr);
    void setFrameTime(int const time) {dt=time;}
    void setBlinds(int const blinds) {n_blinds=blinds;}
    void paintSplitHI();
    void paintSplitVI();
    void paintSplitHO();
    void paintSplitVO();
    void paintBlindsH();
    void paintBlindsV();
    void paintBoxO();
    void paintBoxI();
    void paintWipeUp();
    void paintWipeDown();
    void paintWipeLeft();
    void paintWipeRight();
    void paintDissolve();
    void paintGlitter();
    void paintFly();
    void paintPushUp();
    void paintPushDown();
    void paintPushLeft();
    void paintPushRight();
    void paintCover();
    void paintUncover();
    void paintFade();
};

typedef void (TransitionWidget::*paint)();

#endif // TRANSITIONWIDGET_H