#include "fenetre.h"
Fenetre::Fenetre(QWidget *parent) : QWidget(parent)
{
    ConfigurationFenetre();
    resize(1173, 904);
    TitreDeLaFenetre();
    pscene = new Scene(0, 0, 1100, 850);
    ptrvue = new Vue(pscene,this);
    CreerLeMenu();
    pscene->InitPtrVue(ptrvue);
    pscene->InitialiserScene( nouveau, quitter, ligneinfo1);
}
Fenetre::~Fenetre()
{
    delete layoutdroite;
    delete layoutgraphique;
    delete layinfo;
    delete toutLayout;
    delete pscene;
    delete ptrvue;
}
void Fenetre::ConfigurationFenetre()
{
    QColor valfond;
    valfond.setNamedColor("#3c6483");
    QPalette fond;
    fond.setColor( QPalette::Active,   QPalette::Window,valfond);
    fond.setColor( QPalette::Inactive, QPalette::Window,valfond);
    QWidget::setPalette(fond);
}
void Fenetre::TitreDeLaFenetre()
{
    phrtmp.clear();
    phrtmp.append("Test QStateParallele");
    setWindowTitle(phrtmp);
}
void Fenetre::CreerUnBouton( QToolButton *qbt, const QString &icone, const QString &msg, int tailleicone)
{
    QString ptmp(icone);
    if(ptmp.isEmpty()){ ptmp = ":/icone/apropos.png";}
    qbt->setIcon( QIcon(QPixmap(ptmp)));
    qbt->setIconSize( QSize (tailleicone,tailleicone));
    qbt->setToolTip(msg);
}
QVBoxLayout* Fenetre::BarreBouton()
{
    int htico = 35;
    QVBoxLayout *barrevert = new QVBoxLayout;
    nouveau = new QToolButton;
    CreerUnBouton( nouveau, ":/general/nouveau.png","démarrer une nouvelle session", htico);
      barrevert->addWidget(nouveau);
    quitter = new QToolButton;
    CreerUnBouton( quitter, ":/general/quitter.png", "quitter le jeu", htico);
      barrevert->addWidget(quitter);
    return barrevert;
}
void Fenetre::CreerLeMenu()
{
    layoutgraphique = new QVBoxLayout;
    layoutgraphique->addWidget(ptrvue);
    layoutdroite = new QGridLayout;
    layoutdroite->addLayout(BarreBouton(),1,0);
    layinfo = new QGridLayout;
    ligneinfo1 = new QLineEdit( QString("Ligne d'information"));
    layinfo->addWidget(ligneinfo1,0,0, Qt::AlignVCenter);
    toutLayout = new QGridLayout;
    toutLayout->addLayout(layoutgraphique, 0, 0);
    toutLayout->addLayout(layoutdroite, 0, 1);
    toutLayout->addLayout(layinfo, 1, 0);
    setLayout(toutLayout);
}
