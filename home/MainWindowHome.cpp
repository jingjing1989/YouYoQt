#include "MainWindowHome.h"
#include "ui_MainWindowHome.h"
#include "utility/CommonUtility.h"

#include <QFile>
#include <QPoint>
#include <QMouseEvent>
#include <QtDebug>
#include <QPropertyAnimation>

#ifdef Q_OS_WIN
#include "windows.h"
#endif

MainWindowHome::MainWindowHome(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindowHome)
{
  ui->setupUi(this);
  //不显示标题栏
  setWindowFlags(Qt::FramelessWindowHint);


  //设置样式
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  QString styleSheet(":/qss/res/qss/defaultstyle/top.css");
  CommonUtility::setStyleSheet(styleSheet,this);

  QString styleSheetlefttop(":/qss/res/qss/defaultstyle/lefttop.css");
  CommonUtility::setStyleSheet(styleSheetlefttop,ui->shrinkButton);
  CommonUtility::setStyleSheet(styleSheetlefttop,ui->collectButton);
  CommonUtility::setStyleSheet(styleSheetlefttop,ui->lockButton);
  CommonUtility::setStyleSheet(styleSheetlefttop,ui->revertButton);

  //ui->shrinkButton->setStyleSheet("border-image:url(:/image/files/images/lefttopbar/shrinkButton_max.png)");



  padding =5;
  this->installEventFilter(this);

  initControl();

}

MainWindowHome::~MainWindowHome()
{
  delete ui;
}

//重写eventFilter 实现鼠标按住左键可以移动窗口
bool MainWindowHome::eventFilter(QObject *watched, QEvent *event)
{
  if(watched ==this){
      static QPoint mousePoint;//为什么要用static
      static bool mousePressed = false;//为什么要用static

      QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

      //点击鼠标事件
      if (mouseEvent->type() == QEvent::MouseButtonPress){
          //按下左键
          if(mouseEvent -> button() == Qt::LeftButton){
              mousePressed = true;
              mousePoint = mouseEvent->globalPos() - this->pos();
            }

        }

      //松开鼠标按键
      else if(mouseEvent->type() == QEvent::MouseButtonRelease){
          mousePressed = false;
        }

      //鼠标拖住移动
      else if(mouseEvent->type() == QEvent::MouseMove){
          if(mousePressed){
              this ->move(mouseEvent ->globalPos() -mousePoint);
              return true;
            }

        }
    }


  return QWidget::eventFilter(watched, event);//?

}


//
bool MainWindowHome::nativeEvent(const QByteArray &eventType, void*message,long *result)
{
#ifdef Q_OS_WIN
  MSG *msg = (MSG*)message;
  switch (msg->message) {
    case WM_NCHITTEST:{
        QPoint pos = mapFromGlobal(QPoint(LOWORD(msg->lParam),HIWORD(msg->lParam)));
        bool left = pos.x() < padding;
        bool right = pos.x() >width() -padding;
        bool top = pos.y() < padding;
        bool bottom = pos.y() >height() -padding;
        if(left && top){
            *result = HTTOPLEFT;
          }
        else if(left && bottom){
            *result = HTBOTTOMLEFT;
        }
        else if (right && top) {
            *result = HTTOPRIGHT;
          }
        else if(right && bottom)
          {
            *result = HTBOTTOMRIGHT;
          }
        else if (left){
            *result = HTLEFT;

          }
        else if (right){
            *result = HTRIGHT;
          }
        else if (top){
            *result = HTTOP;
          }
        else if(bottom){
            *result = HTBOTTOM;
          }
        else
          {
            return false;
          }
        return true;


      }
      break;
    default:
      break;
    }
#endif

    return false;
}


#ifdef Q_OS_WIN
bool MainWindowHome::winEvent(MSG *message, long *result)
{
  return nativeEvent("windows_generic_MSG",message,result);
}
#endif


void MainWindowHome::initControl()
{
//    ui.titleWidget->setFixedWidth(this->width());
//    //这里就是那黄色区域
//    StatusWidget* pWidget = new StatusWidget(ui.upWidget);
//    pWidget->setFixedSize(this->width(), 48);
//    pWidget->move(0, ui.titleWidget->height());
    //点击效果按钮，进行效果展示
connect(ui->shrinkButton, &QPushButton::clicked, [=]() {
  //自定义属性shrinkTree
  QPropertyAnimation *animation =
      new QPropertyAnimation(ui->treeWidgetLeft, "shrinkTree");
  animation->setDuration(300);
  animation->setEasingCurve(QEasingCurve::InQuad);
  //高于最小高度，代表处于展开状态
  if (ui->treeWidgetLeft->width() > 30) {
    animation->setEndValue(30);
    ui->treeWidgetLeft->setExpandsOnDoubleClick(false);
    ui->treeWidgetLeft->setExpand(false);
  }
  //否就是收缩状态
  else {
    animation->setEndValue(ui->treeWidgetLeft->width() + 180);
    ui->treeWidgetLeft->setExpandsOnDoubleClick(true);
    ui->treeWidgetLeft->setExpand(true);
  }
  animation->start(QAbstractAnimation::DeleteWhenStopped);
});
}
