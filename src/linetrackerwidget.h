#ifndef LINETRACKERWIDGET_H
#define LINETRACKERWIDGET_H

#include <QWidget>
#include <QImage>
#include <string>
#include "mainwindow.h"

class LineTrackerWidget : public QWidget {
        Q_OBJECT
    public:
        explicit LineTrackerWidget(QWidget *parent = 0);
        MainWindow* window;
        void drawPath();
        void drawRobot();
        void clear();
        void saveImage(std::string filename);

    protected:
        virtual void paintEvent(QPaintEvent* );

    private:
        QImage* image;
};

#endif // LINETRACKERWIDGET_H
