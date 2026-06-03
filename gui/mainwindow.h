#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnTestComposite_clicked();
    void on_btnTestStrategy_clicked();
    void on_btnStartSimulation_clicked();
    void on_btnPauseSimulation_clicked();
    void on_btnTestState_clicked();
    void on_btnTestBuilder_clicked();
    void on_btnTestPrototype_clicked();
    void on_btnTestDecorator_clicked();
    void on_btnTestFacade_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
