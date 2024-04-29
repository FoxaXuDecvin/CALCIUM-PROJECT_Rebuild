//Run Core

#pragma once
#include "../SourceHeader/include.h"

string araBuffer;
string $quomark = "\"";
string $sqmark = "\'";

//Run any program in any system
//    _system_autoRun("C:\Windows\Notepad.exe","Example.txt");
//    _system_autoRun("./home/desktop/app.run","example");
int _system_autoRun(string file, string arguments) {
	if (!check_file_existenceA(file)) return -1001;

	if (_Run_SysKernel == Win32_kernel) {
		file = ReplaceChar(file, "/", "\\");
		araBuffer = $quomark + file + $quomark + " " + arguments;
		return system(araBuffer.c_str());
	}

	if (_Run_SysKernel == Linux_kernel) {
		file = ReplaceChar(file, "\\", "/");
		araBuffer = $sqmark + file + $sqmark + " " + arguments;
		return system(araBuffer.c_str());
	}

	return -1002;
}

string _get_argslonger(void) {
	return to_string(_argslonger);
}