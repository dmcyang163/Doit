#ifndef QTSTREAMBUFFER_H
#define QTSTREAMBUFFER_H

#include <iostream>
#include <QTextEdit>
#include <QMetaObject>
#include <QString>
#include <QMessageBox>
#include <streambuf>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>


class QtStreamBuffer : public std::streambuf {
public:
	QtStreamBuffer(QTextEdit* textEdit);
	~QtStreamBuffer();

protected:
	virtual std::streambuf::int_type overflow(std::streambuf::int_type v) override;
	virtual std::streamsize xsputn(const char* s, std::streamsize n) override;

private:
	QTextEdit* m_textEdit;
	std::string m_buffer;
	const std::size_t m_bufferSize = 1024;
	void flushBuffer();
};

#endif // QTSTREAMBUFFER_H