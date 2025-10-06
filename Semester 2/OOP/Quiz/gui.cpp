#include "gui.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>

PresenterWindow::PresenterWindow(Service& s) : service(s) {
    setWindowTitle("Presenter");
    list = new QListWidget;
    idEdit = new QLineEdit; textEdit = new QLineEdit;
    answerEdit = new QLineEdit; scoreEdit = new QLineEdit;
    addBtn = new QPushButton("Add");
    errorLabel = new QLabel;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(list);
    QHBoxLayout* h = new QHBoxLayout;
    h->addWidget(idEdit); h->addWidget(textEdit); h->addWidget(answerEdit); h->addWidget(scoreEdit); h->addWidget(addBtn);
    layout->addLayout(h);
    layout->addWidget(errorLabel);
    setLayout(layout);
    connect(addBtn, &QPushButton::clicked, this, &PresenterWindow::onAdd);
    refresh();
    service.addUpdateCallback([this]() { refresh(); }); // <-- Use addUpdateCallback here
}

void PresenterWindow::refresh() {
    list->clear();
    auto qs = service.getQuestions();
    std::vector<Question> sorted = qs;
    std::sort(sorted.begin(), sorted.end(), [](const Question& a, const Question& b) { return a.getId() < b.getId(); });
    for (const auto& q : sorted)
        list->addItem(QString("%1 | %2 | %3 | %4").arg(q.getId()).arg(QString::fromStdString(q.getText()))
            .arg(QString::fromStdString(q.getCorrectAnswer())).arg(q.getScore()));
}

void PresenterWindow::onAdd() {
    int id = idEdit->text().toInt();
    std::string text = textEdit->text().toStdString();
    std::string answer = answerEdit->text().toStdString();
    int score = scoreEdit->text().toInt();
    std::string error;
    if (!service.addQuestion(id, text, answer, score, error))
        errorLabel->setText(QString::fromStdString(error));
    else
        errorLabel->clear();
    refresh();
}

ParticipantWindow::ParticipantWindow(Service& s, const std::string& name) : service(s), participant(name) {
    setWindowTitle(QString::fromStdString(name));
    list = new QListWidget;
    answerEdit = new QLineEdit;
    answerBtn = new QPushButton("Answer");
    scoreLabel = new QLabel;
    QVBoxLayout* layout = new QVBoxLayout;
    layout->addWidget(scoreLabel);
    layout->addWidget(list);
    QHBoxLayout* h = new QHBoxLayout;
    h->addWidget(answerEdit); h->addWidget(answerBtn);
    layout->addLayout(h);
    setLayout(layout);
    connect(answerBtn, &QPushButton::clicked, this, &ParticipantWindow::onAnswer);
    connect(list, &QListWidget::currentRowChanged, this, &ParticipantWindow::onSelectionChanged);
    refresh();
    service.addUpdateCallback([this]() { refresh(); });
}

void ParticipantWindow::refresh() {
    list->clear();
    auto qs = service.getQuestions();
    std::vector<Question> sorted = qs;
    std::sort(sorted.begin(), sorted.end(), [](const Question& a, const Question& b) { return a.getScore() > b.getScore(); });
    for (const auto& q : sorted) {
        QListWidgetItem* item = new QListWidgetItem(
            QString("%1 | %2 | %3").arg(q.getId()).arg(QString::fromStdString(q.getText())).arg(q.getScore()));
        // Mark green if answered
        for (const auto& p : service.getParticipants())
            if (p.getName() == participant && p.hasAnswered(q.getId()))
                item->setBackground(Qt::green);
        list->addItem(item);
    }
    // Update score
    for (const auto& p : service.getParticipants())
        if (p.getName() == participant)
            scoreLabel->setText(QString("Score: %1").arg(p.getScore()));
}

void ParticipantWindow::onAnswer() {
    int row = list->currentRow();
    if (row < 0) return;
    auto qs = service.getQuestions();
    std::vector<Question> sorted = qs;
    std::sort(sorted.begin(), sorted.end(), [](const Question& a, const Question& b) { return a.getScore() > b.getScore(); });
    int qid = sorted[row].getId();
    std::string ans = answerEdit->text().toStdString();
    bool correct = false;
    if (!service.answerQuestion(participant, qid, ans, correct)) {
        QMessageBox::warning(this, "Error", "Already answered or invalid.");
        return;
    }
    if (correct)
        QMessageBox::information(this, "Correct", "Correct answer!");
    else
        QMessageBox::information(this, "Incorrect", "Wrong answer.");
    refresh();
}

void ParticipantWindow::onSelectionChanged() {
    int row = list->currentRow();
    if (row < 0) return;
    auto qs = service.getQuestions();
    std::vector<Question> sorted = qs;
    std::sort(sorted.begin(), sorted.end(), [](const Question& a, const Question& b) { return a.getScore() > b.getScore(); });
    int qid = sorted[row].getId();
    for (const auto& p : service.getParticipants())
        if (p.getName() == participant) {
            answerBtn->setEnabled(!p.hasAnswered(qid));
            break;
        }
}