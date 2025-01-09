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

    // if (!query.exec()) {
    //     qDebug() << "Ошибка выполнения запроса:" << query.lastError().text();
    //     QMessageBox::warning(this, "Ошибка", "Не удалось загрузить список клиентов.");
    //     return;
    // }

    while (query.next())
    {
        QList<QStandardItem*> rowItems;
        for (int i = 0; i < query.record().count(); ++i)
        {
            rowItems.append(new QStandardItem(query.value(i).toString()));
        }
        model->appendRow(rowItems);  // добавляем строку в модель
    }

    if (query.lastError().isValid())
    {
        qDebug() << "Ошибка получение списка клиентов:" << query.lastError().text();
        QMessageBox::information(this, "Ошибка", "Не удалось загрузить список клиентов");
    }

}
