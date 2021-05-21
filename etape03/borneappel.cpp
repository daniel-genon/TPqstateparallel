#include "borneappel.h"

BorneAppel::BorneAppel(const QString &vcoul)
{
    InitImage(QString(vcoul));
    setZValue(2);
}
