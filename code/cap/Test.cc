#include <Windows.h>

#include <Utility/PathUtils.h>

#include <cap_1.h>

namespace cap
{

/* 
CAPTEST TestFindScripts()
{
	// Cap Test Result: the asterisked call doesn't find *.lua files
	// it works fine with a single asterisk

	std::puts("CAPTEST: TestFindScripts");

	auto path = Utility::MakeAbsolutePathW(L"dawnhook\\scripts");

	WIN32_FIND_DATAW fd;
	HANDLE handle = FindFirstFileW((path + L"\\*").c_str(), &fd);

	if (handle != INVALID_HANDLE_VALUE)
	{
		while (FindNextFileW(handle, &fd))
		{
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				std::wstring wstr = path + L"\\" + std::wstring(fd.cFileName);

				//std::puts("Cap test: finds file");
			}
		}

		FindClose(handle);
	}
	else
	{
		std::puts("CAPTEST: handle invalid");
	}
}
*/
} // namespace cap