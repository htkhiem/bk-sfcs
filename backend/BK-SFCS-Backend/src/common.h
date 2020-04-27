#ifndef COMMON_H
#define COMMON_H



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
#include "../rapidjson/rapidjson.h"
#include "../rapidjson/document.h"
#include "../rapidjson/prettywriter.h"
#include "../rapidjson/stringbuffer.h"
#include "../rapidjson/filereadstream.h"
#include "../rapidjson/filewritestream.h"

// Qt Quick
#include <QObject>
#include <QString>
#include <QDate>
#include <QList>
#include <QtCore>

using namespace std;
using namespace rapidjson;



#endif // COMMON_H
