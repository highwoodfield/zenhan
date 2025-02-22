#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <iostream>

int
main(int argc, char** argv)
{
    /*
    ImmGetContextやImmGetOpenStatusを使うこともできそうに見えたが、
    ImmGetContextは自分のウィンドウのContextしか取得できないようだ。

    GETOPENSTATUS/SETOPENSTATUSの資料は、以下のWindows CE向けリファレンスしか見つけられなかった。
    https://learn.microsoft.com/en-us/previous-versions/windows/embedded/ms905960(v=msdn.10)
    */

  constexpr LPARAM IMC_GETOPENSTATUS = 5;
  constexpr LPARAM IMC_SETOPENSTATUS = 6;

  auto hwnd = GetForegroundWindow();
  if (!hwnd)
    return 0;

  auto ime = ImmGetDefaultIMEWnd(hwnd);
  if (!ime)
    return 0;

  LPARAM stat;
  if (argc < 2) {
      stat = SendMessage(ime, WM_IME_CONTROL, IMC_GETOPENSTATUS, 0);
  } else {
      stat = std::atoi(argv[1]);
      SendMessage(ime, WM_IME_CONTROL, IMC_SETOPENSTATUS, stat);
  }
  std::printf("%d\n", stat);
  return 0;
}
