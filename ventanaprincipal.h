#ifndef VENTANAPRINCIPAL_H
#define VENTANAPRINCIPAL_H

#include <QMainWindow>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>

#include "calculoimc.h"

QT_BEGIN_NAMESPACE
namespace Ui { class VentanaPrincipal; }
QT_END_NAMESPACE

class VentanaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    VentanaPrincipal(QWidget *parent = nullptr);
    ~VentanaPrincipal();

private slots:
    void on_btn_calcular_released();

private:
    Ui::VentanaPrincipal *ui;
    Calculoimc *calculoimc;
    float altura;
    float peso;
    QString fecha;

    void guardar();
};
#endif // VENTANAPRINCIPAL_H
