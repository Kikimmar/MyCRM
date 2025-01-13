#include "mainwindow.h"
#include "addclientdialog.h"
#include "clientmanager.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QSqlRecord>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), model(new QStandardItemModel(this))
{
    layout = new QVBoxLayout;

    tableView = new QTableView;  // список клиентов
    tableView->setModel(model);  // установка модели в таблицу

    addClientButton = new QPushButton("Добавить клиента");  // кнопка добавления клиента

    layout->addWidget(tableView);
    layout->addWidget(addClientButton);

    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(addClientButton, &QPushButton::clicked, this, &MainWindow::onAddClientButtonClicked);
    connect(tableView, &QTableView::doubleClicked, this, &MainWindow::onTableViewDoubleClicked);

    updateClientList();
}

MainWindow::~MainWindow() {}

void MainWindow::onAddClientButtonClicked()
{
    AddClientDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        // Логика добавления нового клиента в БД
        updateClientList();  // обновляем список после добавления клиента
        QMessageBox::information(this, "Успех", "Клиент успешно добавлен!");
    }
}

void MainWindow::updateClientList()
{
    model->clear();  // очищаем модель перед обновлением
    model->setHorizontalHeaderLabels({"Компания", "ИНН", "Адрес", "Фамилия", "Имя", "Отчество", "Телефон", "Email", "Заметки"});

    DatabaseManager& dbManager = DatabaseManager::getInstance();

    if (!dbManager.connectToDatabase())
    {
        QMessageBox::warning(this, "Ошибка", "База данныx не подключена");
        return;
    }

    QSqlQuery query("SELECT company_name, inn, address, last_name, first_name, middle_name, phone, email, notes FROM clients");

    while (query.next())
    {
        QList<QStandardItem*> rowItems;
        for (int i = 0; i < query.record().count(); ++i)
        {
            rowItems.append(new QStandardItem(query.value(i).toString()));
        }
        model->appendRow(rowItems);  // добавляем строку в модель
    }

    // Устанавливаем поведение выделения на строки
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Отключаем редактирование
    tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Устанавливаем ширину 200 пикселей для всех колонок, кроме "Заметки"
    for (int i = 0; i < model->columnCount() - 1; ++i) // -1, чтобы не включать последнюю колонку
    {
        tableView->setColumnWidth(i, 200);
    }

    // Устанавливаем ширину колонки "Заметки" (последней колонки) на автоматическую
    tableView->horizontalHeader()->setSectionResizeMode(model->columnCount() - 1, QHeaderView::Stretch);

    if (query.lastError().isValid())
    {
        qDebug() << "Ошибка получение списка клиентов:" << query.lastError().text();
        QMessageBox::information(this, "Ошибка", "Не удалось загрузить список клиентов");
    }
}

void MainWindow::onTableViewDoubleClicked(const QModelIndex &index)
{
    if (!index.isValid())
    {
        return;
    }

    int row = index.row();  // получаем номер строки

    // Извлекаем данные клиента из модели
    ClientData clientData;
    for (int i = 0; i < model->columnCount(); ++i)
    {
        QModelIndex modelIndex = model->index(row, i);  // получаем индекс модели для каждой колонки
        QString value = model->data(modelIndex).toString();  // получаем значение из модели

        switch (i)
        {
        case 0:
            clientData.companyName = value;
            break;
        case 1:
            clientData.inn = value;
            break;
        case 2:
            clientData.address = value;
            break;
        case 3:
            clientData.lastName = value;
            break;
        case 4:
            clientData.firstName = value;
            break;
        case 5:
            clientData.middleName = value;
            break;
        case 6:
            clientData.phone = value;
            break;
        case 7:
            clientData.email = value;
            break;
        case 8:
            clientData.notes = value;
            break;
        }
    }

    EditClientDialog editDialog(clientData, this);  // создаем диалог с данными клиента

    if (editDialog.exec() == QDialog::Accepted)
    {
        updateClientList();  // обновляем список клиентов после редактирования
    }

}

