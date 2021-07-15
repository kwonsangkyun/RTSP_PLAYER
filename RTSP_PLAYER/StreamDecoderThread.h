#pragma once

#include <QThread>
#include "StreamDecoder.h"

class CStreamDecoderThread : public QThread
{
	Q_OBJECT
public:
	void push(const QByteArray &frame);

signals:
	void onDecodeSuccess(QByteArray decodeFrame);

protected:
	void run() override;

private:
	CStreamDecoder* m_pStreamDecoder = nullptr;
};