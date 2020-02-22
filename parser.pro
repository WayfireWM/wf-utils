TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    lexer/lexer.cpp \
    lexer/literal.cpp \
    lexer/symbol.cpp \
    parser/rule_parser.cpp \
    parser/action_parser.cpp \
    parser/condition_parser.cpp \
    main.cpp \
    action/action.cpp \
    rule/rule.cpp \
    rule/rule_interface.cpp \
    condition/condition.cpp \
    condition/logic_condition.cpp \
    condition/test_condition.cpp

HEADERS += \
    action/action.hpp \
    lexer/lexer.hpp \
    lexer/literal.hpp \
    lexer/symbol.hpp \
    parser/rule_parser.hpp \
    parser/condition_parser.hpp \
    parser/action_parser.hpp \
    utils.hpp \
    condition/condition.hpp \
    rule/rule.hpp \
    rule/rule_interface.hpp \
    condition/logic_condition.hpp \
    condition/test_condition.hpp
