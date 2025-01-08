#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QListView>
#include <QMessageBox>
#include <QPointer>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddClientButtonClicked();  // слот для обработки кнопки "Добавить клиента"

private:
    QPointer<QVBoxLayout> layout;
    QPointer<QListView> listView;
    QPointer<QPushButton> addClientButton;  // кнопка "Добавить клиента"

    void updateClientList();
};
#endif // MAINWINDOW_H
