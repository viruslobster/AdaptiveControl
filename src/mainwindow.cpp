#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Math.h"
#include "PIDcontroller.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    controller = new PIDcontroller(-1000, 1000);
    pathFunction = 'f';
    ui->setupUi(this);    
    ui->lineTrackerWidget->window = this;
    ui->lineTrackerWidget->drawPath();
    speed = 1;
    robot = new Robot(0, -50);
    updater = new QTimer(this);
    connect(updater, SIGNAL(timeout()), this, SLOT(updateLoop()));
    connect(ui->radioButton_3, SIGNAL( clicked() ), this, SLOT( on_radioButton_3_clicked() ));
    connect(ui->radioButton_4, SIGNAL( clicked() ), this, SLOT( on_radioButton_4_clicked() ));
    connect(ui->radioButton_5, SIGNAL( clicked() ), this, SLOT( on_radioButton_5_clicked() ));
    connect(ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( on_pushButton_2_clicked() ));
    //updater->start(100);

}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::f(double x) {
  return 0;
}

double MainWindow::g(double x) {
  return 50 * sin(0.01*x);
}

double MainWindow::h(double x) {
  if(x < 350) return 0;
  if(x >= 350) return 50 * sin(0.01*x);
}



void MainWindow::updateLoop() {
   double error = 0;
   switch(pathFunction) {
     case 'f':
       error = f(robot->y) - robot->y;
       
       break;
     case 'g':
       error = g(robot->y) - robot->y;
       break;
     case 'h':
       error = h(robot->y) - robot->y;
       
       break;
     
   }
   double correction = controller->getCorrection(error);
   robot->move(speed, map(correction, -1000, 1000, -PI/2, PI/2));
   ui->lineTrackerWidget->drawRobot();
   this->repaint();
   if(robot->x > 700) updater->stop();
  
  std::cout << "Error:" << error << ", ";
  std::cout << "Correction:" << correction << std::endl;


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

void MainWindow::on_pushButton_2_clicked() {
  ui->lineTrackerWidget->drawPath();
  delete controller;
  controller = new PIDcontroller(-1000, 1000);
  delete robot;
  robot = new Robot(0, -50);
  updater->start(10);
}
