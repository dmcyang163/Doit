#ifndef QDLGDEBUG_H
#define QDLGDEBUG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <iostream>
#include "QtStreamBuffer.h"


class QDlgDebug : public QDialog {
public:
    QDlgDebug(QWidget* parent = nullptr);
    ~QDlgDebug();
    void show();
    QTextEdit* textEdit() const;

private:
    QTextEdit* m_textEdit;
    QtStreamBuffer* m_coutBuffer;
    QtStreamBuffer* m_cerrBuffer;
    std::streambuf* m_coutOriginalBuffer;
    std::streambuf* m_cerrOriginalBuffer;
};

#endif // QDLGDEBUG_H