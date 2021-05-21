#ifndef BORNEAPPEL_H
#define BORNEAPPEL_H

#include "../objetimage.h"
class BorneAppel : public ObjetImage
{
public:
    BorneAppel( const QString &vcoul);
};

typedef QList<BorneAppel*> LBorne;

#endif // BORNEAPPEL_H
