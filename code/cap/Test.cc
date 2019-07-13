#include <Windows.h>

#include <Utility/PathUtils.h>

#include <Cap.h>

namespace cap
{

CAPTEST TestFindScripts()
{
	// Cap Test Result: the asterisked findfile doesn't see my .lua files
	//                  it works fine with a single asterisk

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

				std::puts("Found file");
			}
		}

		FindClose(handle);
	}
	else
	{
		std::puts("CAPTEST: handle invalid");
	}
}
} // namespace cap