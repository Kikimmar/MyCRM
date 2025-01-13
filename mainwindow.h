#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>
#include <QStandardItemModel>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onAddClientButtonClicked();  // слот для обработки кнопки "Добавить клиента"
    void onTableViewDoubleClicked(const QModelIndex &index);

private:
    QVBoxLayout *layout;
    QTableView *tableView;
    QPushButton *addClientButton;  // кнопка "Добавить клиента"
    QStandardItemModel *model;

    void updateClientList();
    // void setupTableView();
};
#endif // MAINWINDOW_H
