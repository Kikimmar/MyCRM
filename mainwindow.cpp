#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    clientList = new ClientList(this);
    setCentralWidget(clientList);
}

MainWindow::~MainWindow() {}

