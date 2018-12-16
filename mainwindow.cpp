#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("RAPID : FLIGHT FINDER");
    setFixedSize(1991,1173);
    finder = new dijkstra("flightData.xml");
    connectSignalsToSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete finder;
}

void MainWindow::findPressed()
{
    ui->itineraryField->clear();
    if(ui->sourceBox->toPlainText() == ui->destinationBox->toPlainText())
    {
        QMessageBox::warning(this,"WARNING","Destination and Source Airport codes must be different and non-empty!");
        return;
    }
    try
    {
        finder->findShortest(ui->sourceBox->toPlainText().toInt(),ui->destinationBox->toPlainText().toInt());
        finder->displayItinerary(ui->itineraryField,ui->sourceBox->toPlainText().toInt(),
                                 ui->destinationBox->toPlainText().toInt());
    }
    catch(d_errors e)
    {
        QMessageBox::warning(this,"WARNING","Unable to find route! Please try a different airport code");
    }
}

void MainWindow::printPressed()
{
    QString toSave = QFileDialog::getSaveFileName(this,"save an itinerary file");
    try
    {
        finder->printItinerary(toSave.toStdString(), ui->sourceBox->toPlainText().toInt(),
                               ui->destinationBox->toPlainText().toInt());
        QMessageBox::information(this,"SUCCESS","Itinerary successfully saved!");
    }
    catch(d_errors)
    {
        QMessageBox::warning(this,"WARNING","Error finding route! Please try again.");
    }
}

void MainWindow::connectSignalsToSlots()
{
    connect(ui->findButton,SIGNAL(pressed()),this,SLOT(findPressed()));
    connect(ui->printButton,SIGNAL(pressed()),this,SLOT(printPressed()));
}
