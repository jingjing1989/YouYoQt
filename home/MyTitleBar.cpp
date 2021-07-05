#pragma execution_character_set("utf-8")
#include "MyTitleBar.h"
#include "utility/CommonUtility.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QPushButton>

#include <QApplication>
#include <QDebug>
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

MyTitleBar::MyTitleBar(QWidget *parent) : QWidget(parent) {

  logo = new QLabel(this);
  logo->setFixedSize(20, 20);
  logo->setScaledContents(true);
  logo->setObjectName("logo");

  m_pTitleLabel = new QLabel(this);
  m_pTitleLabel->setObjectName("whiteLabel");
  m_pTitleLabel->setContentsMargins(8, 0, 0, 0);
  m_pTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  //    m_pTitleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

  //最大最小关闭按钮
  minimizeBtn = new QPushButton(this);
  maxBtn = new QPushButton(this);
  closeBtn = new QPushButton(this);

  minimizeBtn->setFixedSize(30, 30);
  maxBtn->setFixedSize(30, 30);
  closeBtn->setFixedSize(30, 30);

  minimizeBtn->setObjectName("minimizeBtn");
  maxBtn->setObjectName("maxBtn");
  closeBtn->setObjectName("closeBtn");

  minimizeBtn->setToolTip("Minimize");
  maxBtn->setToolTip("Maximize");
  closeBtn->setToolTip("Close");

  //按钮

  selectPluginBtn = new QPushButton(this);
  selectPluginBtn->setFixedSize(30, 30);
  selectPluginBtn->setObjectName("selectPluginBtn");
  selectPluginBtn->setToolTip("selectPlugin");
#if 1
  cloudBtn = new QPushButton(this);
  skinBtn = new QPushButton(this);
  cfgBtn = new QPushButton(this);
  sizeBtn = new QPushButton(this);

  cloudBtn->setFixedSize(30, 30);
  skinBtn->setFixedSize(30, 30);
  cfgBtn->setFixedSize(30, 30);
  sizeBtn->setFixedSize(30, 30);

  cloudBtn->setObjectName("cloudBtn");
  skinBtn->setObjectName("skinBtn");
  cfgBtn->setObjectName("cfgBtn");
  sizeBtn->setObjectName("sizeBtn");
#endif

  //  minimizeBtn->setIcon(QIcon(":/icon/minus.png"));
  //  maxBtn->setIcon(QIcon(":/icon/maximize.png"));
  //  closeBtn->setIcon(QIcon(":/icon/close.png"));

  QHBoxLayout *pLayout = new QHBoxLayout;

  pLayout->addWidget(logo);
  pLayout->addWidget(m_pTitleLabel);
  pLayout->addStretch();

  pLayout->addWidget(selectPluginBtn);
  pLayout->addWidget(cloudBtn);
  pLayout->addWidget(skinBtn);
  pLayout->addWidget(cfgBtn);
  pLayout->addWidget(sizeBtn);

  pLayout->addWidget(minimizeBtn);
  pLayout->addWidget(maxBtn);
  pLayout->addWidget(closeBtn);

  pLayout->setMargin(0);
  this->setLayout(pLayout);

  connect(minimizeBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
  connect(maxBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
  connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

  //设置样式
#if 0
  //只有对qApp才可以直接用"file:///:/qss/files/application.css"设置
  QFile styleSheet(":/qss/files/top.css");

  if (!styleSheet.open(QIODevice::ReadOnly)) {
      qWarning("Unable to open :/files/top.qss");
      return;
  }

   this->setStyleSheet(styleSheet.readAll());
#endif

  CommonUtility::setStyleSheet(":/qss/res/qss/defaultstyle/top.css", this);
}

MyTitleBar::~MyTitleBar() {}

void MyTitleBar::mouseDoubleClickEvent(QMouseEvent *event) {
  Q_UNUSED(event);

  emit maxBtn->clicked();
}

void MyTitleBar::mousePressEvent(QMouseEvent *event) {
#ifdef Q_OS_WIN
  if (ReleaseCapture()) {
    QWidget *pWindow = this->window();
    if (pWindow->isTopLevel()) {
      SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
    }
  }
  event->ignore();
#else
#endif
}

bool MyTitleBar::eventFilter(QObject *obj, QEvent *event) {
  switch (event->type()) {
  case QEvent::WindowTitleChange: {
    QWidget *pWidget = qobject_cast<QWidget *>(obj);
    if (pWidget) {
      m_pTitleLabel->setText(pWidget->windowTitle());
      return true;
    }
  }
  case QEvent::WindowIconChange: {
    QWidget *pWidget = qobject_cast<QWidget *>(obj);
    if (pWidget) {
      QIcon icon = pWidget->windowIcon();
      logo->setPixmap(icon.pixmap(logo->size()));
      return true;
    }
  }
  case QEvent::WindowStateChange:
  case QEvent::Resize:
    updateMaximize();
    return true;
  default:
    return QWidget::eventFilter(obj, event);
  }
  return QWidget::eventFilter(obj, event);
}

void MyTitleBar::onClicked() {
  QPushButton *pButton = qobject_cast<QPushButton *>(sender());
  QWidget *pWindow = this->window();
  if (pWindow->isTopLevel()) {
    if (pButton == minimizeBtn) {
      pWindow->showMinimized();
    } else if (pButton == maxBtn) {
      pWindow->isMaximized() ? pWindow->showNormal() : pWindow->showMaximized();
    } else if (pButton == closeBtn) {
      pWindow->close();
    }
  }
}

void MyTitleBar::updateMaximize() {
  QWidget *pWindow = this->window();
  if (pWindow->isTopLevel()) {
    bool bMaximize = pWindow->isMaximized();
    if (bMaximize) {
      maxBtn->setToolTip(tr("Restore"));
      maxBtn->setProperty("maximizeProperty", "restore");
    } else {
      maxBtn->setProperty("maximizeProperty", "maximize");
      maxBtn->setToolTip(tr("Maximize"));
    }

    maxBtn->setStyle(QApplication::style());
  }
}
