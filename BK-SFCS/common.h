#ifndef COMMON_H
#define COMMON_H


#include <Windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <unordered_map>

// Threading
#include <thread>
#include <chrono>

#define DATEFORMAT "%F %X"

// RapidJSON
#include "rapidjson/rapidjson.h"
#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"

// Qt Quick
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QObject>
#include <QString>
#include <QDate>
#include <QList>
#include <QQuickItem>

// Globals (QML and C++)
extern QList<QObject*> fleet_list;
extern QList<QObject*> contracts_list;

using namespace std;




#endif // COMMON_H
