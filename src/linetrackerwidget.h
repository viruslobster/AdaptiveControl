#ifndef LINETRACKERWIDGET_H
#define LINETRACKERWIDGET_H

#include <QWidget>

class LineTrackerWidget : public QWidget {
  Q_OBJECT
public:
  explicit LineTrackerWidget(QWidget *parent = 0);
    
protected:
  virtual void paintEvent(QPaintEvent* );
    
};

#endif // LINETRACKERWIDGET_H
