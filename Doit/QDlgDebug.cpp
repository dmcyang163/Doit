#include "QDlgDebug.h"


QDlgDebug::QDlgDebug(QWidget* parent) : QDialog(parent) {
    setWindowTitle("Debug Output");
    setGeometry(100, 100, 600, 400);

    QVBoxLayout* layout = new QVBoxLayout(this);
    m_textEdit = new QTextEdit(this);
    layout->addWidget(m_textEdit);

    QPushButton* clearButton = new QPushButton("Clear", this);
    connect(clearButton, &QPushButton::clicked, m_textEdit, &QTextEdit::clear);
    layout->addWidget(clearButton);

    // 初始化流缓冲区
    m_coutBuffer = nullptr;
    m_cerrBuffer = nullptr;
    m_coutOriginalBuffer = nullptr;
    m_cerrOriginalBuffer = nullptr;
}


QDlgDebug::~QDlgDebug() {
    if (m_coutBuffer)
    {
        std::cout.rdbuf(m_coutOriginalBuffer);
        delete m_coutBuffer;
    }
    if (m_cerrBuffer)
    {
        std::cerr.rdbuf(m_cerrOriginalBuffer);
        delete m_cerrBuffer;
    }
}


void QDlgDebug::show() {
    if (!m_coutBuffer)
    {
        m_coutBuffer = new QtStreamBuffer(m_textEdit);
        m_cerrBuffer = new QtStreamBuffer(m_textEdit);
        m_coutOriginalBuffer = std::cout.rdbuf();
        m_cerrOriginalBuffer = std::cerr.rdbuf();
        std::cout.rdbuf(m_coutBuffer);
        std::cerr.rdbuf(m_cerrBuffer);
    }
    QDialog::show();
}


QTextEdit* QDlgDebug::textEdit() const {
    return m_textEdit;
}