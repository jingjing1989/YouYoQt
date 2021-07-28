#include "MainWindowHome.h"
#include "ui_MainWindowHome.h"
#include "utility/CommonUtility.h"

#include <QFile>
#include <QMouseEvent>
#include <QPoint>
#include <QPropertyAnimation>
#include <QtDebug>
#include <iostream>

#ifdef Q_OS_WIN
#include "windows.h"
#endif

MainWindowHome::MainWindowHome(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindowHome) {
  ui->setupUi(this);
  //不显示标题栏
  setWindowFlags(Qt::FramelessWindowHint);

  //设置样式
  QString styleSheetlefttop(":/qss/res/qss/defaultstyle/mainHome.css");
  CommonUtility::setStyleSheet(styleSheetlefttop, this);

  this->installEventFilter(this);

  //初始化左边栏
  initLeftBar();
  //初始化MDI
  initMDI();

  connect(ui->leftBar->GetTreeWidget(), &QTreeWidget::itemClicked, this, &MainWindowHome::changeMDISubWindow);
}

MainWindowHome::~MainWindowHome() {
  delete ui;
}

//重写eventFilter 实现鼠标按住左键可以移动窗口
bool MainWindowHome::eventFilter(QObject *watched, QEvent *event) {
  if (watched == this) {
    static QPoint mousePoint;         //为什么要用static
    static bool mousePressed = false; //为什么要用static

    QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);

    //点击鼠标事件
    if (mouseEvent->type() == QEvent::MouseButtonPress) {
      //按下左键
      if (mouseEvent->button() == Qt::LeftButton) {
        mousePressed = true;
        mousePoint = mouseEvent->globalPos() - this->pos();
      }
    }
    //松开鼠标按键
    else if (mouseEvent->type() == QEvent::MouseButtonRelease) {
      mousePressed = false;
    }
    //鼠标拖住移动
    else if (mouseEvent->type() == QEvent::MouseMove) {
      if (mousePressed) {
        this->move(mouseEvent->globalPos() - mousePoint);
        return true;
      }
    }
  }

  return QWidget::eventFilter(watched, event); //?
}

//
bool MainWindowHome::nativeEvent(const QByteArray &eventType, void *message, long *result) {
#ifdef Q_OS_WIN
  MSG *msg = (MSG *)message;
  switch (msg->message) {
  case WM_NCHITTEST: {
    QPoint pos = mapFromGlobal(QPoint(LOWORD(msg->lParam), HIWORD(msg->lParam)));
    bool left = pos.x() < MainWindowHomeSpace::LeftPadding;
    bool right = pos.x() > width() - MainWindowHomeSpace::LeftPadding;
    bool top = pos.y() < MainWindowHomeSpace::LeftPadding;
    bool bottom = pos.y() > height() - MainWindowHomeSpace::LeftPadding;
    if (left && top) {
      *result = HTTOPLEFT;
    } else if (left && bottom) {
      *result = HTBOTTOMLEFT;
    } else if (right && top) {
      *result = HTTOPRIGHT;
    } else if (right && bottom) {
      *result = HTBOTTOMRIGHT;
    } else if (left) {
      *result = HTLEFT;

    } else if (right) {
      *result = HTRIGHT;
    } else if (top) {
      *result = HTTOP;
    } else if (bottom) {
      *result = HTBOTTOM;
    } else {
      return false;
    }
    return true;

  } break;
  default:
    break;
  }
#endif

  return false;
}

#ifdef Q_OS_WIN
bool MainWindowHome::winEvent(MSG *message, long *result) {
  return nativeEvent("windows_generic_MSG", message, result);
}
#endif

void MainWindowHome::initLeftBar() {
  qDebug() << "ui->leftBar:" << ui->leftBar->height();
  CommonUtility::setIconFont(QChar(0xf137), ui->shrinkButton);
  //收缩按钮
  connect(ui->shrinkButton, &QPushButton::toggled, [=](bool isChecked) {
    //自定义属性-shrinkTree
    QPropertyAnimation *animation = new QPropertyAnimation(ui->leftBar, "shrinkTree");
    animation->setDuration(200);
    animation->setEasingCurve(QEasingCurve::InQuad);
    //收起
    if (isChecked) {
      qDebug() << "isChecked  ui->leftBar->width() :" << ui->leftBar->width();
      CommonUtility::setIconFont(QChar(0xf138), ui->shrinkButton);
      animation->setEndValue(40);
      ui->leftBar->setExpandsOnDoubleClick(false);
      ui->leftBar->setExpand(false);
    }
    //展开
    else {
      qDebug() << "not check   ui->leftBar->width() :" << ui->leftBar->width();
      CommonUtility::setIconFont(QChar(0xf137), ui->shrinkButton);
      animation->setEndValue(150);
      ui->leftBar->setExpandsOnDoubleClick(true);
      ui->leftBar->setExpand(true);
    }
    animation->start(QAbstractAnimation::DeleteWhenStopped);
  });
}

//初始化MDI
void MainWindowHome::initMDI() {
  CHarts *pchart = new CHarts(this);
  // pchart->setWindowFlags(Qt::FramelessWindowHint);
  pchart->setWindowTitle(tr("我的首页"));

  QMdiSubWindow *subWindow1 = new QMdiSubWindow;
  subWindow1->setWidget(pchart);
  //设置关闭删除
  subWindow1->setAttribute(Qt::WA_DeleteOnClose);
  ui->mdiArea->addSubWindow(subWindow1);
  ui->mdiArea->setViewMode(QMdiArea::TabbedView); // Tab多页显示模式
  ui->mdiArea->setTabsClosable(true);             //页面可关闭
  pchart->showMaximized();
}

void MainWindowHome::changeMDISubWindow(QTreeWidgetItem *current, int column) {

  QString strText = current->text(column);
  //判断页面是否已经存在 若已经打开则设为当前页面
  foreach (QMdiSubWindow *subWindow, ui->mdiArea->subWindowList()) {
    // MdiChild *mdiChild = qobject_cast<MdiChild *>(window);
    if (subWindow->windowTitle() == strText) { //如果已经打开过，则获得焦点
      ui->mdiArea->setActiveSubWindow(subWindow);
      QSize size = ui->mdiArea->size();
      subWindow->resize(size);
      ui->mdiArea->setActiveSubWindow(subWindow);
      return;
    }
  }

  if (strText == "普通交易") {
    MyTableWidget *tableWidget = new MyTableWidget(this);
    tableWidget->setWindowTitle(tr("普通交易"));

    QMdiSubWindow *subWindow1 = new QMdiSubWindow;
    subWindow1->setWidget(tableWidget);
    //设置关闭删除
    subWindow1->setAttribute(Qt::WA_DeleteOnClose);

    ui->mdiArea->addSubWindow(subWindow1);
    tableWidget->show();
    QSize size = ui->mdiArea->size();
    subWindow1->resize(size);
    ui->mdiArea->setActiveSubWindow(subWindow1);
  }
}
