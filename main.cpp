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
        QString valor = modelo.data(index, docentryRole).toString();
        qDebug() << "Modelo recebido " << valor;
    });
    QObject::connect(&cli, &ClientSocket::erroConexao,
                     [=]() {
        qApp->quit();
    });

    cli.receberModelo("localhost", 53593);

    return a.exec();
}
