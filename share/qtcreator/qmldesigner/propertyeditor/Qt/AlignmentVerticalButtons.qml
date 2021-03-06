/**************************************************************************
**
** This file is part of Qt Creator
**
** Copyright (c) 2012 Nokia Corporation and/or its subsidiary(-ies).
**
** Contact: Nokia Corporation (qt-info@nokia.com)
**
**
** GNU Lesser General Public License Usage
**
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this file.
** Please review the following information to ensure the GNU Lesser General
** Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** Other Usage
**
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
** If you have questions regarding the use of this file, please contact
** Nokia at qt-info@nokia.com.
**
**************************************************************************/

import Qt 4.7
import Bauhaus 1.0

QGroupBox {
    id: alignmentVerticalButtons

    property variant theValue: backendValues.verticalAlignment.value;

    property bool blueHigh: false

    property bool baseStateFlag: isBaseState;

    property variant backendValue: backendValues.verticalAlignment;


    onBaseStateFlagChanged: {
        evaluate();
    }

    property bool isInModel: backendValue.isInModel;
    onIsInModelChanged: {
        evaluate();
    }
    property bool isInSubState: backendValue.isInSubState;
    onIsInSubStateChanged: {
        evaluate();
    }

    onTheValueChanged: {
        if (theValue != undefined) {
            topButton.checked = theValue == "AlignTop";
            centerButton.checked = theValue == "AlignVCenter";
            bottomButton.checked = theValue == "AlignBottom";
        }
        evaluate();
    }

    function evaluate() {
        if (!enabled) {
            fontSelector.setStyleSheet("color: "+scheme.disabledColor);
        } else {
            if (baseStateFlag) {
                if (backendValue != null && backendValue.isInModel)
                    blueHigh = true;
                else
                    blueHigh = false;
            } else {
                if (backendValue != null && backendValue.isInSubState)
                    blueHigh = true;
                else
                    blueHigh = false;
            }
        }
    }

    layout: HorizontalLayout {
        QWidget {
            fixedHeight: 32

            QPushButton {
                id: topButton;
                checkable: true
                iconSize.width: 24;
                iconSize.height: 24;
                fixedWidth: 41
                width: fixedWidth
                fixedHeight: 28
                height: fixedHeight
                styleSheetFile: "styledbuttonleft.css";

                iconFromFile: blueHigh ? "images/alignmenttop-h-icon.png" : "images/alignmenttop-icon.png"

                checked: backendValues.verticalAlignment.value == "AlignTop"

                onClicked: {
                    backendValues.verticalAlignment.value = "AlignTop";
                    checked = true;
                    bottomButton.checked = false;
                    centerButton.checked = false;
                }

                ExtendedFunctionButton {
                    backendValue:   backendValues.verticalAlignment;
                    y: 7
                    x: 2
                }

            }
            QPushButton {
                x: 41
                id: centerButton;
                checkable: true
                iconSize.width: 24;
                iconSize.height: 24;
                fixedWidth: 31
                width: fixedWidth
                fixedHeight: 28
                height: fixedHeight
                styleSheetFile: "styledbuttonmiddle.css";

                iconFromFile: blueHigh ? "images/alignmentmiddle-h-icon.png" : "images/alignmentmiddle-icon.png"

                checked: backendValues.verticalAlignment.value == "AlignVCenter"

                onClicked: {
                    backendValues.verticalAlignment.value = "AlignVCenter";
                    checked = true;
                    bottomButton.checked = false;
                    topButton.checked = false;
                }

            }
            QPushButton {
                x: 72
                id: bottomButton;
                checkable: true
                iconSize.width: 24;
                iconSize.height: 24;
                fixedWidth: 31
                width: fixedWidth
                fixedHeight: 28
                height: fixedHeight
                styleSheetFile: "styledbuttonright.css";

                iconFromFile: blueHigh ? "images/alignmentbottom-h-icon.png" : "images/alignmentbottom-icon.png"

                checked: backendValues.verticalAlignment.value == "AlignBottom"

                onClicked: {
                    backendValues.verticalAlignment.value = "AlignBottom";
                    checked = true;
                    centerButton.checked = false;
                    topButton.checked = false;
                }

            }
        }

    }

}
