#ifndef CAROUSEL_H
#define CAROUSEL_H

#include <QDebug>
#include <QLabel>
#include <QList>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QTimer>
#include <QWidget>

namespace CarouselSpace {

const int INTERVAL_TIMER = 3000;
const int ANIMATION_DURTION = 200;
const QByteArray ANIMATION_GEOMETRY = "geometry";
const QString FIRST_IMAGE_PATH = ":/image/files/images/carousel/1.jpg";
const QString SECOND_IMAGE_PATH = ":/image/files/images/carousel/2.jpg";
const QString THIRD_IMAGE_PATH = ":/image/files/images/carousel/3.jpg";
const QString FOURTH_IMAGE_PATH = ":/image/files/images/carousel/4.jpg";
const QString FIFTH_IMAGE_PATH = ":/image/files/images/carousel/5.jpg";

enum SortWidget {
  SORT_FIRST,
  SORT_SECOND,
  SORT_THIRD,
  SORT_FOURTH,
  SORT_FIFTH,
};

} // namespace CarouselSpace
// 使用双向链表思想
typedef struct BannaData {
  QPushButton *pushButton;
  QLabel *currentImageLabel;
  QLabel *nextImageLabel;
  QLabel *preImageLabel;
  QPropertyAnimation *proAnimation;
} BannaData;
typedef struct ImageAnimationData {
  QLabel *labelCurrent;
  QLabel *labelPre;
  QLabel *labelNext;
  QPushButton *pushButton;
  QPropertyAnimation *properAnimation;

} ImaData;

namespace Ui {
class Carousel;
}

class Carousel : public QWidget {
  Q_OBJECT

public:
  explicit Carousel(QWidget *parent = nullptr);
  ~Carousel();

  //每隔几秒切换图片
  void ChangeImage();

  //设置向后移动图片
  void SetNextAnimation();
  //设置向前移动图片
  void SetPreAnimation();

  //图层排序
  void sortGeometry();

private:
  Ui::Carousel *ui;

  QTimer *changeTimer = nullptr;
  QList<ImaData> imaDataList;
  QParallelAnimationGroup animationGroup;
  int centerIndex = CarouselSpace::SORT_THIRD;

  void initWidget();
};

#endif // CAROUSEL_H
