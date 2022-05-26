#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include "utils.h"

//angular step for search of dividing line
//should be at least 1/2 of minimal angle difference between points relative to pivot
#define CYCLE_STEP 1


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loaddata_clicked()
{
    datal.clear();
    //reading points from file
    //first n line with X and Y coordinate divided by space
    //last line is number of line with pivot, counting from 1
    scene->clear();
    QString file_name = QFileDialog::getOpenFileName(this,tr("Open text file with list of points"), "/home/jana", tr("Text Files (*.txt)"));
    QFile file(file_name);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    while (!file.atEnd()) {
        QString line = file.readLine();
        if (file.atEnd()) {
            //if its last line, read position of pivot and remove it from datal
            int pos = line.toInt();
            ct.setX(datal[pos - 1].x());
            ct.setY(datal[pos - 1].y());
            datal.remove(pos - 1);
            break;
        }
        QStringList list = line.split(QRegExp("\\s+"), QString::SkipEmptyParts);
        QPoint p(list[0].toFloat(), list[1].toFloat());
        datal.append(p);
    }

    //drawing points
    double rad = 0.5;

    //draws pivot in red color
    scene->addEllipse(ct.x()-rad, ct.y()-rad, rad*2.0, rad*2.0,
        QPen(QColor(255,0,0)), QBrush(Qt::SolidPattern));

    //draws all remaining points
    for (int i = 0; i<datal.size(); i++) {
        scene->addEllipse(datal[i].x()-rad, datal[i].y()-rad, rad*2.0, rad*2.0,
            QPen(), QBrush(Qt::SolidPattern));
    }
}

void MainWindow::on_pushButton_2_clicked()
{    
    //arbitrary point for line
    //change to relative to ct
    float maxl = 0;
    int maxp = 0;
    for (int j = 0; j < datal.size(); j++)
    {
       float lg = sqrt(pow(datal[j].x() - ct.x(), 2)
                        + pow(datal[j].y() - ct.y(), 2));
       if (lg > maxl)
       {
           maxl = lg;
       }
    }
    QPoint pt(ct.x() + 1.5 * maxl, ct.y() + 1.5 * maxl);

    int left = 0, right = 0;
    bool flag = false;

    //cycle goes from 0 to 180 degrees searching for line that
    //divides all points into either equal groups of n points
    //or groups of n and n-1 points
    //such line will indefinitely intersect with all given points

    //NOTE: much more effective algorithm would be getting projections of all points
    //relatively to our arbitrary generate line (ct -> pt)
    //counting their angle relative to that line (i.e. angle between ct -> pt and ct -> pt2
    //and working with resulting sorted 1D list of all points
    //didnt have time to write it properly
    for (int i = 0; i < 180; i += CYCLE_STEP)
    {
        for (int j = 0; j < datal.size(); j++)
        {
            int t = isLeft(pt,ct,datal[j]);
            if (t == 1){
                left++;
            }
            else if (t == -1){
                right++;
            }
            else {
                flag = !flag;
            }
        }

        //if found rotation is incorrect, rotates line and returns to start of cycle
        if (flag or (left - right < -1) or (left - right > 1)) {
            pt = rotateline(pt, ct, CYCLE_STEP);
            left = 0, right = 0;
            flag = false;
            if (i == 179) {
                ui->lineEdit->setText(QString("Solution not found"));
            }
            continue;
        }

        //if correct rotation is found, draws line based on resulting point
        //and its opposite point relative to pivot
        scene->addLine(pt.x(), pt.y(), ct.x()-pt.x(), ct.y()-pt.y(), QPen(Qt::green, 1));

        ui->lineEdit->setText(QString("Elements on the left: %1, on the right: %2").arg(left).arg(right));
        break;
    }
}








