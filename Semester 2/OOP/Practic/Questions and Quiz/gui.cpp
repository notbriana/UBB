#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPalette>
#include <algorithm>

UserWindow::UserWindow(Service& service, const User& user, QWidget* parent)
    : QWidget(parent), service(service), user(user) {
    setWindowTitle(QString::fromStdString(user.getName()));

    questionList = new QListWidget;
    addQuestionBtn = new QPushButton("Add Question");
    questionInput = new QLineEdit;

    answerList = new QListWidget;
    addAnswerBtn = new QPushButton("Add Answer");
    answerInput = new QLineEdit;

    voteSpinBox = new QSpinBox;
    voteLabel = new QLabel("Votes:");
    voteSpinBox->setMinimum(-9999); // or any negative value you want
    voteSpinBox->setMaximum(9999);  // or any positive value you want

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Questions:"));
    mainLayout->addWidget(questionList);

    QHBoxLayout* addQLayout = new QHBoxLayout;
    addQLayout->addWidget(questionInput);
    addQLayout->addWidget(addQuestionBtn);
    mainLayout->addLayout(addQLayout);

    mainLayout->addWidget(new QLabel("Answers:"));
    mainLayout->addWidget(answerList);

    QHBoxLayout* addALayout = new QHBoxLayout;
    addALayout->addWidget(answerInput);
    addALayout->addWidget(addAnswerBtn);
    mainLayout->addLayout(addALayout);

    QHBoxLayout* voteLayout = new QHBoxLayout;
    voteLayout->addWidget(voteLabel);
    voteLayout->addWidget(voteSpinBox);
    mainLayout->addLayout(voteLayout);

    setLayout(mainLayout);

    connectSignals();
    service.addObserver([this]() { this->update(); });
    update();
}

void UserWindow::connectSignals() {
    connect(questionList, &QListWidget::itemSelectionChanged, this, &UserWindow::onQuestionSelected);
    connect(addQuestionBtn, &QPushButton::clicked, this, &UserWindow::onAddQuestion);
    connect(addAnswerBtn, &QPushButton::clicked, this, &UserWindow::onAddAnswer);
    connect(answerList, &QListWidget::itemSelectionChanged, this, &UserWindow::onAnswerSelected);
    connect(voteSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &UserWindow::onVoteChanged);
}

void UserWindow::refreshQuestions() {
    questionList->clear();
    auto sorted = service.getQuestionsSortedByAnswerCount();
    for (const auto& q : sorted) {
        int count = std::count_if(service.getAnswers().begin(), service.getAnswers().end(),
                                  [&q](const Answer& a) { return a.getQuestionId() == q.getId(); });
        questionList->addItem(QString::fromStdString(q.getText() + " [" + std::to_string(count) + " answers]"));
    }
}

void UserWindow::refreshAnswers() {
    answerList->clear();
    voteSpinBox->setEnabled(false);
    voteSpinBox->setValue(0);
    selectedAnswerId = -1;

    if (selectedQuestionId == -1) return;
    auto answers = service.getAnswersForQuestion(selectedQuestionId);
    std::sort(answers.begin(), answers.end(), [](const Answer& a, const Answer& b) {
        return a.getVotes() > b.getVotes();
    });

    for (const auto& a : answers) {
        QString text = QString::fromStdString(
            std::to_string(a.getId()) + " | " + a.getUserName() + " | " + a.getText() + " | " + std::to_string(a.getVotes()) + " votes"
        );
        QListWidgetItem* item = new QListWidgetItem(text);
        if (a.getUserName() == user.getName()) {
            QBrush yellow(Qt::yellow);
            item->setBackground(yellow);
        }
        answerList->addItem(item);
    }
}

void UserWindow::onQuestionSelected() {
    int row = questionList->currentRow();
    if (row < 0) {
        selectedQuestionId = -1;
        answerList->clear();
        return;
    }
    auto sorted = service.getQuestionsSortedByAnswerCount();
    selectedQuestionId = sorted[row].getId();
    refreshAnswers();
}

void UserWindow::onAddQuestion() {
    std::string text = questionInput->text().toStdString();
    try {
        service.addQuestion(text, user.getName());
        questionInput->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::onAddAnswer() {
    if (selectedQuestionId == -1) return;
    std::string text = answerInput->text().toStdString();
    try {
        service.addAnswer(selectedQuestionId, text, user.getName());
        answerInput->clear();
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}

void UserWindow::onAnswerSelected() {
    int row = answerList->currentRow();
    if (row < 0 || selectedQuestionId == -1) {
        voteSpinBox->setEnabled(false);
        voteSpinBox->setValue(0);
        selectedAnswerId = -1;
        lastVotes = 0;
        return;
    }
    auto answers = service.getAnswersForQuestion(selectedQuestionId);
    std::sort(answers.begin(), answers.end(), [](const Answer& a, const Answer& b) {
        return a.getVotes() > b.getVotes();
        });
    if (row >= (int)answers.size()) return;
    selectedAnswerId = answers[row].getId();
    lastVotes = answers[row].getVotes();
    voteSpinBox->blockSignals(true);
    voteSpinBox->setValue(lastVotes);
    voteSpinBox->blockSignals(false);
    if (answers[row].getUserName() == user.getName()) {
        voteSpinBox->setEnabled(false);
    }
    else {
        voteSpinBox->setEnabled(true);
    }
}

void UserWindow::onVoteChanged(int value) {
    if (selectedAnswerId == -1) return;

    if (value == lastVotes + 1) {
        service.increaseVote(selectedAnswerId, user.getName());
        service.save();
    } else if (value == lastVotes - 1) {
        service.decreaseVote(selectedAnswerId, user.getName());
        service.save();
    } else {
        // Reset to lastVotes if user tries to jump more than 1
        voteSpinBox->blockSignals(true);
        voteSpinBox->setValue(lastVotes);
        voteSpinBox->blockSignals(false);
        return;
    }

    // Get the updated votes from the model
    auto answers = service.getAnswers();
    auto it = std::find_if(answers.begin(), answers.end(), [this](const Answer& a) {
        return a.getId() == selectedAnswerId;
    });
    if (it != answers.end()) {
        lastVotes = it->getVotes();
    }

    /*voteSpinBox->blockSignals(true);
    voteSpinBox->setValue(lastVotes);
    voteSpinBox->blockSignals(false);*/

    refreshAnswers();
    // Optionally, re-select the answer to keep the spinbox in sync
    for (int i = 0; i < answerList->count(); ++i) {
        if (answerList->item(i)->text().toStdString().find(std::to_string(selectedAnswerId) + " |") == 0) {
            answerList->setCurrentRow(i);
            break;
        }
    }
}

void UserWindow::update() {
    refreshQuestions();
    refreshAnswers();
}

// ------------------- SearchWindow -------------------

SearchWindow::SearchWindow(Service& service, QWidget* parent)
    : QWidget(parent), service(service) {
    setWindowTitle("Search Questions");
    searchInput = new QLineEdit;
    bestMatchLabel = new QLabel;
    topAnswersList = new QListWidget;

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(new QLabel("Search:"));
    layout->addWidget(searchInput);
    layout->addWidget(new QLabel("Best Match:"));
    layout->addWidget(bestMatchLabel);
    layout->addWidget(new QLabel("Top 3 Answers:"));
    layout->addWidget(topAnswersList);

    setLayout(layout);

    connect(searchInput, &QLineEdit::textChanged, this, &SearchWindow::onSearchTextChanged);
    service.addObserver([this]() { this->update(); });
    update();
}

void SearchWindow::onSearchTextChanged(const QString& text) {
    refreshSearch();
}

void SearchWindow::refreshSearch() {
    std::string text = searchInput->text().toStdString();
    bestMatchLabel->clear();
    topAnswersList->clear();
    if (text.empty()) return;
    auto results = service.searchQuestionsByText(text);
    if (results.empty()) return;
    const Question& best = results.front().first;
    bestMatchLabel->setText(QString::fromStdString(best.getText()));

    auto answers = service.getAnswersForQuestion(best.getId());
    std::sort(answers.begin(), answers.end(), [](const Answer& a, const Answer& b) {
        return a.getVotes() > b.getVotes();
    });
    for (size_t i = 0; i < std::min<size_t>(3, answers.size()); ++i) {
        const auto& a = answers[i];
        QString text = QString::fromStdString(
            a.getUserName() + " | " + a.getText() + " | " + std::to_string(a.getVotes()) + " votes"
        );
        topAnswersList->addItem(text);
    }
}

void SearchWindow::update() {
    refreshSearch();
}