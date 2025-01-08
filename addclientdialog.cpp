#include "addclientdialog.h"
#include "clientmanager.h"

AddClientDialog::AddClientDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Добавление клиента");

    auto *formLayout = new QFormLayout(this);

    companyNameInput = new QLineEdit(this);

    // Установка валидатора для ИНН
    innInput = new QLineEdit(this);
    innInput->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{12}"), this));

    addressInput = new QLineEdit(this);

    formLayout->addRow("Название компании:", companyNameInput);
    formLayout->addRow("ИНН:", innInput);
    formLayout->addRow("Юридический адрес:", addressInput);

    lastNameInput = new QLineEdit(this);
    firstNameInput = new QLineEdit(this);
    middleNameInput = new QLineEdit(this);

    phoneInput = new QLineEdit(this);
    phoneInput->setPlaceholderText("Телефон (например, +7-(999)999-99-99)");
    phoneInput->setInputMask("+7 (999) 999-99-99;_");  // маска для телефонного ввода

    emailInput = new QLineEdit(this);
    emailInput->setValidator(new QRegularExpressionValidator(QRegularExpression(R"((\w+)(\.\w+)*@(\w+)(\.\w+)+)"), this));

    formLayout->addRow("Фамилия:", lastNameInput);
    formLayout->addRow("Имя:", firstNameInput);
    formLayout->addRow("Отчество:", middleNameInput);
    formLayout->addRow("Телефон:", phoneInput);
    formLayout->addRow("Электронная почта:", emailInput);

    // Поле заметок
    notesInput = new QTextEdit(this);

    formLayout->addRow("Комментарии:", notesInput);

    auto *saveButton = new QPushButton("Сохранить", this);

    connect(saveButton, &QPushButton::clicked, this, &AddClientDialog::onSaveButtonClicked);

    formLayout->addWidget(saveButton);  // добавляем кнопку в форму

    setLayout(formLayout);  // форма как основной макет диалога
}

void AddClientDialog::onSaveButtonClicked()
{
    ClientManager clientManager;

    // Получаем данные из полей
    ClientData clientData
    {
        companyNameInput->text(),
        innInput->text(),
        addressInput->text(),
        lastNameInput->text(),
        firstNameInput->text(),
        middleNameInput->text(),
        phoneInput->text(),
        emailInput->text(),
        notesInput->toPlainText()
    };

    // Сохраняем клиента в БД
    if (clientManager.addClient(clientData.companyName, clientData.inn, clientData.address,
                                clientData.lastName, clientData.firstName, clientData.middleName,
                                clientData.phone, clientData.email, clientData.notes))
    {
        QMessageBox::information(this, "Успех", "Клиент успешно добавлен!");
        accept();
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Не удалось добавить клиента.");
    }
}
