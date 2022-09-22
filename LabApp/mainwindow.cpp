#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonRun_clicked()
{
    double b = ui->lineEditXb->text().toDouble();
    double u0 = ui->lineEditU0->text().toDouble();
    double N = ui->lineEditN->text().toInt();
    double h0 = ui->lineEditH0->text().toDouble();
    double eps = ui->lineEditEPS->text().toDouble();
    bool ctrlLP = ui->radioButtonCtrlLP->isChecked();

    TestWork T(b, u0, h0, N, ctrlLP);
    T.Run();
    QVector<double> x = QVector<double>(T.grid.begin(), T.grid.end());
    QVector<double> y = QVector<double>(T.final_num_values.begin(), T.final_num_values.end());

    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->xAxis->setRange(0, T.right_border);
    ui->graph->yAxis->setRange(T.final_num_values.front(),T.final_num_values.back());
    ui->graph->replot();
}

