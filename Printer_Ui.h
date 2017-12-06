#ifndef PRINTER_UI_H
#define PRINTER_UI_H

#include <QMainWindow>
#include <QPrinter>
#include <QPainter>
#include <QPrintPreviewDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QPrintDialog>
#include <QDebug>

namespace Ui {
class Printer_Ui;
}

class Printer_Ui : public QMainWindow
{
    Q_OBJECT

public:
    explicit Printer_Ui(QWidget *parent = 0);
    ~Printer_Ui();

private slots:
    void on_bt_save_img_clicked();
    void on_bt_preview_clicked();
    void on_bt_prints_clicked();

    void printPreviewSlot(QPrinter*);



private:
    Ui::Printer_Ui *ui;
};

#endif // PRINTER_UI_H
