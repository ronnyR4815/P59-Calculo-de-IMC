#include "calculoimc.h"

Calculoimc::Calculoimc(QObject *parent) : QObject(parent)
{
    this->m_peso = 0;
    this->m_altura = 0;
}

Calculoimc::Calculoimc(float peso, float altura) : m_peso(peso),
    m_altura(altura)
{}

float Calculoimc::peso() const
{
    return m_peso;
}

void Calculoimc::setPeso(float newPeso)
{
    m_peso = newPeso;
}

float Calculoimc::altura() const
{
    return m_altura;
}

void Calculoimc::setAltura(float newAltura)
{
    m_altura = newAltura;
}

float Calculoimc::calcular()
{
    return peso() / pow(altura(), 2);
}

QString Calculoimc::clasificacion()
{
    if(calcular() < 18.5){
        return "Bajo Peso";
    }else if(calcular() >= 18.5 && calcular() < 25){
        return "Normal";
    }else if(calcular() >= 25 && calcular() < 30){
        return "Sobrepeso";
    }else if(calcular() >= 30 && calcular() < 35){
        return "Obesidad I";
    }else if(calcular() >= 35 && calcular() < 40){
        return "Obesidad II";
    }else if(calcular() >= 40){
        return "Obesidad III";
    }
    return "";
}
