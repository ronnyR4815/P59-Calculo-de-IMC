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

    // Iniciar la etiqueta de clasificacion invisible
    ui->out_clasificacion->setVisible(false);
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
    clasificacion = calculoimc->clasificacion();

    ui->out_imc->setText(QString::number(imc, 'f', 2));
    ui->out_pesoAc->setText(QString::number(peso, 'f', 2) + " kg");

    clasificarImc(imc, clasificacion);

    guardar();
}

void VentanaPrincipal::clasificarImc(float imc, QString clasificacion)
{
    // Sobreescribir etiqueta con la clasificacion del IMC
    ui->out_clasificacion->setText(clasificacion);
    ui->out_bar->setValue(imc);

    if(imc < 16){
        ui->out_clasificacion->setStyleSheet("color: rgb(176, 211, 205)");
        ui->out_bar->setValue(ui->out_bar->minimum()+1);
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(176, 211, 205);}"));
    }else if(imc >= 16 && imc < 18.5){
        ui->out_clasificacion->setStyleSheet("color: rgb(76, 108, 148)");
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(76, 108, 148);}"));
    }else if(imc >= 18.5 && imc < 25){
        ui->out_clasificacion->setStyleSheet("color: rgb(117, 221, 119)");
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(117, 221, 119);}"));
    }else if(imc >= 25 && imc < 30){
        ui->out_clasificacion->setStyleSheet("color: rgb(220, 230, 130)");
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(220, 230, 130);}"));
    }else if(imc >= 30 && imc < 40){
        ui->out_clasificacion->setStyleSheet("color: rgb(254, 181, 70)");
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(254, 181, 70);}"));
    }else if(imc >= 40){
        ui->out_clasificacion->setStyleSheet("color: rgb(234, 68, 78)");
        ui->out_bar->setStyleSheet(QString::fromUtf8("QProgressBar::chunk{background-color: rgb(234, 68, 78);}"));
        ui->out_bar->setValue(ui->out_bar->maximum());
    }

    ui->out_clasificacion->setVisible(true);

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

        QString info = "", peso = "";
        float pesoMax = 0.00, pesoAc = 0, pesoMin = 0.00;

        while(!datos.atEnd()){
            info = datos.readLine();
            if(info.contains("Peso:")){
                peso = datos.readLine();
                // Buscar mayor y menor peso
                pesoAc = peso.toFloat();
                pesoMin = peso.toFloat();
                pesoMax = peso.toFloat();

                if(pesoAc >= pesoMax){
                    pesoMax = pesoAc;
                    ui->out_pesoMax->setText(QString::number(pesoMax) + " kg");
                }
                if(pesoAc <= pesoMax){
                    pesoMin = pesoAc;
                    ui->out_pesoMin->setText(QString::number(pesoMin) + " kg");
                }
            }
        }

        datos << "| Fecha: " << ui->in_fecha->text() << " |" << endl;
        datos << "Peso: " << endl;
        datos << ui->in_peso->text() << endl;
        datos << "Altura: " << endl;
        datos << ui->in_altura->text() << endl << endl;

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
