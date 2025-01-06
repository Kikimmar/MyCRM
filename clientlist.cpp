#include "clientlist.h"
#include "addclientdialog.h"

#include <QVBoxLayout>
#include <QListView>
#include <QMessageBox>

ClientList::ClientList(QWidget *parent) : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    QListView *listView = new QListView(this);  // список клиентов

    addClientButton = new QPushButton("Добавить клиента", this);  // кнопка добавления клиента

    layout->addWidget(listView);
    layout->addWidget(addClientButton);

    connect(addClientButton, &QPushButton::clicked, this, &ClientList::onAddClientButtonClicked);
}

void ClientList::onAddClientButtonClicked()
{
    AddClientDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        // Логика добавления нового клиента в БД
        QMessageBox::information(this, "Успех", "Клиент успешно добавлен!");
    }
}
