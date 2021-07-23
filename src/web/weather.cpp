#include "weather.h"

weather::weather(QObject *parent) : QObject(parent) {
  manager = new QNetworkAccessManager(this);
  //发送请求
  queryWeather();
  //关联信号槽
  connect(manager, &QNetworkAccessManager::finished, this,
          &weather::netReplyFinished);
}

weather::weather(QString cityname) {
  qDebug() << __FUNCTION__;
  manager = new QNetworkAccessManager(this);
  this->strCityName = cityname;
  qDebug() << "strCityName:" << strCityName.toUtf8();

  //发送请求
  queryWeather();
  //关联信号槽
  connect(manager, &QNetworkAccessManager::finished, this,
          &weather::netReplyFinished);
}

void weather::setCityName(QString strCityName) {
  this->strCityName = strCityName;
}

QString weather::getCityName() {
  //返回城市名称
  return this->strCityName;
}

//当前日期
QString weather::getCurrentDate() { return this->currentDate; }

//获取温度范围
QString weather::getTempratureRange() { return this->tempratureRange; }
//获取当前温度
QString weather::getCurrentTemprature() { return this->currentTemprature; }
//获取天气类型
QString weather::getWeatherType() { return this->weathertype; }
//获取风向风力
QString weather::getWind() { return this->wind; }
//获取感冒提示
QString weather::getColdInfo() { return this->cold; }
//获取全部信息
QString weather::getAllData() { return this->allArray; }

//获取全部信息
QVector<QMap<QString, QString>> weather::getAllDataMap() {
  return this->dataMap;
}

//查询天气
void weather::queryWeather() {
  qDebug() << __FUNCTION__;
  //先清空数据
  qDebug() << __FUNCTION__;
  this->tempratureRange.clear();
  this->currentTemprature.clear();
  this->cold.clear();
  this->wind.clear();
  this->weathertype.clear();
  this->allArray.clear();

  dataMap.clear(); //刷新的清空，待获取时在加载

  char quest_array[256] = "http://wthrcdn.etouch.cn/weather_mini?city=";
  QNetworkRequest quest;
  qDebug() << strCityName;
  sprintf(quest_array, "%s%s", quest_array, strCityName.toUtf8().data());
  //  QString strurl = "http://wthrcdn.etouch.cn/weather_mini?city=";
  //  strurl += strCityName;
  //  quest.setUrl(strurl);
  //  qDebug() << strurl;
  quest.setUrl(QUrl(quest_array));
  quest.setHeader(QNetworkRequest::UserAgentHeader, "RT-Thread ART");
  qDebug() << "quest_array:" << quest_array;
  //发送get网络请求
  manager->get(quest);
}

void weather::netReplyFinished(QNetworkReply *reply) {
  qDebug() << __FUNCTION__;
  allArray = reply->readAll();

  QJsonParseError err;
  QJsonDocument jsonDoc = QJsonDocument::fromJson(allArray, &err);
  qDebug() << "reply Json error:" << err.error;
  if (jsonDoc.isNull()) {
    qDebug() << "json is null";
    reply->deleteLater(); //销毁请求对象
    qDebug() << QString::fromLocal8Bit("获取天气失败");
    emit this->getDataFailedSignal();
    //获取结束
    emit this->getDataFinisedSignal();
    qDebug() << "获取天气结束";
    return;
  }
  QJsonObject jsonObj = jsonDoc.object();
  if (!jsonObj.contains("data")) {
    qDebug() << "QJsonObject is not  contain data";
    reply->deleteLater(); //销毁请求对象
    qDebug() << QString::fromLocal8Bit("获取天气失败");
    emit this->getDataFailedSignal();
    //获取结束
    emit this->getDataFinisedSignal();
    qDebug() << "获取天气结束";
    return;
  }
  //获取指定key的value
  QJsonValue jsonVal = jsonObj.value("data");
  if (!jsonVal.isObject()) {
    qDebug() << "QJsonValue is not  object";
    reply->deleteLater(); //销毁请求对象
    qDebug() << QString::fromLocal8Bit("获取天气失败");
    emit this->getDataFailedSignal(); //获取结束
    emit this->getDataFinisedSignal();
    qDebug() << "获取天气结束";
    return;
  }

  //获取当前信息
  QJsonObject objdata = jsonVal.toObject();
  this->strCityName = objdata.value("city").toString();
  this->currentTemprature = objdata.value("wendu").toString();
  currentTemprature += "℃";
  qDebug() << currentTemprature;
  cold = objdata.value("ganmao").toString();

  if (!objdata.contains("forecast")) {
    qDebug() << "QJsonObject is not  contain forecast";
    reply->deleteLater(); //销毁请求对象
    qDebug() << QString::fromLocal8Bit("获取天气失败");
    emit this->getDataFailedSignal();
    //获取结束
    emit this->getDataFinisedSignal();
    qDebug() << "获取天气结束";
    return;
  }

  //获取预报信息 当天序号为0 第二天为1 ...
  QJsonValue value = objdata.value("forecast");
  if (value.isArray()) {
    QJsonArray valArray = value.toArray();
    QJsonObject weatherToday = valArray.at(0).toObject();
    //天气类型
    weathertype = weatherToday.value("type").toString();
    qDebug() << weathertype;
    //日期
    currentDate = weatherToday.value("date").toString();
    qDebug() << currentDate;

    //最低温-最高温
    QString low = weatherToday.value("low").toString();
    QString high = weatherToday.value("high").toString();
    tempratureRange =
        low.mid(low.length() - 3, 4) + "-" + high.mid(high.length() - 3, 4);
    qDebug() << tempratureRange;
    //风向+风力
    QString windStrength = weatherToday.value("fengli").toString();
    windStrength.remove(0, 8);
    windStrength.remove(windStrength.length() - 2, 2);
    wind = weatherToday.value("fengxiang").toString() + windStrength;
    qDebug() << wind;

    //获取后几天
    for (int i = 1; i < valArray.count(); i++) {
      QJsonObject jsonObj = value.toArray().at(i).toObject();
      QMap<QString, QString> mapValue;
      //

      //日期
      mapValue["date"] = jsonObj.value("date").toString();
      qDebug() << mapValue["date"];
      //天气类型
      mapValue["type"] = jsonObj.value("type").toString();
      qDebug() << mapValue["type"];

      //最低温  最高温
      mapValue["low"] = jsonObj.value("low").toString();
      mapValue["high"] = jsonObj.value("high").toString();
      qDebug() << mapValue["low"] << mapValue["high"];

      //风向+风力
      QString windStrength = jsonObj.value("fengli").toString();
      windStrength.remove(0, 8);
      windStrength.remove(jsonObj.length() - 2, 2);
      mapValue["wind"] = jsonObj.value("fengxiang").toString() + windStrength;
      qDebug() << wind;
      QString strIndex;
      dataMap.push_back(mapValue);
    }
    qDebug() << "获取天气成功";
    emit this->getDataSuccessedSignal();
  } else {
    qDebug() << "QJsonObject is not  array";
    qDebug() << "获取天气失败";
    emit this->getDataFailedSignal();
  }
  //获取结束
  emit this->getDataFinisedSignal();
  qDebug() << "获取天气结束";
}
