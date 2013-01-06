#include <QPainter>
#include <QRect>
#include "linetrackerwidget.h"


LineTrackerWidget::LineTrackerWidget(QWidget *parent) : QWidget(parent) {
    image = new QImage(700, 200, QImage::Format_ARGB32);
    this->resize(100, 100);



  
}

void LineTrackerWidget::drawPath() {
    clear();
    QPen pen(Qt::black, 2, Qt::SolidLine);

    QPainter imagePainter(image);
    imagePainter.setRenderHint(QPainter::Antialiasing);

    imagePainter.setPen(pen);
    imagePainter.drawRect(0, 0, image->width(), image->height());


    double x = 0;
    double deltax = 0.1;
    double OFFSET = image->height() / 2.0;

    while(x < 700) {
        double y;
        switch(window->pathFunction) {
          case 'f':
            y = window->f(x) + OFFSET;
          break;
          case 'g':
            y = window->g(x) + OFFSET;
          break;
          case 'h':
            y = window->h(x) + OFFSET;
          break;
        }

        imagePainter.drawPoint(x, y);
        x += deltax;
    }



}

void LineTrackerWidget::drawRobot() {
  QPen pen(Qt::red, 2, Qt::SolidLine);

  QPainter imagePainter(image);
  imagePainter.setPen(pen);
  double OFFSET = image->height() / 2.0;
  imagePainter.drawPoint(window->robot->x, window->robot->y + OFFSET);

}

void LineTrackerWidget::clear() {
  QPainter imagePainter(image);
  imagePainter.eraseRect(0, 0, image->width(), image->height());

}

void LineTrackerWidget::paintEvent(QPaintEvent* ) {  
  QPainter painter(this);
  QRect sourceRect(0, 0, image->width(), image->height());
  QRect destRect(0, 0, this->width(), this->height());
  //painter.drawImage(destRect, *image, sourceRect);
  painter.drawImage(QPoint(0,0), *image);

  
}
