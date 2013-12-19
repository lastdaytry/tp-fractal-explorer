#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fractalexplorer.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->fractalArea = new fractalExplorer(ui->centralWidget);
    ui->fractalArea->setGeometry(QRect(10, 30, 551, 351));
    ui->colorChooser->setCurrentIndex(0);
    connect(ui->fractalChooser, SIGNAL(currentIndexChanged(int)),
            ui->fractalArea, SLOT(changeFractalType(int)));
    connect(ui->colorChooser, SIGNAL(currentIndexChanged(int)),
            ui->fractalArea, SLOT(updateColor(int)));
    connect(ui->SaveImageButton, SIGNAL(clicked()),
            ui->fractalArea, SLOT(saveImage()));

    ui->fractalArea->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
