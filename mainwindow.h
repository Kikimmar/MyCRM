#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QMessageBox>
#include <QPointer>
#include <QStandardItemModel>

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
    QPointer<QTableView> tableView;
    QPointer<QPushButton> addClientButton;  // кнопка "Добавить клиента"
    QStandardItemModel *model;

    void updateClientList();
};
#endif // MAINWINDOW_H
