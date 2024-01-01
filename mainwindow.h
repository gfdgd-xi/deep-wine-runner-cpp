#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMap>
#include <QDir>
#include <QCoreApplication>
#include <QPushButton>
#include <QComboBox>

class MainWindow
{

public:
    MainWindow();
    ~MainWindow();
    void CheckWine();
    QString get_home();
    QString readtxt(QString path);
    void write_txt(QString path, QByteArray things);
    QByteArray readtxtByte(QString path);
    QString GetCommandResult(QString command);

private:
    void runexebutton();
    void DisableButton(bool things);
    QString homePath = QDir::homePath();
    QString programPath = QCoreApplication::applicationDirPath();
    QMap<QString, QString> wine;
    QStringList untipsWine = {"使用 Flatpak 安装的 Wine", "基于 exagear 的 deepin-wine6-stable", "基于 UOS box86 的 deepin-wine6-stable", "基于 UOS exagear 的 deepin-wine6-stable", "基于 linglong 的 deepin-wine6-stable（不推荐）"};
    QStringList canUseWine = {};
    QStringList qemuBottleList = {};
    QString qemuPath = homePath + "/.deepin-wine-runner-ubuntu-images";
    QStringList shellHistory;
    QStringList findExeHistory;
    QStringList wineBottonHistory;
    QStringList isoPath;
    QStringList isoPathFound;
    QMap<QString, QString> setting;
    // 控件
    QPushButton *button_r_6;
    QPushButton *button1;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *wineConfig;
    QPushButton *miniAppStore;
    QPushButton *getProgramIcon;
    QPushButton *uninstallProgram;
    QPushButton *trasButton;
    QComboBox *e1;
    QComboBox *e2;
    QComboBox *o1;


};
#endif // MAINWINDOW_H
