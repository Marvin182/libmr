#ifndef MR_LOG_H
#define MR_LOG_H

#ifdef BUILD_WITH_QT

#include <QtDebug>

#define qLog qInfo().noquote().nospace

namespace mr {
namespace log {

const char* messageTypeToStr(QtMsgType type);

void init();
void setLogfile(QtMsgType type, const char* filename);

} // namespace log
} // namespace mr

#endif // BUILD_WITH_QT

#endif // MR_LOG_H
