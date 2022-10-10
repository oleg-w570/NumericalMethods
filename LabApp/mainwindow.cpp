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

    TestWork T(b, u0, h0, N, ctrlLP, eps);
    T.Run();
    QVector<double> x = QVector<double>(T.grid.begin(), T.grid.end());
    QVector<double> y = QVector<double>(T.final_num_values.begin(), T.final_num_values.end());

    ui->graph->addGraph();
    ui->graph->graph(0)->setData(x, y);
    ui->graph->xAxis->setRange(0, T.right_border);
    ui->graph->yAxis->setRange(T.final_num_values.front(),T.final_num_values.back());
    ui->graph->replot();

    ui->tableWidget->clear();
    ui->tableWidget->setHorizontalHeaderLabels(QStringList() << "Xi" << "Vi" << "V2i" << "Vi - V2i" << "ОЛП" << "Hi" << "C1" << "C2" << "Ui" << "Ui - Vi");
    for (int i = 0; i < T.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(T.grid[i]));
        QTableWidgetItem *v = new QTableWidgetItem(QString::number(T.num_values[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(T.d_num_values[i]));
        QTableWidgetItem *diff = new QTableWidgetItem(QString::number(T.num_values[i] - T.d_num_values[i]));
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number((T.d_num_values[i] - T.num_values[i]) / 15 * 16));
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(T.grid_step[i]));
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(T.div2[i]));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(T.mult2[i]));
        QTableWidgetItem *u = new QTableWidgetItem(QString::number(T.true_values[i]));
        QTableWidgetItem *true_diff = new QTableWidgetItem(QString::number(T.true_values[i] - T.final_num_values[i]));

        ui->tableWidget->insertRow(i);
        ui->tableWidget->setItem(i, 0, x);
        ui->tableWidget->setItem(i, 1, v);
        ui->tableWidget->setItem(i, 2, v2);
        ui->tableWidget->setItem(i, 3, diff);
        ui->tableWidget->setItem(i, 4, OLP);
        ui->tableWidget->setItem(i, 5, h);
        ui->tableWidget->setItem(i, 6, c1);
        ui->tableWidget->setItem(i, 7, c2);
        ui->tableWidget->setItem(i, 8, u);
        ui->tableWidget->setItem(i, 9, true_diff);
    }
}

