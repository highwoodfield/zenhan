#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <iostream>

/*
* 引数無しで実行した場合、IMEが無効なら0を、有効なら1を標準出力に出力する。
* 引数をつけて実行した場合、それが1ならIMEは有効になり、そうでなければ無効になる。指定された引数を出力する。
*/
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
  std::printf("%lld\n", stat);
  return 0;
}
