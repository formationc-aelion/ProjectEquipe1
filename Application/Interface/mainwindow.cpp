#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Verouillage();
    ui->teInfo->setVisible(false);
    ui->pbMasquer->setVisible(false);


    QSqlDatabase db = QSqlDatabase::database("connexionBDDfilm");
    mFilmModel = new QSqlTableModel (this,db);
    mFilmModel->setTable("film");
    mFilmModel->select();

    mFilmSortingModel = new QSortFilterProxyModel(this);
    mFilmSortingModel->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    mFilmSortingModel->sort(1, Qt::AscendingOrder);
    mFilmSortingModel->setDynamicSortFilter(true);
    mFilmSortingModel->setSourceModel(mFilmModel);

    ui->lvListeRecherche->setModel(mFilmSortingModel);
    ui->lvListeRecherche->setModelColumn(1);


   QDataWidgetMapper *mapper = new QDataWidgetMapper;
    mapper->setModel(mFilmSortingModel);
    mapper->addMapping(ui->leTitre, 1);
    mapper->addMapping(ui->leAnnee, 2);
    mapper->addMapping(ui->leGenre, 3);
    mapper->addMapping(ui->leDuree, 4);
    mapper->addMapping(ui->leVO, 5);


    connect(ui->lvListeRecherche->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            mapper,
            SLOT(setCurrentModelIndex(QModelIndex)));

    connect(ui->lvListeRecherche->selectionModel(),SIGNAL(currentRowChanged (QModelIndex,QModelIndex)),
            this,
            SLOT(conversion_min_en_heure()));

    connect(ui->pbInfo,SIGNAL(clicked()),this,SLOT(apparition_texte()));
    connect(ui->pbMasquer,SIGNAL(clicked()),this,SLOT(masquer_texte()));

    connect(ui->pbSupprimer,SIGNAL(clicked()),this,SLOT(suppression()));

    connect(ui->pbAjouter,SIGNAL(clicked()),this, SLOT(ajouter_Film()));
     connect(ui->pbModifier,SIGNAL(clicked()),this, SLOT(modification()));

     connect(ui->leRecherche,SIGNAL(textChanged(QString)),this,SLOT(filtreRecherche(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Verouillage()
{
    ui->leTitre->setReadOnly(true);
    ui->leAnnee->setReadOnly(true);
    ui->leGenre->setReadOnly(true);
    ui->leDuree->setReadOnly(true);
    ui->leVO->setReadOnly(true);
}

void MainWindow::Deverouillage()
{
    ui->leTitre->setReadOnly(false);
    ui->leAnnee->setReadOnly(false);
    ui->leGenre->setReadOnly(false);
    ui->leDuree->setReadOnly(false);
    ui->leVO->setReadOnly(false);
}

void MainWindow::ajouter_Film()
{
    AjouterFilm af; // déclaration de la boîte de dialogue affichage
    af.exec(); // affichage de la fenêtre d'ajout
    //cf HUGO Film film = af.getDetails(); // stockage des info dans un objet film

}

void MainWindow::conversion_min_en_heure()
{
    QString conversion_en_heure = ui->leDuree->text();
    int chiffre = conversion_en_heure.toInt();

    qDebug () << chiffre;

    if (chiffre == 60)
    {
        conversion_en_heure = "1h";
        qDebug () << conversion_en_heure <<"condition 1h";
    }
    else if (chiffre > 60)
    {
        int a = conversion_en_heure.toInt();
        int resultat = a/60;
        int modulo = a%60;
        char heure = 'h';
        QString minutes = "min";;
        QString modulo_avec_zero = QString ("%1")
                .arg(modulo);

        if (modulo < 10)

        { modulo_avec_zero = QString("%1%2")
                    .arg("0")
                    .arg(modulo);
            qDebug () << modulo_avec_zero << "condition ou module<10";
        }


        conversion_en_heure = QString ("%1%2%3%4")
                .arg(resultat)
                .arg(heure)
                .arg(modulo_avec_zero)
                .arg(minutes);
        qDebug () << conversion_en_heure << "condition 1het qques min";
    }
    else {
        conversion_en_heure += "min";
        qDebug () << conversion_en_heure << "condition min";
    }

    ui->leDuree->setText(conversion_en_heure);
    qDebug () << conversion_en_heure << "resultat apres conversion";


}

void MainWindow::apparition_texte()
{
    ui->teInfo->setVisible(true);
    ui->pbMasquer->setVisible(true);
    ui->pbInfo->setHidden(true);

}

void MainWindow::suppression()
{
   int response = QMessageBox::critical(this,"Supprimer le fichier","Voulez-vous vraiment supprimer cette entrée de façon permanente?",
                         QMessageBox::Yes | QMessageBox::No);
   if (response == QMessageBox::Yes)
   {
       QModelIndex a_supprimer = ui->lvListeRecherche->currentIndex();
       mFilmSortingModel->removeRow(a_supprimer.row());
       ui->leTitre->clear();
       ui->leAnnee->clear();
       ui->leGenre->clear();
       ui->leDuree->clear();
       ui->leVO->clear();

       QMessageBox::information(this,"Suppression","Element supprimé");

       mFilmModel->select();
   }

}

void MainWindow::modification()
{
    Deverouillage();

}

void MainWindow::masquer_texte()
{
    ui->teInfo->setHidden(true);
    ui->pbMasquer->setHidden(true);
    ui->pbInfo->setVisible(true);
}

void MainWindow::filtreRecherche(QString tri)
{
    QString find ="*"+tri+"*";


    mFilmSortingModel->setFilterWildcard(find);
    mFilmSortingModel->setFilterKeyColumn(1);
}

