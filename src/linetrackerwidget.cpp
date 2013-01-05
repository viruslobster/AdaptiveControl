#include <QPainter>
#include "linetrackerwidget.h"


LineTrackerWidget::LineTrackerWidget(QWidget *parent) : QWidget(parent) {
  
  
}

void LineTrackerWidget::paintEvent(QPaintEvent* ) {
  QPen pen(Qt::black, 2, Qt::SolidLine);

  QPainter painter(this); 
  
  painter.setPen(pen);
  
  painter.drawRect(0,0,100,100);
  
  
}
