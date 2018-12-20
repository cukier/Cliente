#include <QCoreApplication>
#include <QDebug>
#include <QModelIndex>

#include "clientsocket.h"
#include "clistmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ClientSocket cli("mauricio", "mauricio1", &a);
    CListModel modelo(&a);

    QObject::connect(&cli, &ClientSocket::novoModelo,
                     [=] (const CListModel &modelo) {
        QModelIndex index = modelo.index(0, 0);
        qDebug() << modelo.data(index).toString();
    });
    QObject::connect(&cli, &ClientSocket::erroConexao,
                     [=]() {
        qApp->quit();
    });

    cli.receberModelo("localhost", 53593);

    return a.exec();
}
