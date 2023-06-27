#include "mainwindow.h"
#include "ui_mainwindow.h"

QString text;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    campoTexto();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbrir_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Abrir Archivo"),QDir::homePath(), "Dat Files (*.dat)");

    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo"));
            return;
        }
        QDataStream in(&file);

        in>>text;
        file.close();

        ui->textEdit->setText(text);
        currentFilePath = fileName;  // Almacena la ruta del archivo.
    }
}


void MainWindow::on_actionSalir_triggered()
{
    QString textoActual= ui->textEdit->toPlainText();
    if (textoActual!=text) {
        QMessageBox::StandardButton respuesta;

        respuesta=QMessageBox::question(this, tr("Mensaje"), tr("Hay cambios en el archivo, Desea Guardar?"),QMessageBox::Yes|QMessageBox::No);
        if(respuesta==QMessageBox::Yes){
            MainWindow::on_actionGuardar_triggered();

        }


    }
    this->close();

}


void MainWindow::on_actionGuardar_triggered()
{
    QString fileName;
    if (!currentFilePath.isEmpty())
    {
        fileName=currentFilePath;

    }
    else
    {
        //Guardar como
        fileName = QFileDialog::getSaveFileName(nullptr, tr("Guardar Archivo"), QDir::homePath(), "DAT files (*.dat)");
        fileName+=".dat";
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, tr("Error"), tr("No se pudo abrir el archivo"));
        return;
    }
    QDataStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();
    QMessageBox::information(this, tr("Mensaje"), tr("Guardado con exito"));
}

void MainWindow::updateStatusBar()
{
    statusBar()->setFixedHeight(30);
    statusBar()->setStyleSheet("font-size: 20px");
    int characterCount = ui->textEdit->toPlainText().length();
    statusBar()->showMessage(tr("Contador: %1").arg(characterCount));

}

void MainWindow::campoTexto()
{
    connect(ui->textEdit, &QTextEdit::textChanged, this, &MainWindow::updateStatusBar);
}

void MainWindow::on_actionNuevo_triggered()
{

    QMessageBox::StandardButton respuesta;

    respuesta=QMessageBox::question(this, tr("Mensaje"), tr("Hay cambios en el archivo, Desea Guardar?"),QMessageBox::Yes|QMessageBox::No);
    if(respuesta==QMessageBox::Yes){
        MainWindow::on_actionGuardar_triggered();

    }
        ui->textEdit->setText("");
        currentFilePath="";

}


void MainWindow::on_actionAcerca_de_triggered()
{
    Acerca ventana;
    ventana.exec();
}

