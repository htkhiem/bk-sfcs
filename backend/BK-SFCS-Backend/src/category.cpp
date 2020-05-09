#include "category.h"

Category::Category(QObject *parent)
    : QObject(parent),
      name("NULL"),
      symbol('O'),
      color_start("#FFFFFF"),
      color_end("#FFFFFF"),
      visible(true)
{
}
Category::Category(const QString& cat_name, QChar sym, QColor start, QColor end, QObject *parent)
    : QObject(parent),
      name(cat_name),
      symbol(sym),
      color_start(start),
      color_end(end),
      visible(true)
{
}
QString Category::getName() const {
    return name;
}
void Category::setName(const QString& new_name) {
    if (new_name.isEmpty()) throw invalid_argument("Category name must not be empty");
    name = new_name;
}
QChar Category::getSymbol() const {
    return symbol;
}
void Category::setSymbol(QChar new_symbol) {
    symbol = new_symbol;
}
QColor Category::getStartColor() const {
    return color_start;
}
void Category::setStartColor(QColor new_start) {
    color_start = new_start;
}
QColor Category::getEndColor() const {
    return color_end;
}
void Category::setEndColor(QColor new_end) {
    color_end = new_end;
}
bool Category::isVisible() const {
    return visible;
}
void Category::toggleVisibility(bool new_visible) {
    visible = new_visible;
}
