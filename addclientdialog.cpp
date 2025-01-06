#include "addclientdialog.h"

AddClientDialog::AddClientDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Добавление клиента");

    QFormLayout *formLayout = new QFormLayout(this);

    // Группа полей "Компания"
    companyNameInput = new QLineEdit(this);

    // Установка валидатора для ИНН
    innInput = new QLineEdit(this);
    QRegularExpression innRegex("[0-9]{12}");  // 12 цифр для ИНН
    QRegularExpressionValidator *innValidator = new QRegularExpressionValidator(innRegex, this);
    innInput->setValidator(innValidator);
    addresInput = new QLineEdit(this);

    formLayout->addRow("Название компании:", companyNameInput);
    formLayout->addRow("ИНН:", innInput);
    formLayout->addRow("Юридический адрес:", addresInput);

    // Группа полей контакт
    lastNameInput = new QLineEdit(this);
    firstNameInput = new QLineEdit(this);
    middleNameInput = new QLineEdit(this);

    // Маска для ввода телефона
    phoneInput = new QLineEdit(this);
    phoneInput->setPlaceholderText("Телефон (например, +7-(999)999-99-99)");
    phoneInput->setInputMask("+7 (999) 999-99-99;_");  // маска для телефонного ввода

    emailInput = new QLineEdit(this);

    formLayout->addRow("Фамилия:", lastNameInput);
    formLayout->addRow("Имя:", firstNameInput);
    formLayout->addRow("Отчество:", middleNameInput);
    formLayout->addRow("Телефон:", phoneInput);
    formLayout->addRow("Электронная почта:", emailInput);

    // Поле заметок
    notesinput = new QTextEdit(this);

    formLayout->addRow("Комментарии:", notesinput);

    QPushButton *saveBitton = new QPushButton("Сохранить", this);

    connect(saveBitton, &QPushButton::clicked, this, &AddClientDialog::onSaveButtonClicked);

    formLayout->addWidget(saveBitton);  // добавляем кнопку в форму

    setLayout(formLayout);  // форма как основной макет диалога
}

void AddClientDialog::onSaveButtonClicked()
{
    // Логика сохранения данных о клиенте в БД (сделать проверку на наличие клиента уже в БД)
    QMessageBox::information(this, "Успех!", "Данные о клиенте успешно сохранены");
    accept();
}
