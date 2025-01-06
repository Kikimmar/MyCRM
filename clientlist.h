#ifndef CLIENTLIST_H
#define CLIENTLIST_H

#include <QWidget>
#include <QPushButton>

class ClientList : public QWidget
{
    Q_OBJECT

public:
    ClientList(QWidget *parent = nullptr);

private slots:
    void onAddClientButtonClicked();  // слот для обработки кнопки "Добавить клиента"

private:
    QPushButton *addClientButton;  // кнопка "Добавить клиента"
};

#endif // CLIENTLIST_H
