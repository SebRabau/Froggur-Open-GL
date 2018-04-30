#include "controller.hpp"

Model* modelC;
View* viewC;

Controller::Controller(Model* modelt, View *viewt) {
	modelC = modelt;
	viewC = viewt;
}

void Controller::execute()
{
	modelC->play();
}