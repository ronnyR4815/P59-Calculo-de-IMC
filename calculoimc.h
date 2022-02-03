#ifndef CALCULOIMC_H
#define CALCULOIMC_H

#include <QObject>
#include <math.h>

class Calculoimc : public QObject
{
    Q_OBJECT
public:
    explicit Calculoimc(QObject *parent = nullptr);
    Calculoimc(float peso, float altura);

    float calcular();
    QString clasificacion();

    float peso() const;
    void setPeso(float newPeso);
    float altura() const;
    void setAltura(float newAltura);

private:
    float m_peso;
    float m_altura;

signals:

};

#endif // CALCULOIMC_H
