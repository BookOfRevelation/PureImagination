#include "mainwindow.h"
#include <QApplication>

#include <stdio.h>
#include <QDebug>
#include <QSound>
#include <QSplashScreen>
#include "purecore.h"
#include "roidialog.h"
#include <aquila/global.h>
#include <aquila/source/WaveFile.h>
#include <iostream>

//#define PI_TEST
#include <string>
#include <cmath>
#include <cstdlib>
float __closest_keypt(float, float*, int, float, bool);
float __modulo(float, float, bool);

float newPixel(float oldPixel, float* keypts, int nbkeypts, float delta, float lim_val, bool is_modulo)
{
        float closest_keypt = __closest_keypt(oldPixel, keypts, nbkeypts, lim_val, is_modulo);
    if(__modulo(std::fabs(oldPixel - closest_keypt), lim_val, is_modulo) < delta)
            return oldPixel;
        if(!is_modulo)
            return (oldPixel < closest_keypt) ? std::max(0.0f, closest_keypt-delta) : std::min(closest_keypt+delta, lim_val-1);
        if(std::fabs(oldPixel - closest_keypt) < lim_val/2.f)
            return (oldPixel < closest_keypt) ? fmod(closest_keypt-delta+lim_val,lim_val) : fmod(closest_keypt+delta+lim_val,lim_val);
        return (oldPixel < closest_keypt) ? fmod(closest_keypt+delta+lim_val,lim_val) : fmod(closest_keypt-delta+lim_val,lim_val);
}

float __closest_keypt(float oldPixel, float* keypts, int nbkeypts, float lim_val, bool is_modulo)
{
        float res=0;
        float mindist=lim_val;
        for(int i=0 ; i<nbkeypts ; ++i) {
            float dist = __modulo(std::fabs(oldPixel - keypts[i]), lim_val, is_modulo);
            if(dist < mindist){
                mindist = dist;
                res = keypts[i];
            }
        }
    return res;
}

float __modulo(float val, float lim_val, bool is_modulo)
{
    return (is_modulo ? lim_val/2.f - std::fabs(val - lim_val/2.f) : val);
}


void test()
{
    float* kpts = new float[51];
    kpts[0] = 30.f;

    float* sv = new float[5];
    sv[0] = 10;
    sv[4] = 25;
    sv[1] = 40;
    sv[2] = 80;
    sv[3] = 90;

    const float delta = 5;

    QImage img("C:\\Users\\Bastien\\Pictures\\vision.jpg");

    for(int i = 0 ; i < img.width() ; ++i)
    {
        for(int j = 0 ; j < img.height() ; ++j)
        {
            QColor px = img.pixelColor(i,j).toHsv();

            px.setHsv(newPixel(px.hue(), kpts, 1, delta, 360.f, true), newPixel(px.saturation(), sv, 5, delta*200, 100.0f, false), newPixel(px.value(), sv, 5, delta*200, 100.0f, false));

            img.setPixelColor(i, j, QColor::fromHsv(px.hue(), px.saturation(), px.value()));
        }
    }

    img.save("G:\\result.jpg");


    delete[] kpts;
}


int main(int argc, char *argv[])
{

    PureCore::initRNG();

#ifdef PI_TEST
    test();
    return 0;
#else

    QVector<QString> rde;
    rde.push_back("");

    rde.push_back("bitcrush");
    rde.push_back("downsampling");
    rde.push_back("retrigger");
    rde.push_back("ghost");
    rde.push_back("old");

    QApplication a(argc, argv);

    QString rdstr = rde.at(PureCore::getRandom(0, rde.size() -1));
    QSplashScreen ss(QPixmap(QString(":res/pisplash%1.jpg").arg(rdstr)));
    ss.show();
    a.processEvents();


    QSound ms(QString(":res/jinggle%1.wav").arg(rdstr));
    ms.play();


    MainWindow w;
    w.show();
    ss.finish(&w);

    return a.exec();
#endif
}
