#pragma once

#define RED_BUTTON                                                                    \
    "QPushButton{"                                                                    \
    "background-color: rgba(154, 46, 93, 0.4);"                                       \
    "}"                                                                               \
    "QPushButton:hover{"                                                              \
    "background: qradialgradient("                                                    \
    "cx: 0.3, cy: -0.4, fx: 0.3, fy: 0.4,"                                            \
    "radius: 1.35, stop: 0 rgba(254, 146, 193, 0.4), stop: 1 rgba(194, 86, 133, 0.4)" \
    ");"                                                                              \
    "}"

#define GREEN_BUTTON                                                                  \
    "QPushButton{"                                                                    \
    "background-color: rgba(46, 154, 93, 0.4);"                                       \
    "}"                                                                               \
    "QPushButton:hover{"                                                              \
    "background: qradialgradient("                                                    \
    "cx: 0.3, cy: -0.4, fx: 0.3, fy: 0.4,"                                            \
    "radius: 1.35, stop: 0 rgba(146, 254, 193, 0.4), stop: 1 rgba(86, 194, 133, 0.4)" \
    ");"                                                                              \
    "}"

#define BEACON_TABLE_ITEM     \
    "border: 1px solid #000;" \
    "color: black;"           \
    "font: 18px 'Ubuntu';"    \
    "font-weight: bold;"
