#pragma once
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QSpinBox>
#include <QLabel>
#include "service.h"

class UserWindow : public QWidget {
    Q_OBJECT
    Service& service;
    User user;

    QListWidget* questionList;
    QPushButton* addQuestionBtn;
    QLineEdit* questionInput;

    QListWidget* answerList;
    QPushButton* addAnswerBtn;
    QLineEdit* answerInput;

    QSpinBox* voteSpinBox;
    QLabel* voteLabel;

    int selectedQuestionId = -1;
    int selectedAnswerId = -1;

    void refreshQuestions();
    void refreshAnswers();
    void connectSignals();

private:
    int lastVotes = 0;

public:
    UserWindow(Service& service, const User& user, QWidget* parent = nullptr);

public slots:

    void onQuestionSelected();
    void onAddQuestion();
    void onAddAnswer();
    void onAnswerSelected();
    void onVoteChanged(int value);
    void update();
};

class SearchWindow : public QWidget {
    Q_OBJECT
    Service& service;

    QLineEdit* searchInput;
    QLabel* bestMatchLabel;
    QListWidget* topAnswersList;

    void refreshSearch();

public:
    SearchWindow(Service& service, QWidget* parent = nullptr);

public slots:
    void onSearchTextChanged(const QString&);
    void update();
};
