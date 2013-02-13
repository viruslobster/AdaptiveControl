#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Math.h"
#include "PIDcontroller.h"
#include "AdaptiveController.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    lastAve = 10000; sum = 0; count = 0; inmin = 0; inmax = 1; outmin = 0; outmax = 1;
    
    controller = new PIDcontroller(-1000, 1000);
    pathFunction = 'f';
    ui->setupUi(this);
    ui->lineTrackerWidget->window = this;
    ui->lineTrackerWidget->drawPath();
    speed = 1;
    robot = new Robot(0, -10);
    updater = new QTimer(this);
    
    // connect events
    connect(updater, SIGNAL(timeout()), this, SLOT(updateLoop()));
    connect(ui->radioButton_3, SIGNAL( clicked() ), this, SLOT( on_radioButton_3_clicked() ));
    connect(ui->radioButton_4, SIGNAL( clicked() ), this, SLOT( on_radioButton_4_clicked() ));
    connect(ui->radioButton_5, SIGNAL( clicked() ), this, SLOT( on_radioButton_5_clicked() ));
    connect(ui->pushButton_2, SIGNAL( clicked() ), this, SLOT( on_pushButton_2_clicked() ));
    connect(ui->pushButton, SIGNAL( clicked() ), this, SLOT( on_pushButton_clicked() ));
}

MainWindow::~MainWindow() {
    delete ui;
}

double MainWindow::f(double x) {
    return 0;
}

double MainWindow::g(double x) {
    return 50 * sin(0.01 * x);
}

double MainWindow::h(double x) {
    if(x < 350) return 0;

    if(x >= 350) return 50 * sin(0.01 * x);
}

void MainWindow::updateLoop() {
    double error = 0;

    switch(pathFunction) {
    case 'f':
        error = f(robot->x) - robot->y;

        break;
    case 'g':
        error = g(robot->x) - robot->y;
        break;
    case 'h':
        error = h(robot->x) - robot->y;

        break;

    }

    double correction = controller->getCorrection(error);
    robot->move(speed, mapValues(correction, inmin, inmax, outmin, outmax));
    
    ui->lineTrackerWidget->drawRobot();
    this->repaint();

    sum += abs(error);
    count++;

    if(robot->x > 700) {
        updater->stop();
        double ave = sum / count;
        std::cout << "Average error = " << ave << std::endl;

        if(abs(lastAve - ave) > 0.000001 && ave > 5 && !(ave < 35)) {
            delete robot;
            robot = new Robot(0, -30);
            sum = 0;
            count = 0;
            ui->lineTrackerWidget->drawPath();
            updater->start(1);
            lastAve = ave;
        }


    }
}

void MainWindow::on_radioButton_4_clicked() {
    controller->loadConfig(pathFunction);
    this->pathFunction = 'f';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();
}

void MainWindow::on_radioButton_3_clicked() {
    controller->loadConfig(pathFunction);
    this->pathFunction = 'g';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();
}

void MainWindow::on_radioButton_5_clicked() {
    controller->loadConfig(pathFunction);
    this->pathFunction = 'h';
    ui->lineTrackerWidget->clear();
    ui->lineTrackerWidget->drawPath();
    this->repaint();
}

void MainWindow::on_pushButton_2_clicked() {
    sum = 0;
    count = 0;
    ui->lineTrackerWidget->drawPath();
    delete controller;

    if(ui->radioButton_2->isChecked()) {
        controller = new PIDcontroller(-1000, 1000);
        filename = "PID_";
	inmin = -1000; inmax = 1000; 
	outmin = -PI / 2; outmax = PI / 2;

    } else if(ui->radioButton->isChecked()) {
        controller = new AdaptiveController(1, 4);
        filename = "NN_L1_N4_";
	inmin = 0; inmax = 1; 
	outmin = -PI / 1000; outmax = PI / 1000;

    } else if(ui->radioButton_6->isChecked()) {
        controller = new AdaptiveController(1, 6);
        filename = "NN_L1_N6_";
	inmin = 0; inmax = 1; 
	outmin = -PI / 1000; outmax = PI / 1000;

    } else if(ui->radioButton_7->isChecked()) {
        controller = new AdaptiveController(2, 4);
        filename = "NN_L2_N4_";
	inmin = 0; inmax = 1; 
	outmin = -PI / 1000; outmax = PI / 1000;

    } else if(ui->radioButton_8->isChecked()) {
        controller = new AdaptiveController(2, 6);
        filename = "NN_L2_N6_";
	inmin = 0; inmax = 1; 
	outmin = -PI / 1000; outmax = PI / 1000;

    } else {
        controller = new PIDcontroller(-1000, 1000);
	inmin = -1000; inmax = 1000; 
	outmin = -PI / 2; outmax = PI / 2;
    }

    controller->loadConfig(pathFunction);
    delete robot;
    robot = new Robot(0, -30);
    updater->start(1);
}

void MainWindow::on_pushButton_clicked() {    
    std::string name;    
    name.append(filename);
    name.push_back(pathFunction);
    name.append(".png");    
    ui->lineTrackerWidget->saveImage(name);
}

