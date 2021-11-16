#include <QPainter>
#include <QResizeEvent>
#include <QStyleOption>
#include <QtCore/qmath.h>
#include <QDebug>
#include <QPalette>
#include <QLabel>

#include "menucolorpicker.h"

ColorWheel::ColorWheel(QWidget *parent): QWidget(parent)
{
    color = new QColor(255, 255, 255, 1);
    h = color->hueF();
    s = color->saturationF();
    v = color->valueF();

    margin = 10;
    radius = 0;
}

void ColorWheel::paintEvent(QPaintEvent *e)
{
    QPointF center = QPointF(width()/2, height()/2);
    QPainter painter(this);

    painter.setViewport(margin, margin, width() - 2 * margin, height() - 2 * margin);

    QConicalGradient hsv_grad = QConicalGradient(center, 90);
    for (int i = 0; i < 360; ++i) {
        QColor col = QColor::fromHsvF(i / 360.0, 1, v);
        hsv_grad.setColorAt(i / 360.0, col);
    }

    QRadialGradient val_grad = QRadialGradient(center, radius);
    val_grad.setColorAt(0.0, QColor::fromHsvF(0.0, 0.0, v, 1.0));
    val_grad.setColorAt(1.0, Qt::transparent);

    painter.setPen(Qt::transparent);
    painter.setBrush(hsv_grad);
    painter.drawEllipse(rect());

    painter.setBrush(val_grad);
    painter.drawEllipse(rect());
}

void ColorWheel::resizeEvent(QResizeEvent *e)
{
    radius = qMin(width() / 2, height() / 2);
}


QSize ColorWheel::sizeHint() const {
    return QSize(width(), height());
}

TemperatureBox::TemperatureBox(QWidget *parent): QWidget(parent)
{
    color = new QColor(255, 255, 255, 1);
    h = color->hueF();
    s = color->saturationF();
    v = color->valueF();

    margin = 10;
    radius = 0;
}

void TemperatureBox::paintEvent(QPaintEvent *e)
{
    QPointF center = QPointF(width()/2, height()/2);
    QPainter painter(this);

    painter.setViewport(margin, margin, width() - 2 * margin, height() - 2 * margin);

    QConicalGradient hsv_grad = QConicalGradient(center, 90);
    for (int i = 0; i < 360; ++i) {
        QColor col = QColor::fromHsvF(i / 360.0, 1, v);
        hsv_grad.setColorAt(i / 360.0, col);
    }

    QRadialGradient val_grad = QRadialGradient(center, radius);
    val_grad.setColorAt(0.0, QColor::fromHsvF(0.0, 0.0, v, 1.0));
    val_grad.setColorAt(1.0, Qt::transparent);

    painter.setPen(Qt::transparent);
    painter.setBrush(hsv_grad);
    painter.drawRoundedRect(rect(), 0.5, 0.5);

    //painter.setBrush(val_grad);
    //painter.drawRoundedRect(rect());
}

void TemperatureBox::resizeEvent(QResizeEvent *e)
{
    radius = qMin(width() / 2, height() / 2);
}


QSize TemperatureBox::sizeHint() const {
    return QSize(width(), height());
}

ColorPicker::ColorPicker(QWidget *parent): QWidget(parent)
{
    int tmp_size = 250;
    main_layout = new QVBoxLayout(this);

    main_layout->setContentsMargins(0, 0, 0, 0);

    ColorWheel* color_wheel = new ColorWheel(this);

    color_wheel->setMinimumHeight(tmp_size);
    color_wheel->setMinimumWidth(tmp_size);
    color_wheel->setMaximumHeight(tmp_size);
    color_wheel->setMaximumWidth(tmp_size);

    main_layout->addWidget(color_wheel);

    TemperatureBox* temperature_box = new TemperatureBox(this);

    temperature_box->setMinimumHeight(tmp_size / 4.5);
    temperature_box->setMinimumWidth(tmp_size);
    temperature_box->setMaximumHeight(tmp_size / 4.5);
    temperature_box->setMaximumWidth(tmp_size);

    main_layout->addWidget(temperature_box);
}

QSize ColorPicker::sizeHint() const {
    return main_layout->sizeHint();
}
