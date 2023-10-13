#include "jsonModel.h"

#include <iostream>

#include "QDebug"
#include "QFile"
#include "QJsonArray"
#include "QJsonDocument"
#include "QJsonObject"
#include "crypt.h"

JsonModel::JsonModel(const QString key) {
  this->key = key;
  this->file = readFile();
  this->json = readJson(key);
}
const QString JsonModel::kFileName = "encoded.json";

QJsonArray JsonModel::readJson(QString key) {  // парсинг json
  auto decodedFile = Crypt::decrypt(this->file, key, key);

  auto start = decodedFile.indexOf("\n");
  auto jsonStr = decodedFile.sliced(start, decodedFile.length() - start);

  QJsonDocument d = QJsonDocument::fromJson(jsonStr.toUtf8());
  QJsonArray json = d.QJsonDocument::array();
  qDebug() << d;
  return json;
}

QByteArray JsonModel::readFile() { // читаем файл
  QFile file(JsonModel::kFileName);

  file.open(QIODevice::ReadWrite | QIODevice::Text);
  auto readedFile = file.readAll();

  file.close();
  return readedFile;
}

void JsonModel::writeFile() { // запись в файл
  QJsonDocument doc(this->json);
  QString strJson(doc.toJson(QJsonDocument::Compact)); //переводим в строку

  QFile file(JsonModel::kFileName);
  file.open(QIODevice::ReadWrite | QIODevice::Text);
  auto encodedText = Crypt::encrypt((this->key + "\n" + strJson).toUtf8(),
                                    this->key, this->key);    //шифруем 2 раз
  file.write(encodedText);

  file.close();
  file.open(QIODevice::ReadOnly | QIODevice::Text);
  this->file = file.readAll();
}
void JsonModel::writeRowToJSON(JsonModel::Row row) { // новую строку записываем в json
  QJsonObject obj;
  obj[JsonModel::fields.login] = row.login;
  obj[JsonModel::fields.pass] = row.pass;
  obj[JsonModel::fields.url] = row.url;

  this->json.append(obj);
  this->writeFile();
}

JsonModel::Row JsonModel::getRow(int index) { //получение строки по индексу
  QJsonObject jsonRow = json[index].toObject();
  JsonModel::Row row = {jsonRow["url"].toString(), jsonRow["login"].toString(),
                      jsonRow["pass"].toString()};
  return row;
}

JsonModel::Row JsonModel::encrypt(JsonModel::Row row) { // зашифровка 2
  auto login = row.login;
  auto eLogin = Crypt::encrypt((login).toUtf8(), this->key, this->key);

  auto pass = row.pass;
  auto ePass = Crypt::encrypt((pass).toUtf8(), this->key, this->key);

  Row res = {row.url, eLogin, ePass};
  return res;
}

JsonModel::Row JsonModel::decrypt(JsonModel::Row row) { // расшифровка 2
  auto login = row.login;
  auto plainLogin = Crypt::decrypt((login).toUtf8(), this->key, this->key);

  auto pass = row.pass;
  auto plainPass = Crypt::decrypt((pass).toUtf8(), this->key, this->key);

  Row res = {row.url, plainLogin, plainPass};
  return res;
}
