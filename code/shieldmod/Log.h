/*
 * ShieldMod file
 * 
 * Tse Ojeng
 */

#ifndef shieldmod_log_h
#define shieldmod_log_h

#include <string>
#include <deque>

#define CAPCONSOLELOG(x) shieldmod::log_->Logg(x)

namespace shieldmod
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

} // namespace shieldmod

#endif