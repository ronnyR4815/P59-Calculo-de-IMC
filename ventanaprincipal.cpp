#include "ventanaprincipal.h"
#include "ui_ventanaprincipal.h"

VentanaPrincipal::VentanaPrincipal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::VentanaPrincipal)
{
    ui->setupUi(this);
    this->altura = 0;
    this->peso = 0;
    this->fecha = "";
}

VentanaPrincipal::~VentanaPrincipal()
{
    delete ui;
}

void VentanaPrincipal::on_btn_calcular_released()
{
    float imc;
    QString clasificacion;
    altura = ui->in_altura->text().toFloat();
    peso = ui->in_peso->text().toFloat();
    // Enviar los datos a la clase calculo
    calculoimc = new Calculoimc(peso, altura);
    // Recibir los calculos y la clasificacion del IMC
    imc = calculoimc->calcular();
    ui->out_imc->setText(QString::number(imc, 'f', 2));

    ui->out_pesoAc->setText(QString::number(imc, 'f', 2) + " kg");

    guardar();
}

void VentanaPrincipal::guardar()
{
    /* Guardar archivo en el
     * directorio del programa */

    QString path = QDir::home().currentPath() + "/imc.txt";
    // Crear un objeto QFile
    QFile archivo(path);

    // Abrir archivo para escritura
    if(archivo.open(QFile::ReadWrite | QFile::Text)){
        // Crear un "stream" de texto (flujo)
        QTextStream datos(&archivo);

        QString info;
        info = datos.readAll();

        datos << "Fecha: " << ui->in_fecha->text() << endl;
        datos << "Peso: " << ui->in_peso->text() << endl;
        datos << "Altura: " << ui->in_altura->text() << endl << endl;

        ui->statusbar->showMessage("Datos almacenados correctamente!", 3000);
    }else{
        // Mensaje de error si no se puede abrir el archivo
        QMessageBox::warning(
                    this,
                    "Guardar informacion",
                    "No se pudo guardar la informacion");
    }
    // Cerrar el archivo
    archivo.close();
}
