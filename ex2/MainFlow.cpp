#include "MainFlow.h"

MainFlow::MainFlow() {

}

MainFlow::MainFlow(int x) {
    created = false;
}

void MainFlow::parseInput(string s)throw(exception) {
    creation(s);
}

void MainFlow::creation(string s) {
    created = true;
}

void MainFlow::startFlow() {

}

bool MainFlow::isCreated() const {
    return true;
}
