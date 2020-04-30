#include "controller.h"

void Controller::run() {
    cout << "BK-SFCS ADMINISTRATIVE CONTROL PANEL\n";
    emit finished();
}

Controller::Controller(QObject *parent) : QObject(parent)
{

}

size_t Controller::DisplayStallList() {

}

void Controller::RegisterStall() {

}

void Controller::RemoveStall() {

}

void Controller::Login() {

}

void Controller::Logout() {

}

void Controller::AddFoodItem() {

}

void Controller::RemoveFoodItem() {

}

void Controller::EditFoodItem() {

}
