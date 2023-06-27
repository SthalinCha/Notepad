#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "acerca.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QTextStream>
#include <QStatusBar>
#include <QMessageBox>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionAbrir_triggered();
    void on_actionSalir_triggered();
    void on_actionGuardar_triggered();

    void on_actionNuevo_triggered();

    void on_actionAcerca_de_triggered();

private:
    Ui::MainWindow *ui;
    void campoTexto();
    void updateStatusBar();
    QString currentFilePath;
};
#endif // MAINWINDOW_H
