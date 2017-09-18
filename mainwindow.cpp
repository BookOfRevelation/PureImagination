#include "mainwindow.h"
#include "gempuzzleeffect.h"
#include "imagetoxyz.h"
#include "ghostfusioneffect.h"
#include "modulopusheffect.h"
#include "retriggereffect.h"
#include "visualcrusheffect.h"
#include "visualdownsamplingeffect.h"
#include "gradiantthresholdingeffect.h"
#include "vaporskyeffect.h"
#include "tanglefusioneffect.h"
#include "noizifiereffect.h"
#include "rgbtohsv.h"
#include "xyztoimg.h"
#include "hsvtorgb.h"
#include "oldvcreffect.h"
#include "compositioneffect.h"
#include "puretreeitem.h"
#include "imageloader.h"
#include "imagesaver.h"
#include "symbioticmesseffect.h"
#include "anaglypheffect.h"
#include "tiltshifteffect.h"
#include "gifloader.h"
#include "xyzloader.h"
//#include "wavloader.h"
//#include "wavbinimage.h"
#include "melteffect.h"
#include "subliminaleffect.h"
#include "gifsaver.h"
#include "purecommand.h"
#include <QSplashScreen>
#include <QSound>
#include <QCoreApplication>
#include <QTime>
#include <QMessageBox>
#include <QGraphicsBlurEffect>
#include "pureconfiguration.h"
#include <QDesktopServices>
#include "monitoringwidget.h"
#include "texttoimg.h"
#include "plaintextloader.h"
#include "scrollereffect.h"
#include "fragmenttoimage.h"
#include "imagetofragment.h"
#include "stalactiteeffect.h"
#include "xyzsaver.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    undoStack = new QUndoStack(this);


    setMouseTracking(true);

    QToolBar* tb = this->addToolBar("");
    QAction* newAct = tb->addAction(QIcon(":/res/runicon.png"), "Run", this, MainWindow::run);
    newAct->setShortcut(QKeySequence(tr("Ctrl+R")));
    QAction* clearAct = tb->addAction(QIcon(":/res/newicon.png"), "New", this, MainWindow::clear);
    clearAct->setShortcut(QKeySequence::New);

    QAction* undoAct = undoStack->createUndoAction(tb);
    undoAct->setShortcut(QKeySequence::Undo);
    QAction* redoAct = undoStack->createRedoAction(tb);
    redoAct->setShortcut(QKeySequence::Redo);
    undoAct->setIcon(QIcon(":/res/undoicon.png"));
    redoAct->setIcon(QIcon(":/res/redoicon.png"));
    tb->addActions(QList<QAction*>{undoAct, redoAct});

    connect(undoAct, &QAction::triggered, this, &MainWindow::updateEnabledEffects);
    connect(redoAct, &QAction::triggered, this, &MainWindow::updateEnabledEffects);




    currentEffect = nullptr;
    statusbar = new QStatusBar;

    this->setStatusBar(statusbar);

    effects.clear();
    btns.clear();
    central = new QWidget();
    mainLt = new QBoxLayout(QBoxLayout::LeftToRight);
    central->setLayout(mainLt);
    effectLt = new QBoxLayout(QBoxLayout::TopToBottom);

    effectTree = new QTreeWidget();
    effectTree->setColumnCount(1);
    effectTree->setHeaderItem(new QTreeWidgetItem(QStringList({"Name", "Input", "Output"})));

    loaderItem = new QTreeWidgetItem(QStringList("Loaders"));
    filterItem = new QTreeWidgetItem(QStringList("Filters"));
    transformaterItem = new QTreeWidgetItem(QStringList("Transformaters"));
    saverItem = new QTreeWidgetItem(QStringList("Savers"));

    effectTree->addTopLevelItems({loaderItem, filterItem, transformaterItem, saverItem});
    effectTree->setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum));

    //research zone
    QBoxLayout* sLt = new QBoxLayout(QBoxLayout::LeftToRight);
    researchZone = new QLineEdit();
    sLt->addWidget(new QLabel("Rechercher un effet :"));
    sLt->addWidget(researchZone);
    //end
    QBoxLayout* effzone = new QBoxLayout(QBoxLayout::TopToBottom);
    effzone->addLayout(sLt);
    effzone->addWidget(effectTree);
    hz = new HelpZone();
    //hz->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding));
    effzone->addWidget(hz);

    effectPart = new QWidget;
    effectPart->setLayout(effectLt);


    connect(researchZone, &QLineEdit::textChanged, this, &MainWindow::filterList);




    mainLt->addLayout(effzone);

    scene = new PureScene();
    view = new PureView();
    view->setScene(scene);
    mainLt->addWidget(view,1);

    connect(effectTree, QTreeWidget::itemDoubleClicked, this, [this](QTreeWidgetItem *item, int column)
    {
        if(!item->isDisabled())
        {
            Q_UNUSED(column);
            PureTreeItem* i = dynamic_cast<PureTreeItem*>(item);
            if(i)
            {
                PureEffect* e = i->getEffect();
                if(e->init())
                {
                    this->showEffect(e);
                    PureCore::currentOutput = e->getOutputType();
                    updateEnabledEffects();
                }

            }
        }

    });
    connect(effectTree, &QTreeWidget::itemClicked, this, [this](QTreeWidgetItem* item, int column)
    {
       Q_UNUSED(column);

        PureTreeItem* i = dynamic_cast<PureTreeItem*>(item);
        if(i)
        {
            hz->setWidget(i->getEffect()->getInfo().first, i->getEffect()->name);
        }
        else
        {
            QString str = item->text(0);
            QString desc = "";

            if(str == "Loaders")
            {
                desc = "Les effets 'Loader' permettent d'injecter\n des données de votre pc vers la chaîne\n de traitement."
                              "Une chaine de traitement \ndoit toujours commencer par un 'Loader'.";
            }
            else if(str == "Filters")
            {
                desc = "Les effets 'Filter' sont des effets de traitement\n"
                       " de données. Il permettent d'exécuter des algo-\n"
                       "rithmes"
                       "pour modifier les données d'entrées.";
            }
            else if(str == "Transformaters")
            {
                desc = "Les effets 'Transformater' permettent de convertir \n"
                       " certains type de données vers d'autres.\n";
            }
            else if(str == "Savers")
            {
                desc = "Les effets 'Saver' sauvegardent sur votre \n"
                       " PC le résultat de la chaîne de traitement.\n"
                       "Une chaîne de traitement doit toujours terminer\n"
                       "par un effet 'Saver'.";
            }
            hz->setWidget(str, desc);

        }
    });

    this->setCentralWidget(central);

    QTime dieTime= QTime::currentTime().addSecs(2);
        while (QTime::currentTime() < dieTime)
            QCoreApplication::processEvents(QEventLoop::AllEvents, 100);

        addEffect(new GemPuzzleEffect("GemPuzzle"));
        addEffect(new ModuloPushEffect("ModuloPush"));
        addEffect(new ImageToXYZ("ImageToXYZ"));
        //addEffect(new GhostFusionEffect( "GhostFusion"));
        addEffect(new RetriggerEffect("Retrigger") );
        addEffect(new VisualCrushEffect("VisualCrush") );
        addEffect(new VisualDownSamplingEffect("DownSampling") );
        //addEffect(new GradiantThresholdingEffect(), "GradiantThresholdin");
        //addEffect(new VaporSkyEffect(), "VaporSky");
        //addEffect(new TangleFusionEffect(), "TangleFusion");
        addEffect(new NoizifierEffect("Noizifier") );
        addEffect(new RgbToHsv("RgbToHsv") );
        addEffect(new HsvToRgb("HsvToRgb") );
        addEffect(new OldVcrEffect("OldVcr") );
        addEffect(new ImageLoader("Images") );
        addEffect(new ImageSaver("Images"));
        addEffect(new SymbioticMessEffect("SymbioticMess"));
        addEffect(new AnaglyphEffect("Anaglyph") );
        //addEffect(new TiltShiftEffect(), "TiltShifting");
        //addEffect(new WavLoader("Wave") );
        //addEffect(new WavBinImage("Wave binary Image") );
        addEffect(new MeltEffect("MeltEffect") );
        addEffect(new CompositionEffect("Composition") );
        addEffect(new GifLoader("Animated Gif") );
        addEffect(new GifSaver("Animateg Gif") );
        addEffect(new SubliminalEffect("Subliminal Effect"));
        addEffect(new PlainTextLoader("Text"));
        addEffect(new TextToImg("TextToImage"));
        addEffect(new FragmentToImage("FragmentToImage"));
        addEffect(new ImageToFragment("ImageToFragment"));
        addEffect(new ScrollerEffect("Scrolling Effect"));
        addEffect(new StalactiteEffect("Dust"));
        addEffect(new XYZSaver("XYZ Saver"));
        addEffect(new XYZToImg("XYZToImage"));
        addEffect(new XYZLoader("XYZ Loader"));


        pbar = new QProgressBar;
        statusbar->addPermanentWidget(pbar);
        statusbar->addPermanentWidget(new MonitoringWidget());
        statusbar->showMessage("Ready.");

        updateEnabledEffects();

        this->resize(PureConfiguration::windowGeometry[0],PureConfiguration::windowGeometry[1]);
        this->move(PureConfiguration::windowGeometry[2], PureConfiguration::windowGeometry[3]);


}

MainWindow::~MainWindow()
{

    PureEffect* e;
    foreach (e, effects)
    {
        delete e;
    }

    effects.clear();
    PureConfiguration::windowGeometry[0] = this->width();
    PureConfiguration::windowGeometry[1] = this->height();
    PureConfiguration::windowGeometry[2] = this->pos().x();
    PureConfiguration::windowGeometry[3] = this->pos().y();
    PureConfiguration::saveConf();

}


void MainWindow::addEffect(PureEffect *e)
{
    QString name = e->name;
    PureCore::PureNature nat = e->getNature();
    QTreeWidgetItem* father = nullptr;
    switch(nat)
    {
    case PureCore::Loader:
        father = loaderItem;
        break;
    case PureCore::Filter:
        father = filterItem;
        break;
    case PureCore::Transformater:
        father = transformaterItem;
        break;
    case PureCore::Saver:
        father = saverItem;
        break;
    }
    PureTreeItem* child = new PureTreeItem;
    if(father)
    {
        child->setText(0, name);
        child->setText(1, PureCore::TypeToStr(e->getInputType()));
        child->setText(2, PureCore::TypeToStr(e->getOutputType()));
        child->setEffect(e);
        father->addChild(child);
    }


    effects.push_back(e);

    connect(this->scene, &PureScene::makeProgress, this, MainWindow::makeProgress);
    connect(this->scene, &PureScene::endChain, this, MainWindow::effectProcessed);
}


void MainWindow::makeProgress(int cur, int max)
{
    statusbar->showMessage("Computing...");
    pbar->setRange(0, max);
    pbar->setValue(cur);
}

void MainWindow::effectProcessed(bool success)
{
    pbar->setValue(pbar->maximum());
    if(success)
    {
         if(QMessageBox::information(this, "Success", "Processing suceeded.", QMessageBox::Ok | QMessageBox::Open) == QMessageBox::Open)
         {
            QDesktopServices::openUrl(QUrl(PureCore::lastTargetDir));
         }

    }
    else
    {
        QMessageBox::critical(this, "Failure", "Le traitement a échoué.");
    }

    statusbar->showMessage("Ready");

}


void MainWindow::activeEffect(bool active)
{
    QPushButton* b;
    foreach(b, btns)
    {
        b->setEnabled(active);
    }
}

void MainWindow::showEffect(PureEffect *e)
{
    CommandParameters* cmd = new CommandParameters();
    cmd->effect = e->clone();
    cmd->scene = scene;
    cmd->currentEffect = currentEffect;

    //will automatically call PureCommand::redo()
    undoStack->push(new PureCommand(cmd, undoStack));
}

void MainWindow::run()
{
    this->scene->run();
}


void MainWindow::updateEnabledEffects()
{
    if(PureCore::currentOutput == PureCore::NoType)
    {
        //start or end : allows only loaders
        for(int i  = 0 ; i < loaderItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = loaderItem->child(i);
            it->setDisabled(false);
        }
        for(int i  = 0 ; i < filterItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = filterItem->child(i);
            it->setDisabled(true);
        }
        for(int i  = 0 ; i < transformaterItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = transformaterItem->child(i);
            it->setDisabled(true);
        }
        for(int i  = 0 ; i < saverItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = saverItem->child(i);
            it->setDisabled(true);
        }
    }
    else
    {
        PureCore::PureType t = PureCore::currentOutput;
        for(int i  = 0 ; i < loaderItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = loaderItem->child(i);
            PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
            if(pi)
            {
               it->setDisabled(pi->getEffect()->getInputType() != t);
            }

        }
        for(int i  = 0 ; i < filterItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = filterItem->child(i);
            PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
            if(pi)
            {
               it->setDisabled(pi->getEffect()->getInputType() != t);
            }
        }
        for(int i  = 0 ; i < transformaterItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = transformaterItem->child(i);
            PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
            if(pi)
            {
               it->setDisabled(pi->getEffect()->getInputType() != t);
            }
        }
        for(int i  = 0 ; i < saverItem->childCount() ; ++i)
        {
            QTreeWidgetItem* it = saverItem->child(i);
            PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
            if(pi)
            {
               it->setDisabled(pi->getEffect()->getInputType() != t);
            }
        }
    }
}


void MainWindow::clear()
{

    if(QMessageBox::question(
                this,
                "Confirmation",
                "Êtes vous sûr de vouloir effacer le traitement actuel ?"
                ) == QMessageBox::Yes)
    {
        if(PureCore::currentData)
        {
            delete PureCore::currentData;
            PureCore::currentData = nullptr;

        }
        if(PureCore::noFragement)
        {
            delete PureCore::noFragement;
            PureCore::noFragement = nullptr;
        }
        PureCore::currentOutput = PureCore::NoType;
        scene->clean();

        for(int i = 0 ; i < undoStack->count() ; ++i)
        {
            undoStack->clear();
        }

        this->pbar->setValue(0);
        this->statusBar()->showMessage("Ready.");
        updateEnabledEffects();
    }
}



void MainWindow::filterList(const QString &filter)
{
    for(int i  = 0 ; i < loaderItem->childCount() ; ++i)
    {
        QTreeWidgetItem* it = loaderItem->child(i);
        PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
        if(pi)
        {
           it->setHidden(!it->text(0).contains(filter, Qt::CaseInsensitive));
        }

    }
    for(int i  = 0 ; i < filterItem->childCount() ; ++i)
    {
        QTreeWidgetItem* it = filterItem->child(i);
        PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
        if(pi)
        {
           it->setHidden(!it->text(0).contains(filter, Qt::CaseInsensitive));
        }
    }
    for(int i  = 0 ; i < transformaterItem->childCount() ; ++i)
    {
        QTreeWidgetItem* it = transformaterItem->child(i);
        PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
        if(pi)
        {
           it->setHidden(!it->text(0).contains(filter, Qt::CaseInsensitive));
        }
    }
    for(int i  = 0 ; i < saverItem->childCount() ; ++i)
    {
        QTreeWidgetItem* it = saverItem->child(i);
        PureTreeItem* pi = dynamic_cast<PureTreeItem*>(it);
        if(pi)
        {
           it->setHidden(!it->text(0).contains(filter, Qt::CaseInsensitive));;
        }
    }

}
