#ifndef MR_LOG_H
#define MR_LOG_H

#ifdef QT_CORE_LIB

#include <QtDebug>

#define qLog qInfo().noquote().nospace

namespace mr {
namespace log {

const char* messageTypeToStr(QtMsgType type);

void init();
void setLogfile(QtMsgType type, const char* filename);

} // namespace log
} // namespace mr

#endif // QT_CORE_LIB

#endif // MR_LOG_H
