/*==============================================================================

  Program: 3D Slicer

  Copyright (c) 2010 Kitware Inc.

  See Doc/copyright/copyright.txt
  or http://www.slicer.org/copyright/copyright.txt for details.

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  This file was originally developed by Julien Finet, Kitware Inc.
  and was partially funded by NIH grant 3P41RR013218-12S1

==============================================================================*/

// Qt includes
#include <QDebug>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QMenu>
#include <QStyleOptionSlider>
#include <QToolButton>
#include <QWidgetAction>

// CTK includes
#include "qMRMLRangeWidget.h"

// --------------------------------------------------------------------------
qMRMLRangeWidget::qMRMLRangeWidget(QWidget* parentWidget)
  : ctkRangeWidget(parentWidget)
{
  this->setSlider(new qMRMLDoubleRangeSlider(0));
  
  QWidget* rangeWidget = new QWidget;
  this->MinSpinBox = new QDoubleSpinBox;
  this->MaxSpinBox = new QDoubleSpinBox;
  this->MinSpinBox->setPrefix("Min: ");
  this->MinSpinBox->setRange(-1000000., 1000000.);
  this->MinSpinBox->setValue(this->minimum());
  this->MaxSpinBox->setPrefix("Max: ");
  this->MaxSpinBox->setRange(-1000000., 1000000.);
  this->MaxSpinBox->setValue(this->maximum());
  connect(this->MinSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(updateRange()));
  connect(this->MaxSpinBox, SIGNAL(valueChanged(double)),
          this, SLOT(updateRange()));
  connect(this->slider(), SIGNAL(rangeChanged(double, double)),
          this, SLOT(updateSpinBoxRange(double, double)));
  QHBoxLayout* rangeLayout = new QHBoxLayout;
  rangeLayout->addWidget(this->MinSpinBox);
  rangeLayout->addWidget(this->MaxSpinBox);
  rangeLayout->setContentsMargins(0,0,0,0);
  rangeWidget->setLayout(rangeLayout);
  
  QWidgetAction* rangeAction = new QWidgetAction(0);
  rangeAction->setDefaultWidget(rangeWidget);
  
  QMenu* optionsMenu = new QMenu;
  optionsMenu->addAction(rangeAction);
  
  QToolButton* optionsButton = new QToolButton(this);
  optionsButton->setIcon(QIcon(":Icons/SliceMoreOptions.png"));
  optionsButton->setMenu(optionsMenu);
  optionsButton->setPopupMode(QToolButton::InstantPopup);
  QGridLayout* gridLayout = qobject_cast<QGridLayout*>(this->layout());
  gridLayout->addWidget(optionsButton,0,3);
}

// --------------------------------------------------------------------------
QPalette qMRMLRangeWidget::minimumHandlePalette()const
{
  return qobject_cast<qMRMLDoubleRangeSlider*>(this->slider())
    ->minimumHandlePalette();
}

// --------------------------------------------------------------------------
QPalette qMRMLRangeWidget::maximumHandlePalette()const
{
  return qobject_cast<qMRMLDoubleRangeSlider*>(this->slider())
    ->maximumHandlePalette();
}

// --------------------------------------------------------------------------
void qMRMLRangeWidget::setMinimumHandlePalette(const QPalette& palette)
{
  qobject_cast<qMRMLDoubleRangeSlider*>(this->slider())
    ->setMinimumHandlePalette(palette);
}

// --------------------------------------------------------------------------
void qMRMLRangeWidget::setMaximumHandlePalette(const QPalette& palette)
{
  qobject_cast<qMRMLDoubleRangeSlider*>(this->slider())
    ->setMaximumHandlePalette(palette);
}

// --------------------------------------------------------------------------
void qMRMLRangeWidget::updateSpinBoxRange(double min, double max)
{
  this->MinSpinBox->setValue(min);
  this->MaxSpinBox->setValue(max);
}

// --------------------------------------------------------------------------
void qMRMLRangeWidget::updateRange()
{
  this->setRange(this->MinSpinBox->value(),
                 this->MaxSpinBox->value());
}

// --------------------------------------------------------------------------
qMRMLDoubleRangeSlider::qMRMLDoubleRangeSlider(QWidget* parentWidget)
  :ctkDoubleRangeSlider(parentWidget)
{
  this->setSlider(new qMRMLRangeSlider(0));
}

// --------------------------------------------------------------------------
QPalette qMRMLDoubleRangeSlider::minimumHandlePalette()const
{
  return qobject_cast<qMRMLRangeSlider*>(this->slider())
    ->minimumHandlePalette();
}

// --------------------------------------------------------------------------
QPalette qMRMLDoubleRangeSlider::maximumHandlePalette()const
{
  return qobject_cast<qMRMLRangeSlider*>(this->slider())
    ->maximumHandlePalette();
}

// --------------------------------------------------------------------------
void qMRMLDoubleRangeSlider::setMinimumHandlePalette(const QPalette& palette)
{
  qobject_cast<qMRMLRangeSlider*>(this->slider())
    ->setMinimumHandlePalette(palette);
}

// --------------------------------------------------------------------------
void qMRMLDoubleRangeSlider::setMaximumHandlePalette(const QPalette& palette)
{
  qobject_cast<qMRMLRangeSlider*>(this->slider())
    ->setMaximumHandlePalette(palette);
}

// --------------------------------------------------------------------------
class qMRMLRangeSliderPrivate
{
  Q_DECLARE_PUBLIC(qMRMLRangeSlider);
protected:
  qMRMLRangeSlider* const q_ptr;

public:
  qMRMLRangeSliderPrivate(qMRMLRangeSlider* widget);

  QPalette MinimumPalette;
  QPalette MaximumPalette;
};

// --------------------------------------------------------------------------
qMRMLRangeSliderPrivate::qMRMLRangeSliderPrivate(qMRMLRangeSlider* pub)
  : q_ptr(pub)
{
}

// --------------------------------------------------------------------------
qMRMLRangeSlider::qMRMLRangeSlider(QWidget* parentWidget)
  :ctkRangeSlider(parentWidget)
   ,d_ptr(new qMRMLRangeSliderPrivate(this))
{
}

// --------------------------------------------------------------------------
qMRMLRangeSlider::~qMRMLRangeSlider()
{
}

// --------------------------------------------------------------------------
QPalette qMRMLRangeSlider::minimumHandlePalette()const
{
  Q_D(const qMRMLRangeSlider);
  return d->MinimumPalette;
}

// --------------------------------------------------------------------------
QPalette qMRMLRangeSlider::maximumHandlePalette()const
{
  Q_D(const qMRMLRangeSlider);
  return d->MaximumPalette;
}

// --------------------------------------------------------------------------
void qMRMLRangeSlider::setMinimumHandlePalette(const QPalette& palette)
{
  Q_D(qMRMLRangeSlider);
  d->MinimumPalette = palette;
  this->update();
}

// --------------------------------------------------------------------------
void qMRMLRangeSlider::setMaximumHandlePalette(const QPalette& palette)
{
  Q_D(qMRMLRangeSlider);
  d->MaximumPalette = palette;
  this->update();
}

//---------------------------------------------------------------------------
void qMRMLRangeSlider::initMinimumSliderStyleOption(QStyleOptionSlider* option) const
{
  Q_D(const qMRMLRangeSlider);
  this->ctkRangeSlider::initStyleOption(option);
  option->palette = d->MinimumPalette;
}

//---------------------------------------------------------------------------
void qMRMLRangeSlider::initMaximumSliderStyleOption(QStyleOptionSlider* option) const
{
  Q_D(const qMRMLRangeSlider);
  this->ctkRangeSlider::initStyleOption(option);
  option->palette = d->MaximumPalette;
}
