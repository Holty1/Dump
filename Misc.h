#pragma once
class Misc
{
public:
	/*static BOOL ShowBalloon(HWND hWnd, LPCTSTR title, LPCTSTR text, HICON hIcon);*/
	static BOOL UpdateBalloon(HWND hWnd, LPCTSTR title, LPCTSTR text, HICON hIcon);
	static HWND FindTopWindow(DWORD pid);
	static int Random(int min, int max);
	static BOOL CALLBACK EnumWindowsCallback(HWND hnd, LPARAM lParam);
	static std::vector<HWND> GetToplevelWindows();
	static string CurrentDateTime();

	static void PlayAlerSound();
	static string CurrentDateTimeShort();
	static SYSTEMTIME GetServerTime();
	static float CountDistanceTwoPoints(int x1, int y1, int x2, int y2);
	/*static uint32_t CRC32(const std::string &fp);*/
	static float AngleBetweenTwoPoints(float x1, float y1, float x2, float y2);
};

