#pragma once

#include <deque>

#define CAPCONSOLELOG(x) cap::console_->Log(x)

namespace cap
{

extern bool ConsoleActive_;

class Console;

typedef Console *console_t;

extern console_t console_;

console_t Console_();

class Console
{
public:
	Console();

	std::deque<std::string> _deq;

	void Draw();
	
	void Log(const std::string &);
};

} // namespace cap