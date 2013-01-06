#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Math.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    pathFunction = 'f';
    ui->setupUi(this);    
    ui->lineTrackerWidget->window = this;
    ui->lineTrackerWidget->drawPath();
    speed = 1;
    robot = new Robot(0, 0);
    updater = new QTimer(this);
    connect(updater, SIGNAL(timeout()), this, SLOT(updateLoop()));
    connect (ui->radioButton_3, SIGNAL( clicked() ), this, SLOT( on_radioButton_3_clicked() ));
    connect (ui->radioButton_4, SIGNAL( clicked() ), this, SLOT( on_radioButton_4_clicked() ));
    connect (ui->radioButton_5, SIGNAL( clicked() ), this, SLOT( on_radioButton_5_clicked() ));
    updater->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(double x) {
  return 0;
}

double MainWindow::g(double x) {
  return 50 * sin(0.1*x);
}

double MainWindow::h(double x) {
  if(x < 350) return 0;
  if(x >= 350) return 50 * sin(0.1*x);
}



void MainWindow::updateLoop() {
  // double error = robot.x - pathFunction(robot.x);
  // double correction = controller.getCorrection(error);
  // robot.move(speed, correction);
  // updateGUI();
  // if(robot.x > 500) updater->stop();


}



void MainWindow::on_radioButton_4_clicked() {
    this->pathFunction = 'f';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();

}

void MainWindow::on_radioButton_3_clicked() {
    this->pathFunction = 'g';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();

}

void MainWindow::on_radioButton_5_clicked() {
    this->pathFunction = 'h';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();
}
