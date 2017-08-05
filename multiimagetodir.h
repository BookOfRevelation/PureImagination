#ifndef MULTIIMAGETODIR_H
#define MULTIIMAGETODIR_H

#include <QtWidgets>
#include "datawidget.h"

class MultiImageToDir : public DataWidget
{

    Q_OBJECT

public:
    MultiImageToDir();
    ~MultiImageToDir();

    QVector<QString> imagePaths;
    QString targetPath;

    bool isBinded() const;

public slots:
    void onInput();
    void onOutput();

private:

    QLineEdit* inputLe;
    QLineEdit* outputLe;
};

#endif // MULTIIMAGETODIR_H
