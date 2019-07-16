#pragma once

#include <deque>

#define CAPCONSOLELOG(x) cap::log_->Logg(x)

namespace cap
{
extern bool log_active_;

class Log;

typedef Log *log_t;

extern log_t log_;

log_t Log_();

class Log
{
public:
	Log();

	std::deque<std::string> _deq;

	void Draw();
	
	void Logg(const std::string &);
};

} // namespace cap