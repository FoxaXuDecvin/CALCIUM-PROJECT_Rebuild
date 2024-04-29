#pragma once

#include"../shload.h"


void TypeHelpMenu() {
	_p("----------------------------------------------------------");
	_p("Based on OCLT  " + $version_title + "  Base version :   " + $version_code_str);
	_p("OCLT CodeName :   " + $codename + "  " + $version_msg);
	_p("OS Kernel £º" + _Run_SysKernel);
	_p("----------------------------------------------------------");
	_p("Calcium Script Core   " + _KernelVersion);
	_p("Copyright FoxaXu " + $year_message);
	_p("Calcium Project Rebuild    .....");
	_p("Github : https://github.com/FoxaXuDecvin/Calcium-Project");
	_p("Args Size :   " + _get_argslonger());
}

//Args API
void argsApi(string args$api) {

	//if (argsSetExit) set true
	//Process will close after args run

	//Args Switch
	if (args$api == "-run") {
		_setnextargs_runscript = true;
		return;
	}

	if (args$api == "-debug") {
		_debugMode = true;
		return;
	}

	if (args$api == "-help") {
		_runmode = _runmode_typehelp;
		return;
	}

	//auto set args
	if (_setnextargs_runscript == true) {
		runscript = args$api;
		_setnextargs_runscript = false;
		_runmode = _runmode_runscript;
	}

	return;
}

//Put Code Here
int _HeadMainLoad() {
	//main
	if (_argslonger == 1) {
		TypeHelpMenu();
		_pause();
		return 0;
	}
	if (_debugMode == true) {
		_p("Runmode ID " + _runmode);
		_p("runscript :  " + runscript);
		_pause();
		return 0;
	}
	if (_runmode == _runmode_typehelp) {
		TypeHelpMenu();
		_pause();
		return 0;
	}
	if (_runmode == _runmode_autoexit) {
		return 0;
	}
	if (_runmode == _runmode_runscript) {

	}

	return 0;
}