#include "StreamDecoderThread.h"

void CStreamDecoderThread::push(const QByteArray& frame)
{
	if (m_pStreamDecoder == nullptr)
		return;

	m_pStreamDecoder->push(frame);
}

void CStreamDecoderThread::run()
{
	QByteArray decodeFrame;
	m_pStreamDecoder = new CStreamDecoder;
	if (m_pStreamDecoder->initialize() == false)
		return;

	while (true)
	{
		if (m_pStreamDecoder->decode(decodeFrame) == true)
			emit onDecodeSuccess(decodeFrame);
		
		if (true == isInterruptionRequested())
			break;

		QThread::msleep(1);
	}
}