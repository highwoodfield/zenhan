#include <cstdio>
#include <cstdlib>
#include <windows.h>
#include <iostream>

int
main(int argc, char** argv)
{
    /*
    ImmGetContext��ImmGetOpenStatus���g�����Ƃ��ł������Ɍ��������A
    ImmGetContext�͎����̃E�B���h�E��Context�����擾�ł��Ȃ��悤���B

    GETOPENSTATUS/SETOPENSTATUS�̎����́A�ȉ���Windows CE�������t�@�����X�����������Ȃ������B
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
