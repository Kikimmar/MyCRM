#include "mainwindow.h"
#include "addclientdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    layout = new QVBoxLayout;
    listView = new QListView;  // список клиентов
    addClientButton = new QPushButton("Добавить клиента");  // кнопка добавления клиента

    layout->addWidget(listView);
    layout->addWidget(addClientButton);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addClientButton, &QPushButton::clicked, this, &MainWindow::onAddClientButtonClicked);

    updateClientList();
}

MainWindow::~MainWindow() {}

void MainWindow::onAddClientButtonClicked()
{
    AddClientDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        // Логика добавления нового клиента в БД
        QMessageBox::information(this, "Успех", "Клиент успешно добавлен!");
    }
}

void MainWindow::updateClientList()
{
    // Логика обновления списка клиентов
    QMessageBox::information(this, "Информация", "Списсок клиентов обновлен");
}
