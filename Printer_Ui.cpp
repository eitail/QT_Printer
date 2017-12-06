#include "Printer_Ui.h"
#include "ui_Printer_Ui.h"

Printer_Ui::Printer_Ui(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Printer_Ui)
{
    ui->setupUi(this);
    ui->lab_img->setGeometry(400,50,200,300);
    ui->lab_img->setStyleSheet("background-image:url(:/img/img/dog.png)");
}

Printer_Ui::~Printer_Ui()
{
    delete ui;
}

void Printer_Ui::on_bt_save_img_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存PDF文件"), QString(), "*.pdf");
    if (!fileName.isEmpty())
    {
        // 如果文件后缀为空，则默认使用.pdf
        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }
        QPrinter printerPixmap(QPrinter::HighResolution);
        //自定义纸张大小，这里要打印的内容都在stackedWidget上
        printerPixmap.setPageSize(QPrinter::Custom);
        printerPixmap.setPaperSize(QSizeF(ui->lab_img->height(), ui->lab_img->width()), QPrinter::Point);
        //设置纸张大小为A4，这里注释掉了，建议自定义纸张 ，否则保存的就会有很多空白
        //printerPixmap.setPageSize(QPrinter::A4);
        //横向打印
        printerPixmap.setOrientation(QPrinter::Landscape);
        //设置输出格式为pdf
        printerPixmap.setOutputFormat(QPrinter::PdfFormat);
        //设置输出路径
        printerPixmap.setOutputFileName(fileName);
        //获取界面的图片
        QPixmap pixmap = QPixmap::grabWidget(ui->lab_img, ui->lab_img->rect());

        QPainter painterPixmap;
        painterPixmap.begin(&printerPixmap);
        QRect rect = painterPixmap.viewport();
        int x = rect.width() / pixmap.width();
        int y = rect.height() / pixmap.height();
        //将图像(所有要画的东西)在pdf上按比例尺缩放,如果想展示原始图，就讲x和y设置为1就可以了
        painterPixmap.scale(x, y);
        //画图
        painterPixmap.drawPixmap(0, 0, pixmap);
        painterPixmap.end();

        QMessageBox::information(this, tr("生成PDF"), tr("保存PDF文件成功"), QMessageBox::Ok);
    }
}

void Printer_Ui::on_bt_preview_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    //自定义纸张大小
    printer.setPageSize(QPrinter::Custom);
    printer.setPaperSize(QSizeF(ui->lab_img->height(), ui->lab_img->width()),
                               QPrinter::Point);
    QPrintPreviewDialog preview(&printer, this);
    preview.setMinimumSize(1000,600);
    connect(&preview, SIGNAL(paintRequested(QPrinter*)), SLOT(printPreviewSlot(QPrinter*)));
    preview.exec ();
}

void Printer_Ui::on_bt_prints_clicked()
{
    QPrinter printerPixmap;
    QPixmap pixmap = QPixmap::grabWidget(ui->lab_img, ui->lab_img->rect());  //获取界面的图片
    printerPixmap.setOrientation(QPrinter::Landscape);//纵向：Portrait 横向：Landscape
    printerPixmap.setPageSize(QPrinter::A4);//设置纸张大小
    QPainter painterPixmap;
    painterPixmap.begin(&printerPixmap);
    painterPixmap.scale(1, 1);//设置图像长宽是原图的多少倍
    painterPixmap.drawPixmap(300, 300 , pixmap);//设置图像在A4中的开始坐标是什么
    painterPixmap.end();
}

void Printer_Ui::printPreviewSlot(QPrinter* printerPixmap)
{
    printerPixmap->setOrientation(QPrinter::Landscape);
    //获取界面的图片
    QPixmap pixmap = QPixmap::grabWidget(ui->lab_img, ui->lab_img->rect());
    QPainter painterPixmap(this);
    painterPixmap.begin(printerPixmap);
    QRect rect = painterPixmap.viewport();
    int x = rect.width() / pixmap.width();
    int y = rect.height() / pixmap.height();
    painterPixmap.scale(x, y);
    painterPixmap.drawPixmap(0, 0, pixmap);
    painterPixmap.end();
}

