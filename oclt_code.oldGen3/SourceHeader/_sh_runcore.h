//Run Core

#pragma once
#include "../SourceHeader/include.h"
//Define
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA);

string araBuffer;
string $quomark = "\"";
string $sqmark = "\'";

//Run any program in any system
//    _system_autoRun("C:\Windows\Notepad.exe","Example.txt");
//    _system_autoRun("./home/desktop/app.run","example");
int resultCode;
int _system_autoRun(string file, string arguments) {
	if (!check_file_existenceA(file)) return -1001;

	if (_Run_SysKernel == Win32_kernel) {
		file = ReplaceChar(file, "/", "\\");
		araBuffer = $quomark + $quomark + file + $quomark + " " + arguments + $quomark;
		resultCode = system(araBuffer.c_str());
	}

	if (_Run_SysKernel == Linux_kernel) {
		file = ReplaceChar(file, "\\", "/");
		araBuffer = $sqmark + file + $sqmark + " " + arguments;
		resultCode = system(araBuffer.c_str());
	}

	if (resultCode == 1) {
		_p("_system_autoRun API Exception");
		_p("Return  1");
		_p("Use Command :    -->  " + araBuffer);
		_pause();
	}

	return resultCode;
}

string _get_argslonger(void) {
	return to_string(_argslonger);
}