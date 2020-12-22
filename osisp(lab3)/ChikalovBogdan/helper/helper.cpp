#include "helper.h"

void SetFalse(QMap<QString, bool> &map) {
    for (auto i = map.begin(); i != map.end(); ++i) {
        i.value() = false;
    }
}

void SetLabS(QLabel &label) {
    label.setText("Success converting!");
}

void SetLabN(QLabel &label) {
    label.setText("");
}