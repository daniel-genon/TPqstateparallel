#ifndef OBJETMOBILE_H
#define OBJETMOBILE_H

#include "objetimage.h"
#include <QVariantAnimation>
#include <QStateMachine>
class ObjetMobile : public ObjetImage
{
Q_OBJECT
public:
    ObjetMobile();
    ~ObjetMobile();
    void BougeToi();
    void Stop();
    quint8 ValeurPas() const;
    void InitPas( quint8 vpas );
    void InitDirection( int v);
    int  CodeDirection();
    bool Immobile() const;
    bool Mobile() const;
    bool VaADroite() const;
    bool NeVaPasADroite() const;
    bool VaAGauche() const;
    bool NeVaPasAGauche() const;
    bool VaEnHaut() const;
    bool VaEnBas() const;
    bool NeVaPasEnHaut() const;
    bool NeVaPasEnBas() const;
    virtual void FixerObjet();
protected:
    QVariantAnimation *animationdelobjet;
    QStateMachine *machine;
    int  direction;
private:
    //0=fixe, gah=Qt::Key_4, drt=Qt::Key_6,
    //        hau=Qt::Key_8, bas=Qt::Key_2
    quint8 pas;
};

#endif // OBJETMOBILE_H
