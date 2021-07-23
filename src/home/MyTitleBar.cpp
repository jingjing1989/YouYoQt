#pragma execution_character_set("utf-8")
#include "MyTitleBar.h"
#include "utility/CommonUtility.h"

#include <QApplication>
#include <QDebug>
#include <QEvent>
#include <QHBoxLayout>
#include <QPushButton>
#ifdef Q_OS_WIN
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#endif

MyTitleBar::MyTitleBar(QWidget *parent) : QWidget(parent) {

  logo = new QLabel(this);
  logo->setScaledContents(true);
  logo->setText("YOUYO-爱呦呦");
  logo->setObjectName("logo");

  m_pTitleLabel = new QLabel(this);
  m_pTitleLabel->setObjectName("whiteLabel");
  m_pTitleLabel->setContentsMargins(8, 0, 0, 0);
  m_pTitleLabel->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);

  //最大最小关闭按钮
  minimizeBtn = new QPushButton(this);
  maxBtn = new QPushButton(this);
  closeBtn = new QPushButton(this);

  minimizeBtn->setObjectName("minimizeBtn");
  maxBtn->setObjectName("maxBtn");
  closeBtn->setObjectName("closeBtn");

  minimizeBtn->setToolTip("Minimize");
  maxBtn->setToolTip("Maximize");
  closeBtn->setToolTip("Close");

  // 创建字体
  CommonUtility::setIconFont(QChar(0xf2d1), minimizeBtn);
  CommonUtility::setIconFont(QChar(0xf2d0), maxBtn);
  CommonUtility::setIconFont(QChar(0xf2d3), closeBtn);

  QHBoxLayout *pLayout = new QHBoxLayout;
  pLayout->addWidget(logo);
  pLayout->addWidget(m_pTitleLabel);
  pLayout->addStretch();

  pLayout->addWidget(minimizeBtn);
  pLayout->addWidget(maxBtn);
  pLayout->addWidget(closeBtn);

  pLayout->setMargin(0);
  this->setLayout(pLayout);

  connect(minimizeBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
  connect(maxBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));
  connect(closeBtn, SIGNAL(clicked(bool)), this, SLOT(onClicked()));

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
