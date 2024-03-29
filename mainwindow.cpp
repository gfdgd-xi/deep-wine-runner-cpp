#include "mainwindow.h"
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QMainWindow>
#include <QObject>
#include <QSizePolicy>
#include <QSpacerItem>
#include <QTextBrowser>
#include <QCoreApplication>
#include <iostream>
#include <QDebug>
#include <QIODevice>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QProcess>
#include <QMessageBox>
#include <QObject>
using namespace std;
QComboBox *MainWindow::e1;
QComboBox *MainWindow::e2;
QComboBox *MainWindow::o1;
QMap<QString, QString> MainWindow::setting;
QMap<QString, QString> MainWindow::wine;
QString MainWindow::lastRunCommand = "";
MainWindow::MainWindow(){
    /*********
     * 设置变量
     *********/

    // 如果要添加其他 wine，请使用安装更多 Wine 功能


    QMainWindow *window = new QMainWindow();
    QWidget *widget = new QWidget();
    window->setCentralWidget(widget);
    QGridLayout *mainLayout = new QGridLayout();
    QSizePolicy size;
    //size->setVerticalPolicy(0);
    QWidget *leftUp = new QWidget();
    mainLayout->addWidget(leftUp, 0, 0, 1, 1);
    QGridLayout *leftUpLayout = new QGridLayout();
    leftUp->setLayout(leftUpLayout);
    QLabel *fastLabel = new QLabel(QObject::tr("快速启动"));
    fastLabel->setStyleSheet("font: 30px;");
    leftUpLayout->addWidget(fastLabel, 0, 0, 1, 2);
    leftUpLayout->addWidget(new QLabel("<hr>"), 1, 0, 1, 2);
    leftUpLayout->addWidget(new QLabel(QObject::tr("请选择容器路径：")), 2, 0, 1, 1);
    e1 = new QComboBox();
    e1->setEditable(1);
    leftUpLayout->addWidget(e1, 3, 0, 1, 1);
    button1 = new QPushButton("浏览");
    //button1.clicked.connect(liulanbutton);
    leftUpLayout->addWidget(button1, 3, 1, 1, 1);
    leftUpLayout->addWidget(new QLabel(QObject::tr("请选择要执行的程序（EXE、MSI或者命令）：")), 4, 0, 1, 1);
    e2 = new QComboBox();
    e2->setEditable(1);
    leftUpLayout->addWidget(e2, 5, 0, 1, 1);
    button2 = new QPushButton(QObject::tr("浏览"));
    //button2.clicked.connect(liulanexebutton);
    leftUpLayout->addWidget(button2, 5, 1, 1, 1);
    leftUpLayout->addWidget(new QLabel(QObject::tr("请选择WINE版本：")), 6, 0, 1, 1);
    o1 = new QComboBox();
    leftUpLayout->addWidget(o1, 7, 0, 1, 1);
    // 设置空间权重
    button1->setSizePolicy(size);
    button2->setSizePolicy(size);

    // UI 创建
    QWidget *leftDown = new QWidget();
    mainLayout->addWidget(leftDown, 1, 0, 1, 1);
    QVBoxLayout *leftDownLayout = new QVBoxLayout();
    leftDown->setLayout(leftDownLayout);
    QLabel *highLabel = new QLabel(QObject::tr("高级功能"));
    highLabel->setStyleSheet("font: 30px;");
    leftDownLayout->addWidget(highLabel);
    leftDownLayout->addWidget(new QLabel("<hr>"));
    leftDownLayout->addWidget(new QLabel(QObject::tr("创建快捷方式（Desktop文件）：")));
    QHBoxLayout *createDesktopLink = new QHBoxLayout();
    QLabel *label_r_2 = new QLabel(QObject::tr("名称："));
    createDesktopLink->addWidget(label_r_2);
    QComboBox *combobox1 = new QComboBox();
    combobox1->setEditable(1);
    createDesktopLink->addWidget(combobox1);
    QPushButton *button5 = new QPushButton(QObject::tr("创建到桌面"));
    //button5.clicked.connect(make_desktop_on_desktop);
    createDesktopLink->addWidget(button5);
    QPushButton *saveDesktopFileOnLauncher =  new QPushButton(QObject::tr("创建到开始菜单"));
    //saveDesktopFileOnLauncher.clicked.connect(make_desktop_on_launcher);
    createDesktopLink->addWidget(saveDesktopFileOnLauncher);
    leftDownLayout->addLayout(createDesktopLink);
    QGridLayout *programManager = new QGridLayout();
    leftDownLayout->addLayout(programManager);
    programManager->addWidget(new QLabel(QObject::tr("程序管理：")), 0, 0, 1, 1);
    getProgramIcon = new QPushButton(QObject::tr("提取图标"));
    //getProgramIcon.clicked.connect(lambda: RunWineProgram(f"{programPath}/BeCyIconGrabber.exe' '{e2.currentText()}" if e2.currentText()[:2].upper() == "C:" else f"{programPath}/BeCyIconGrabber.exe' 'z:/{e2.currentText()}"));
    programManager->addWidget(getProgramIcon, 1, 0, 1, 1);
    programManager->addWidget(new QLabel("     "), 1, 1, 1, 1);
    trasButton = new QPushButton(QObject::tr("窗口透明工具"));
    //trasButton.clicked.connect(lambda: RunWineProgram(f"{programPath}/窗体透明度设置工具.exe"));
    programManager->addWidget(trasButton, 1, 2, 1, 1);
    uninstallProgram = new QPushButton(QObject::tr("卸载程序"));
    //uninstallProgram.clicked.connect(lambda: RunWineProgram(f"{programPath}/geek.exe"));
    programManager->addWidget(new QLabel("     "), 1, 3, 1, 1);
    programManager->addWidget(uninstallProgram, 1, 4, 1, 1);
    miniAppStore = new QPushButton(QObject::tr("微型应用商店"));
    //miniAppStore.clicked.connect(lambda: threading.Thread(target=MiniAppStore).start());
    programManager->addWidget(new QLabel("     "), 1, 5, 1, 1);
    programManager->addWidget(miniAppStore, 1, 6, 1, 1);
    programManager->addWidget(new QLabel("     "), 1, 7, 1, 1);
    QPushButton *getProgramStatus = new QPushButton(QObject::tr("获取该程序运行情况"));
    //getProgramStatus.clicked.connect(ProgramRunStatusShow.ShowWindow);
    programManager->addWidget(getProgramStatus, 1, 8, 1, 1);
    QPushButton *getLoseDll = new QPushButton(QObject::tr("检测静态下程序缺少DLL"));
    //getLoseDll.clicked.connect(GetLoseDll);
    programManager->addWidget(new QLabel("     "), 1, 9, 1, 1);
    programManager->addWidget(getLoseDll, 1, 10, 1, 1);
    programManager->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum), 1, 11, 1, 1);
    programManager->addWidget(new QLabel(QObject::tr("WINE配置：")), 2, 0, 1, 1);
    wineConfig = new QPushButton(QObject::tr("配置容器"));
    //wineConfig.clicked.connect(lambda: RunWineProgram("winecfg"));
    programManager->addWidget(wineConfig, 3, 0, 1, 1);
    QPushButton *fontAppStore = new QPushButton(QObject::tr("字体商店"));
    //fontAppStore.clicked.connect(FontAppStore);
    programManager->addWidget(fontAppStore, 3, 2, 1, 1);
    button_r_6 = new QPushButton(QObject::tr("RegShot"));
    //button_r_6.clicked.connect(lambda: RunWineProgram(f"{programPath}/RegShot/regshot.exe"));
    programManager->addWidget(button_r_6, 3, 4, 1, 1);
    QPushButton *sparkWineSetting = new QPushButton(QObject::tr("星火wine配置"));
    //sparkWineSetting.clicked.connect(lambda: threading.Thread(target=os.system, args=["bash /opt/durapps/spark-dwine-helper/spark-dwine-helper-settings/settings.sh"]).start());
    programManager->addWidget(sparkWineSetting, 3, 6, 1, 1);
    QPushButton *wineAutoConfig =  new QPushButton(QObject::tr("自动/手动配置 Wine 容器"));
    //wineAutoConfig.clicked.connect(WineBottonAutoConfig);
    programManager->addWidget(wineAutoConfig, 3, 8, 1, 1);
    QPushButton *wineBottleReboot = new QPushButton(QObject::tr("重启指定Wine容器"));
    //wineBottleReboot.clicked.connect(lambda: RunWineProgram(f"wineboot' '-k"));
    programManager->addWidget(wineBottleReboot, 3, 10, 1, 1);

    // 权重
    button5->setSizePolicy(size);
    saveDesktopFileOnLauncher->setSizePolicy(size);
    label_r_2->setSizePolicy(size);
    getProgramIcon->setSizePolicy(size);
    //trasButton.setSizePolicy(size);
    button_r_6->setSizePolicy(size);
    wineConfig->setSizePolicy(size);

    QTextBrowser *returnText = new QTextBrowser();
    returnText->setStyleSheet("background-color: black;"\
    "color: white;");
    returnText->setText(QObject::tr("在此可以看到wine安装应用时的终端输出内容\n"\
    "=============================================\n"\
    "如果解决了你的问题，请不要吝啬你的star哟！\n"\
    "地址：\n"\
    "https://gitee.com/gfdgd-xi/deep-wine-runner\n"\
    "https://github.com/gfdgd-xi/deep-wine-runner\n"\
    "https://sourceforge.net/projects/deep-wine-runner"));
    mainLayout->setRowStretch(0, 2);
    mainLayout->setRowStretch(1, 1);
    mainLayout->setColumnStretch(0, 2);
    mainLayout->setColumnStretch(1, 1);
    mainLayout->addWidget(returnText, 0, 1, 2, 1);

    // 版权
    QLabel *copy = new QLabel("程序版本：{version}，<b>提示：Wine 无法保证可以运行所有的 Windows 程序，如果想要运行更多 Windows 程序，可以考虑虚拟机和双系统</b><br/>"\
    "<b>注：部分二进制兼容层会自动注册 binfmt（如原版的 Box86/64、Qemu User Static），则意味着无需在 Wine 版本那里特别指定兼容层，直接指定 Wine 即可</b><br/>"\
    "©2020~" + QDateTime(QDateTime::currentDateTime()).toString("yyyy") + " gfdgd xi");
    mainLayout->addWidget(copy, 2, 0, 1, 1);

    // 程序运行
    QWidget *programRun = new QWidget();
    QHBoxLayout *programRunLayout = new QHBoxLayout();
    programRun->setLayout(programRunLayout);
    programRunLayout->addItem(new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    QPushButton *button3 = new QPushButton(QObject::tr("运行程序"));
    //button3.clicked.connect(runexebutton);
    programRunLayout->addWidget(button3);
    QPushButton *killProgram = new QPushButton(QObject::tr("终止程序"));
    //killProgram.clicked.connect(KillProgram);
    programRunLayout->addWidget(killProgram);
    QPushButton *killBottonProgram = new QPushButton(QObject::tr("终止指定容器的程序"));
    //killBottonProgram.clicked.connect(lambda: threading.Thread(target=os.system, args=[f"'{programPath}/kill.sh' '{os.path.basename(e1.currentText())}'"]).start());
    programRunLayout->addWidget(killBottonProgram);
    mainLayout->addWidget(programRun, 2, 1, 1, 1);

    // 窗口设置
    window->resize(widget->frameGeometry().width() * 2, widget->frameGeometry().height());
    window->setWindowIcon(QIcon(":/Icon/deepin-wine-runner.svg"));
    widget->setLayout(mainLayout);
    window->show();

    CheckWine();

    // 控件设置
    e1->addItems(findExeHistory);
    e2->addItems(wineBottonHistory);
    combobox1->addItems(shellHistory);
    o1->addItems(canUseWine);


    // 一个 Wine 都没有却用 Wine 的功能
    // 还是要处理的，至少不会闪退
    if(o1->currentText() == ""){
        o1->addItem("没有识别到任何Wine，请在菜单栏“程序”安装Wine或安装任意Wine应用");
    }
    QObject::connect(button3, &QPushButton::clicked, [&](){
        Runexebutton_threading *thread = new Runexebutton_threading();
        //QObject::connect(thread, &Runexebutton_threading::signal, this, [this](){});
        thread->start();
    });

}

void MainWindow::Runexebutton_threading::run(){
    QString programPath = QCoreApplication::applicationDirPath();
    QString wineBottlePath = "";
    if(e1->currentText() == ""){
        wineBottlePath = setting.value("DefultBotton");
    }
    else{
        wineBottlePath = e1->currentText();
    }
    QString option = "";
    if(setting.value("Architecture") != "Auto"){
        option += "WINEARCH=" + setting.value("Architecture") + " ";
    }
    if(setting.value("MonoGeckoInstaller") == "1"){
        option += "WINEDLLOVERRIDES=\"mscoree,mshtml=\" ";
    }
    if(setting.value("") != "1"){
        option += "WINEDEBUG=-all ";
    }
    else{
        option += "WINEDEBUG=FIXME,ERR,WARN,TRACE,Message ";
    }
    QString wineUsingOption = "";
    QString exePath = e2->currentText();
    QStringList fileName = {".exe"};
    bool changePath = false;
    for(QString i: fileName){
        if(exePath.contains(i)){
            qDebug() << i;
            qDebug() << exePath;
            int l = exePath.indexOf(i);
            exePath = exePath.mid(0, l + 4) + "' " + exePath.mid(l + 4) + " '";
            qDebug() << l;
            qDebug() << exePath;
            changePath = true;
            break;
        }
    }
    if(!changePath && QFile::exists(exePath)){
        // 删除前后无用空格以防止出现问题
        qDebug() << exePath;
        exePath = exePath.trimmed();
        // 有空格再说
        if(exePath.contains(" ")){
            int l = exePath.indexOf(" ");
            exePath = exePath.mid(0, l) + "' " + exePath.mid(l) + " '";
            qDebug() << l;
        }
        qDebug() << exePath;
    }
    if(o1->currentText() == "基于 UOS exagear 的 deepin-wine6-stable" ||
            o1->currentText() == "基于 UOS box86 的 deepin-wine6-stable"){
        wineUsingOption = "";
    }
    if(o1->currentText() == "基于 UOS box86 的 deepin-wine6-stable" ||
            o1->currentText() == "基于 UOS exagear 的 deepin-wine6-stable"){
        if(!QDir(programPath + "/dlls-arm").exists()){
            if(system(("7z x -y \"" + programPath + "/dlls-arm.7z\" -o\"" + programPath + "\"").toUtf8())){
                QMessageBox::critical(NULL, "错误", "无法解压资源");
                return;
            }
            QFile::remove(programPath + "/dlls-arm.7z");
        }
    }
    //QString runCommand = "";
    QString runCommand = "";
    QProcess *process = new QProcess();
    //if(setting.value("TerminalOpen") == "True"){
    if(0){
        if(e2->currentText().mid(-4) == ".msi" && QFile::exists(e2->currentText())){
            runCommand = "env WINEPREFIX='" + wineBottlePath + "' " + option + wine[o1->currentText()] + " msiexec /i '" + e2->currentText() + "' " + setting.value("WineOption");
            // OpenTerminal(runCommand)
        }
        // ……
    }
    else{
        if(e2->currentText().mid(-4) == ".msi" && QFile::exists(e2->currentText())){
            runCommand = "env WINEPREFIX='" + wineBottlePath + "' " + option + wine[o1->currentText()] + " msiexec /i '" + e2->currentText() + "' " + setting.value("WineOption");
        }
        else if(e2->currentText().mid(-4) == ".bat" && QFile::exists(e2->currentText())){
            runCommand = "WINEPREFIX='" + wineBottlePath + "' " + option + wine[o1->currentText()] + " wineconsole '" + e2->currentText() + "' " + setting["WineOption"];
        }
        else{
            runCommand = "WINEPREFIX='" + wineBottlePath + "' " + option + wine[o1->currentText()] + " '" + exePath + "' " + setting["WineOption"];
        }

    }
    // 实时读取程序返回
    qDebug() << runCommand;
    lastRunCommand = runCommand;
    // 连接槽
    connect(process, &QProcess::readyReadStandardOutput, this, [this, process](){
        //emit this->signal(QString::fromUtf8(process.readAll()));
    });
    //if(setting.value("TerminalOpen") != "True"){
    if(1){
        process->setReadChannel(QProcess::StandardOutput);
        process->start(runCommand);
        process->waitForStarted();
        process->waitForFinished();
        process->close();
    }
    // ……
}

void MainWindow::DisableButton(bool things){
    button_r_6->setDisabled(things);
    button1->setDisabled(things);
    button2->setDisabled(things);
    button3->setDisabled(things);
    wineConfig->setDisabled(things);
    e1->setDisabled(things);
    e2->setDisabled(things);
    o1->setDisabled(things);
    miniAppStore->setDisabled(things);
    //winetricksOpen->configure(state=a[things])
    getProgramIcon->setDisabled(things);
    uninstallProgram->setDisabled(things);
    trasButton->setDisabled(things);
}

void MainWindow::runexebutton(){
    DisableButton(1);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

QString MainWindow::get_home(){
    return QDir::homePath();
}

QString MainWindow::readtxt(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString things = file.readAll();
    file.close();
    return things;
}

QByteArray MainWindow::readtxtByte(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QByteArray things = file.readAll();
    file.close();
    return things;
}

void MainWindow::write_txt(QString path, QByteArray things){
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    file.write(things);
    file.close();
}

QString MainWindow::GetCommandResult(QString command){
    QProcess process;
    process.start(command);
    process.waitForStarted();
    process.waitForFinished();
    QString result = process.readAll();
    process.close();
    return result;
}

/*
 * 检测 Wine
 */
void MainWindow::CheckWine(){
    QStringList wine7zUse = {"wine", "wine64", "wine-i386", "wine-aarch64", "wine-x86_64"};
    wine.clear();
    wine.insert("基于 UOS box86 的 deepin-wine6-stable",
                "WINEPREDLL='" + programPath + "/dlls-arm' "\
                "WINEDLLPATH=/opt/deepin-wine6-stable/lib BOX86_NOSIGSEGV=1 "\
                "/opt/deepin-box86/box86 /opt/deepin-wine6-stable/bin/wine ");
    wine.insert("基于 UOS exagear 的 deepin-wine6-stable",
                "WINEPREDLL='" + programPath + "/dlls-arm' WINEDLLPATH=/opt/deepin-wine6-stable/lib"\
                " /opt/exagear/bin/ubt_x64a64_al --path-prefix " + get_home() + "/.deepinwine/debian-buster --utmp-paths-list " + get_home() + ""\
                "/.deepinwine/debian-buster/.exagear/utmp-list --vpaths-list " + get_home() + "/.deepinwine/debian-buster/.exagear/vpaths-list"\
                " --opaths-list " + get_home() + "/.deepinwine/debian-buster/.exagear/opaths-list --smo-mode fbase --smo-severity smart "\
                "--fd-limit 8192 --foreign-ubt-binary /opt/exagear/bin/ubt_x32a64_al -- /opt/deepin-wine6-stable/bin/wine ");
    wine.insert("使用 Flatpak 安装的 Wine", "flatpak run org.winehq.Wine");
    wine.insert("deepin-wine8-stable", "deepin-wine8-stable");
    wine.insert("deepin-wine6 stable", "deepin-wine6-stable");
    wine.insert("deepin-wine6-vannila", "deepin-wine6-vannila");
    wine.insert("deepin-wine5 stable", "deepin-wine5-stable");
    wine.insert("spark-wine", "spark-wine");
    wine.insert("spark-wine7-devel", "spark-wine7-devel");
    wine.insert("spark-wine8", "spark-wine8");
    wine.insert("spark-wine8-wow", "spark-wine8-wow");
    wine.insert("deepin-wine", "deepin-wine");
    wine.insert("deepin-wine5", "deepin-wine5");
    wine.insert("wine", "wine");
    wine.insert("wine64", "wine64");
    wine.insert("ukylin-wine", "ukylin-wine");
    wine.insert("okylin-wine", "okylin-wine");
    wine.insert("mono（这不是 wine，但可以实现初步调用运行 .net 应用）", "mono");
    wine.insert("基于 linglong 的 deepin-wine6-stable（不推荐）", "ll-cli run '' --exec '/bin/deepin-wine6-stable'");
    if(QFile::exists("/opt/deepin-box86/box86") && QFile::exists("/opt/deepin-wine6-stable/bin/wine")){
        canUseWine.append("基于 UOS box86 的 deepin-wine6-stable");
    }
    if(QFile::exists("/opt/exagear/bin/ubt_x64a64_al") && QFile::exists("/opt/deepin-wine6-stable/bin/wine")){
        canUseWine.append("基于 UOS exagear 的 deepin-wine6-stable");
    }
    for(QString i : wine.keys()){
        if(!system(("which '" + wine.key(i) + "'").toUtf8())){
            canUseWine.append(i);
        }
    }
    if(!system("which flatpak") && QDir("/var/lib/flatpak/app/org.winehq.Wine").exists()){
        canUseWine.append("使用 Flatpak 安装的 Wine");
    }
    if(QDir("/persistent/linglong/layers/").exists()){  // 判断是否使用 linglong
        for(QString i : QDir("/persistent/linglong/layers/").entryList()){
            try{
                break;  // bug
                QString dire = QDir("/persistent/linglong/layers/" + i).entryList()[-1];
                QString arch = QDir("/persistent/linglong/layers/" + i + "/" + dire)[-1];
                if(QFile::exists("/persistent/linglong/layers/" + i + "/" + dire + "/" + arch + "/runtime/bin/deepin-wine6-stable")){
                    wine.insert("基于 linglong 的 deepin-wine6-stable（不推荐）", "ll-cli run " + i + " --exec '/bin/deepin-wine6-stable'");
                    canUseWine.append("基于 linglong 的 deepin-wine6-stable（不推荐）");
                    break;
                }
            }
            catch(QString msg){
                qDebug() << msg;
            }
        }
    }
    // 读取自定义安装的 Wine（需要解包的才能使用）
    if(!system("which qemu-i386-static")){
        if(QDir(qemuPath).exists()){
            for(QString g: QDir(qemuPath).entryList()){
                QString archPath = qemuPath + "/" + g;
                QString arch = g;
                if(QFileInfo(archPath).isDir()){
                    for(QString d: QDir(archPath).entryList()){
                        QString bottlePath = archPath + "/" + g;
                        if(QFileInfo(bottlePath).isDir()){
                            qemuBottleList.append(QStringList() << arch << d << bottlePath);
                        }
                    }
                }
            }
        }
    }
    QJsonParseError jsonError;
    QJsonDocument jsonDocument;
    QJsonObject jsonObject;
    QStringList historyList[] = {shellHistory, findExeHistory, wineBottonHistory, isoPath, isoPathFound};
    QStringList historyListPath = {homePath + "/.config/deepin-wine-runner/ShellHistory.json",
                                  homePath + "/.config/deepin-wine-runner/FindExeHistory.json",
                                  homePath + "/.config/deepin-wine-runner/WineBottonHistory.json",
                                  homePath + "/.config/deepin-wine-runner/ISOPath.json",
                                  homePath + "/.config/deepin-wine-runner/ISOPathFound.json"};
    for(int i = 0; i <= historyList->size(); i++){
        QStringList *list = &historyList[i];
        jsonDocument = QJsonDocument(QJsonDocument::fromJson(readtxtByte(historyListPath[i])));
        jsonObject = jsonDocument.object();
        list->clear();
        for(QString i: jsonObject.keys()){
            list->append(jsonObject.value(i).toString());
        }
    }
    qDebug() << jsonError.errorString();
    jsonDocument = QJsonDocument(QJsonDocument::fromJson(readtxtByte(homePath + "/.config/deepin-wine-runner/WineSetting.json")));
    jsonObject = jsonDocument.object();
    setting.clear();
    for(QString i: jsonObject.keys()){
        setting.insert(i, jsonObject.value(i).toString());
    }
    for(QString i: QDir(programPath + "/wine/").entryList()){
        if(QDir(programPath + "/wine/" + i).exists() && QFileInfo(programPath + "/wine/" + i).isDir()){
            QStringList nameValue = {{"", ""}};
            try{
                if(QFile::exists("/opt/deepin-box86/box86")){
                    nameValue.append(QStringList() << "基于 UOS box86 的 " <<
                                     "WINEPREDLL='" + programPath + "/dlls-arm' WINEDLLPATH=/opt/deepin-wine6-stable/lib BOX86_NOSIGSEGV=1"\
                                      " /opt/deepin-box86/box86  ");
                }
                if(!system("which box86")){
                    nameValue.append(QStringList() << "基于 box86 的 " << "box86 ");
                }
                if(!system("which box64")){
                    nameValue.append(QStringList() << "基于 box64 的 " << "box64 ");
                }
                if(!system("which qemu-i386") &&
                        GetCommandResult("arch").replace(" ", "").replace("\n", "") != "x86_64" &&
                        GetCommandResult("arch").replace(" ", "").replace("\n", "") != "i686"){
                    nameValue.append(QStringList() << "基于 qemu-i386 的 " << "qemu-i386 ");
                }
                if(!system("which qemu-x86_64") &&
                        GetCommandResult("arch").replace(" ", "").replace("\n", "") != "x86_64" &&
                        GetCommandResult("arch").replace(" ", "").replace("\n", "") != "i686"){
                    nameValue.append(QStringList() << "基于 qemu-x86_64 的 " << "qemu-x86_64 ");
                }
                if(QFile::exists("/opt/exagear/bin/ubt_x64a64_al") && QFile::exists(homePath + "/.deepinwine/debian-buster")){
                    nameValue.append(QStringList() << "基于 UOS exagear 的 " << "WINEPREDLL='" + programPath + "/dlls-arm' "\
                                    "WINEDLLPATH=/opt/deepin-wine6-stable/lib /opt/exagear/bin/ubt_x64a64_al --path-prefix " + get_home() + "/.deepinwine/debian-buster "\
                                    "--utmp-paths-list " + homePath + "/.deepinwine/debian-buster/.exagear/utmp-list --vpaths-list " + homePath + "/.deepinwine/debian-buster/.exagear/vpaths-list "\
                                    "--opaths-list " + homePath + "/.deepinwine/debian-buster/.exagear/opaths-list --smo-mode fbase --smo-severity smart --fd-limit 8192 --foreign-ubt-binary /opt/exagear/bin/ubt_x32a64_al --  ");
                }
                if(!system("which exagear")){
                    nameValue.append(QStringList() << "运行 exagear 容器内的 " << "exagear -- ");
                }
                if(QFile::exists("/opt/exagear/bin/ubt_x64a64_al")){
                    nameValue.append(QStringList() << "使用 ubt_x64a64_al 运行" << "/opt/exagear/bin/ubt_x64a64_al -- ");
                }
                if(QFile::exists("/opt/exagear/bin/ubt_x32a64_al")){
                    nameValue.append(QStringList() << "使用 ubt_x32a64_al 运行" << "/opt/exagear/bin/ubt_x32a64_al -- ");
                }
                /*for(QString g: qemuBottleList){
                    nameValue.append(QStringList() << "使用qemu-" + g[0] + "-static 调用容器" + g[1] + "运行 " << "python3 '" + programPath + "/QemuRun.py' '" + g[0] + "/" + g[1] + "' " + setting.value("QemuUnMountHome").toInt());
                }*/
            }
            catch(QString msg){
                qDebug() << msg;
            }
            /*for(QString k: nameValue){
                qDebug() << k;
                if(k.contains("qemu")){

                }
            }*/
            try{
                for(QString i: QDir(homePath + "/.deepinwine/").entryList()){
                    for(QString j: wine7zUse){
                        if(QFile::exists(homePath + "/.deepinwine/" + i + "/bin/" + j)){
                            wine.insert(homePath + "/.deepinwine/" + i + "/bin/" + j, homePath + "/.deepinwine/" + i + "/bin/" + j);
                            canUseWine.append(homePath + "/.deepinwine/" + i + "/bin/" + j);
                        }

                    }
                }
            }
            catch(QString msg){
                qDebug() << msg;
            }
            try{
                QStringList canUseWineOld = canUseWine;
                for(QString i: canUseWineOld){
                    if(QDir(programPath + "/WineLib/usr").exists()){
                        wine.insert("使用运行器的运行库运行 " + i, "bash '" + programPath + "/WineLib/run.sh' " + wine.value(i));
                        canUseWine.append("使用运行器的运行库运行 " + i);
                        untipsWine.append("使用运行器的运行库运行 " + i);
                    }
                }
                if(QDir("/opt/exagear/images").exists()){
                    for(QString k: QDir("/opt/exagear/images").entryList()){
                        if(QFileInfo("/opt/exagear/images/" + k).isDir()){
                            continue;
                        }
                        for(QString i: canUseWineOld){
                            wine.insert("使用Exagear容器运行库运行 " + i, "bash '" + programPath + "/WineLib/run-more.sh' '/opt/exagear/images/" + k + "' " + wine.value(i));
                            canUseWine.append("使用Exagear容器运行库运行 " + i);
                            untipsWine.append("使用Exagear容器运行库运行 " + i);
                        }
                    }
                }
            }
            catch(QString msg){
                qDebug() << msg;
            }
        }
    }
}
