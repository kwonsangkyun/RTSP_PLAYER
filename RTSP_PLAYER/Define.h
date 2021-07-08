#pragma once

#define RTSP_METHOD_OPTION "OPTIONS"
#define RTSP_METHOD_DESCRIBE "DESCRIBE"
#define RTSP_METHOD_SETUP "SETUP"
#define RTSP_METHOD_PLAY "PLAY"
#define RTSP_METHOD_PAUSE "PAUSE"
#define RTSP_METHOD_TEARDOWN "TEARDOWN"
#define RTSP_VERSION "RTSP/1.0"
#define  RTSP_OK "RTSP/1.0 200 OK"
#define CRLF "\r\n"
#define COLON 0x3A

// RTSP header�̸���
#define RTSP_HEADER_NAME_CSEQ "CSeq"
#define RTSP_HEADER_NAME_DATE "Date"
#define RTSP_HEADER_NAME_ALLOW "Allow"
#define RTSP_HEADER_NAME_ACCEPT "Accept"
#define RTSP_HEADER_NAME_USER_AGENT "User-Agent"
#define RTSP_HEADER_NAME_SERVER "Server"
#define RTSP_HEADER_NAME_PUBLIC "Public"
#define RTSP_HEADER_NAME_CONTENT_TYPE "Content-Type"
#define RTSP_HEADER_NAME_CONTENT_LENGTH "Content-Length"
#define RTSP_HEADER_NAME_TRANSPORT "Transport"
#define RTSP_HEADER_NAME_SESSION "Session"
#define RTSP_HEADER_NAME_SCALE "Scale"
#define RTSP_HEADER_NAME_SPEED "Speed"
#define RTSP_HEADER_NAME_RANGE "Range"
#define RTSP_HEADER_NAME_RTP_INFO "RTP-Info"
#define RTSP_HEADER_NAME_AURHENTICATE "WWW-Authenticate"
#define RTSP_SDP "sdp"

#define RTSP_UNAUTHORIZED_CODE "401"
#define RTSP_HEADER_ERROR "Error"

namespace KSK
{
	const int RANDOM_MAX_NUMBER = 32767;
	const char* const DEFAULT_USER_AGENT = "RTSP_PLAYER";
	const char* const DEFAULT_ACCEPT = "application/sdp";
	const char* const DEFAULT_TCP_TRASPORT = "RTP/AVP/TCP;unicast";
	const char* const DEFAULT_UDP_TRASPORT = "RTP/AVP;unicast";

	enum ERtspState
	{
		ERtspState_OPTION,
		ERtspState_DESCRIBE,
		ERtspState_SETUP,
		ERtspState_PLAY,
		ERtspState_TEARDOWN
	};
}