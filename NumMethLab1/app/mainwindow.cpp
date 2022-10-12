#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidgetTest->setHorizontalHeaderLabels(QStringList() << "Xi" << "Vi" << "V2i" << "Vi - V2i" << "ОЛП" << "Hi" << "C1" << "C2" << "Ui" << "|Ui - Vi|");
    ui->tableWidgetTest->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetMain1->setHorizontalHeaderLabels(QStringList() << "Xi" << "Vi" << "V2i" << "Vi - V2i" << "ОЛП" << "Hi" << "C1" << "C2");
    ui->tableWidgetMain1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    ui->tableWidgetMain2->setHorizontalHeaderLabels(QStringList() << "Xi" << "V1i" << "V1_2i" << "V1i - V1_2i" << "V2i" << "V2_2i" << "V2i - V2_2i" << "ОЛП" << "Hi" << "C1" << "C2");
    ui->tableWidgetMain2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonTestRun_clicked()
{
    double u0 = ui->lineEditTestU0->text().toDouble();
    double b = ui->lineEditTestB->text().toDouble();
    int N = ui->lineEditTestN->text().toInt();
    double h0 = ui->lineEditTestH0->text().toDouble();
    double eps = ui->lineEditTestLP->text().toDouble();
    bool ctrlLP = ui->radioButtonTestCLP->isChecked();

    TestWork T(b, u0, h0, N, ctrlLP, eps);
    T.Run();
    QVector<double> x = QVector<double>(T.grid.begin(), T.grid.end());
    QVector<double> y_num = QVector<double>(T.final_num_values.begin(), T.final_num_values.end());
    QVector<double> y_true = QVector<double>(T.true_values.begin(), T.true_values.end());
    const auto [min_y_num, max_y_num] = std::minmax_element(T.final_num_values.begin(), T.final_num_values.end());
    const auto [min_y_true, max_y_true] = std::minmax_element(T.true_values.begin(), T.true_values.end());

    ui->graphTestNum->addGraph();
    ui->graphTestNum->graph(0)->setData(x, y_num);
    ui->graphTestNum->xAxis->setRange(0, T.right_border);
    ui->graphTestNum->yAxis->setRange(*min_y_num, *max_y_num);
    ui->graphTestNum->replot();

    ui->graphTestTrue->addGraph();
    ui->graphTestTrue->graph(0)->setData(x, y_true);
    ui->graphTestTrue->xAxis->setRange(0, T.right_border);
    ui->graphTestTrue->yAxis->setRange(*min_y_true, *max_y_true);
    ui->graphTestTrue->replot();


    ui->tableWidgetTest->clearContents();
    ui->tableWidgetTest->setRowCount(0);

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
        QTableWidgetItem *true_diff = new QTableWidgetItem(QString::number(std::abs(T.true_values[i] - T.final_num_values[i])));
        ui->tableWidgetTest->insertRow(i);
        ui->tableWidgetTest->setItem(i, 0, x);
        ui->tableWidgetTest->setItem(i, 1, v);
        ui->tableWidgetTest->setItem(i, 2, v2);
        ui->tableWidgetTest->setItem(i, 3, diff);
        ui->tableWidgetTest->setItem(i, 4, OLP);
        ui->tableWidgetTest->setItem(i, 5, h);
        ui->tableWidgetTest->setItem(i, 6, c1);
        ui->tableWidgetTest->setItem(i, 7, c2);
        ui->tableWidgetTest->setItem(i, 8, u);
        ui->tableWidgetTest->setItem(i, 9, true_diff);
    }
}


void MainWindow::on_pushButtonMain1Run_clicked()
{
    double u0 = ui->lineEditMain1U0->text().toDouble();
    double b = ui->lineEditMain1B->text().toDouble();
    double h0 = ui->lineEditMain1H0->text().toDouble();
    int N = ui->lineEditMain1N->text().toInt();
    double eps = ui->lineEditMain1EPS->text().toDouble();
    bool ctl = ui->radioButtonMain1CLP->isChecked();

    MainWork1 M(b, u0, h0, N, ctl, eps);
    M.Run();
    QVector<double> x(M.grid.begin(), M.grid.end());
    QVector<double> y(M.final_num_values.begin(), M.final_num_values.end());
    const auto [y_min, y_max] = std::minmax_element(M.final_num_values.begin(), M.final_num_values.end());

    ui->graphMain1->addGraph();
    ui->graphMain1->graph(0)->setData(x, y);
    ui->graphMain1->xAxis->setRange(0, M.grid.back());
    ui->graphMain1->yAxis->setRange(*y_min, *y_max);
    ui->graphMain1->replot();


    ui->tableWidgetMain1->clearContents();
    ui->tableWidgetMain1->setRowCount(0);

    for (int i = 0; i < M.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(M.grid[i]));
        QTableWidgetItem *v = new QTableWidgetItem(QString::number(M.num_values[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(M.d_num_values[i]));
        QTableWidgetItem *diff = new QTableWidgetItem(QString::number(M.num_values[i] - M.d_num_values[i]));
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number((M.d_num_values[i] - M.num_values[i]) / 15 * 16));
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(M.grid_step[i]));
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(M.div2[i]));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(M.mult2[i]));
        ui->tableWidgetMain1->insertRow(i);
        ui->tableWidgetMain1->setItem(i, 0, x);
        ui->tableWidgetMain1->setItem(i, 1, v);
        ui->tableWidgetMain1->setItem(i, 2, v2);
        ui->tableWidgetMain1->setItem(i, 3, diff);
        ui->tableWidgetMain1->setItem(i, 4, OLP);
        ui->tableWidgetMain1->setItem(i, 5, h);
        ui->tableWidgetMain1->setItem(i, 6, c1);
        ui->tableWidgetMain1->setItem(i, 7, c2);
    }

}


void MainWindow::on_pushButtonMain2Run_clicked()
{
    double alpha = ui->lineEditMain2Alpha->text().toDouble();
    double beta = ui->lineEditMain2Beta->text().toDouble();
    double u1 = ui->lineEditMain2U1->text().toDouble();
    double u2 = ui->lineEditMain2U2->text().toDouble();
    double b = ui->lineEditMain2B->text().toDouble();
    double h0 = ui->lineEditMain2H0->text().toDouble();
    int N = ui->lineEditMain2N->text().toInt();
    double eps = ui->lineEditMain2LP->text().toDouble();
    bool ctl = ui->radioButtonMain2CLP->isChecked();

    MainWork2 M(alpha, beta, b, u1, u2, h0, N, ctl, eps);
    M.Run();
    QVector<double> x(M.grid.begin(), M.grid.end());
    QVector<double> y1(M.final_num_values_1.begin(), M.final_num_values_1.end());
    QVector<double> y2(M.final_num_values_2.begin(), M.final_num_values_2.end());
    const auto [y1_min, y1_max] = std::minmax_element(M.final_num_values_1.begin(), M.final_num_values_1.end());
    const auto [y2_min, y2_max] = std::minmax_element(M.final_num_values_2.begin(), M.final_num_values_2.end());

    ui->graphMain2Faz->addGraph();
    ui->graphMain2Faz->graph(0)->setData(y1, y2);
    ui->graphMain2Faz->xAxis->setRange(*y1_min, *y1_max);
    ui->graphMain2Faz->yAxis->setRange(*y2_min, *y2_max);
    ui->graphMain2Faz->replot();

    ui->graphMain2U1->addGraph();
    ui->graphMain2U1->graph(0)->setData(x, y1);
    ui->graphMain2U1->xAxis->setRange(0, M.grid.back());
    ui->graphMain2U1->yAxis->setRange(*y1_min, *y1_max);
    ui->graphMain2U1->replot();

    ui->graphMain2U2->addGraph();
    ui->graphMain2U2->graph(0)->setData(x, y2);
    ui->graphMain2U2->xAxis->setRange(0, M.grid.back());
    ui->graphMain2U2->yAxis->setRange(*y2_min, *y2_max);
    ui->graphMain2U2->replot();


    ui->tableWidgetMain2->clearContents();
    ui->tableWidgetMain2->setRowCount(0);

    for (int i = 0; i < M.grid.size(); i++)
    {
        QTableWidgetItem *x = new QTableWidgetItem(QString::number(M.grid[i]));
        QTableWidgetItem *v1 = new QTableWidgetItem(QString::number(M.num_values_1[i]));
        QTableWidgetItem *v1_2 = new QTableWidgetItem(QString::number(M.d_num_values_1[i]));
        QTableWidgetItem *diff1 = new QTableWidgetItem(QString::number(M.num_values_1[i] - M.d_num_values_1[i]));
        QTableWidgetItem *v2 = new QTableWidgetItem(QString::number(M.num_values_2[i]));
        QTableWidgetItem *v2_2 = new QTableWidgetItem(QString::number(M.d_num_values_2[i]));
        QTableWidgetItem *diff2 = new QTableWidgetItem(QString::number(M.num_values_2[i] - M.d_num_values_2[i]));
        double olp1 = (M.d_num_values_1[i] - M.num_values_1[i]) / 15 * 16;
        double olp2 = (M.d_num_values_2[i] - M.num_values_2[i]) / 15 * 16;
        QTableWidgetItem *OLP = new QTableWidgetItem(QString::number(std::max(olp1, olp2)));
        QTableWidgetItem *h = new QTableWidgetItem(QString::number(M.grid_step[i]));
        QTableWidgetItem *c1 = new QTableWidgetItem(QString::number(M.div2[i]));
        QTableWidgetItem *c2 = new QTableWidgetItem(QString::number(M.mult2[i]));
        ui->tableWidgetMain2->insertRow(i);
        ui->tableWidgetMain2->setItem(i, 0, x);
        ui->tableWidgetMain2->setItem(i, 1, v1);
        ui->tableWidgetMain2->setItem(i, 2, v1_2);
        ui->tableWidgetMain2->setItem(i, 3, diff1);
        ui->tableWidgetMain2->setItem(i, 4, v2);
        ui->tableWidgetMain2->setItem(i, 5, v2_2);
        ui->tableWidgetMain2->setItem(i, 6, diff2);
        ui->tableWidgetMain2->setItem(i, 7, OLP);
        ui->tableWidgetMain2->setItem(i, 8, h);
        ui->tableWidgetMain2->setItem(i, 9, c1);
        ui->tableWidgetMain2->setItem(i, 10, c2);
    }

}

