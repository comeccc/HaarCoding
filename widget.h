#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtGui>
#include "include.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void browseInputPath();
    void haarNb(int);
    void unhaar();
    void saveFinale();
    void saveAffichee();
    
private:
    Ui::Widget *ui;
    int maxIterations;
    QString inputPath;
    QImage imageImportee;
    unsigned char** matrice;
    float** matriceHaar;
    int width;
    int height;
    QImage imageFinale;
    QImage imageAffichee;
};

#endif // WIDGET_H
