#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QBoxLayout>
#include <QPushButton>
#include <QProgressBar>
#include <QStatusBar>
#include <QTabWidget>
#include <QToolBar>
#include <QTreeWidget>
#include <QLineEdit>
#include "pureeffect.h"
#include "pureview.h"
#include "purescene.h"
#include "helpzone.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void addEffect(PureEffect* e, const QString &name);

public slots:
    void makeProgress(int cur, int max);

    void effectProcessed(bool success);

    void run();

    void clear();

private slots:

    void showEffect(PureEffect* e);

    void filterList(const QString& filter);

private:

    QVector<PureEffect*> effects;
    QVector<QPushButton*> btns;
    QWidget* central;
    QBoxLayout* mainLt;
    QBoxLayout* effectLt;

    QTabWidget* mainTab;

    PureScene* scene;
    PureView* view;

    QWidget* effectPart;

    HelpZone* hz;

    QLineEdit* researchZone;

    QTreeWidget* effectTree;
    QTreeWidgetItem* loaderItem;
    QTreeWidgetItem* filterItem;
    QTreeWidgetItem* transformaterItem;
    QTreeWidgetItem* saverItem;

    QProgressBar* pbar;

    QStatusBar* statusbar;


    int infoPosition;
    int dataPosition;
    int parameterPosition;

    void activeEffect(bool active);

    PureEffect* currentEffect;

    void updateEnabledEffects();
};

#endif // MAINWINDOW_H
