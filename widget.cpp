#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->saveFinButton->setEnabled(false);
    ui->sliderHaar->setEnabled(false);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::browseInputPath()
{
    width = 0;
    height = 0;
    inputPath = QFileDialog::getOpenFileName(this, "Ouvrir un fichier", QString(), "Images (*.bmp *.jpg)");

    imageImportee = QImage(inputPath);
    if(imageImportee.isNull())
    {

        return;
    }

    width = imageImportee.width();
    height = imageImportee.height();

    if  ( estPuissanceDe2(width) && estPuissanceDe2(height) )
    {
 
        QPixmap monPixmap;
        monPixmap = QPixmap::fromImage(imageImportee);
        ui->labelImage->setPixmap(monPixmap);
        int dimMinimum;
        (width<height) ? (dimMinimum=width) : (dimMinimum=height);
        maxIterations = (int)( (float) ( (float) log10(dimMinimum) / (float)log10(2) ) );
        ui->sliderHaar->setMaximum(maxIterations);
        ui->sliderHaar->setEnabled(true);

        matrice = new unsigned char* [width];
        for(int i=0; i<width; ++i)
        {
                matrice[i] = new unsigned char [height];
        }
        
        for(int i=0; i<width; ++i)
        {
            for(int j=0; j<height; ++j)
            {
                matrice[i][j]=imageImportee.pixel(i, j);
            }
        }
        matriceHaar = haarMatrice(matrice, width, height, dimMinimum);
    }
    else QMessageBox::warning(this, "Erreur", "Image non valide");
}

void Widget::haarNb(int valIterations)
{
    float** traitement = haarMatrice(matrice, width, height, valIterations);
    unsigned char** matrice_affichee = allouerMatriceChar(width, height);

    redresserErreurMatrice(traitement, matrice_affichee, width/pow(2,valIterations), height/pow(2,valIterations), width, height);

    imageAffichee = imageImportee;
    for(int i=0; i<width; ++i)
    {
        for(int j=0; j<height; ++j)
        {
            imageAffichee.setPixel(i, j, matrice_affichee[i][j]);
        }
    }

    QPixmap monPixmap;
    monPixmap = QPixmap::fromImage(imageAffichee);
    ui->labelImage->setPixmap(monPixmap);

    desallouerMatrice(matrice_affichee, width);
    desallouerMatrice(traitement, width);
}

void Widget::unhaar()
{
    float seuil = ui->valSeuil->value() / 100.0;
    float max = determinerValeurMax(matriceHaar, width, height);
    float taux = appliquerSeuil(matriceHaar, seuil*max, width, height) * 100;
    ui->valTaux->setNum(taux);

    unsigned char** traitement = reconstructionMatrice(matriceHaar, width, height, maxIterations);

    imageFinale = imageImportee;
    for(int i=0; i<width; ++i)
    {
        for(int j=0; j<height; ++j)
            imageFinale.setPixel(i, j, traitement[i][j]);
    }

    imageAffichee = imageFinale;
    QPixmap monPixmap;
    monPixmap = QPixmap::fromImage(imageAffichee);
    ui->labelImage->setPixmap(monPixmap);

    desallouerMatrice(traitement, width);

    ui->saveFinButton->setEnabled(true);
}

void Widget::saveFinale()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.bmp)");
    imageFinale.save(fichier);
}

void Widget::saveAffichee()
{
    QString fichier = QFileDialog::getSaveFileName(this, "Enregistrer un fichier", QString(), "Images (*.bmp)");
    imageAffichee.save(fichier);
}
