#include "mainwindow.h"
#include "logindialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //  Создаем диалог для ввода логина
    LoginDialog loginDialog;

    // Подключаем сигнал rejected для выхода из приложения
    QObject::connect(&loginDialog, &QDialog::rejected, &app, &QCoreApplication::quit);

    // Запускаем диалог в модальном режиме
    if (loginDialog.exec() == QDialog::Accepted)
    {
        // Если пользователь зашел успешно, создаем главное окно
        MainWindow window;
        window.show();
        return app.exec();
    }
    // Если диалог был закрыт, завершаем приложение
    return 0;
}
