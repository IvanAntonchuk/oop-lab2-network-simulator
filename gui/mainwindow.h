#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <map>
#include "NetworkBuilder.h"
#include "NetworkNode.h"
#include "VisualNode.h"
#include "VisualEdge.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnAddServer_clicked();
    void on_btnSaveNetwork_clicked();
    void on_btnLoadNetwork_clicked();
    void on_btnPingNetwork_clicked();

    void handleNodeConnection(VisualNode* source, VisualNode* target);
    void handleEdgeDeletion(VisualEdge* edge);

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    int serverCounter;

    NetworkBuilder builder;
    std::shared_ptr<Subnet> activeNetwork;
    std::map<VisualNode*, std::shared_ptr<NetworkNode>> nodeMapping;
};

#endif
