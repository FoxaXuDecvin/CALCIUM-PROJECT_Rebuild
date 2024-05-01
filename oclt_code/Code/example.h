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

	if (args$api == "-shell") {
		_runmode = _runmode_openshell;
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

string _user_typebuffer;
bool CK_Shell_open(void) {
	_pn();
	_pn();
	_p("----------------------------------------------------------");
	_p("Calcium Shell Console");
	_p("----------------------------------------------------------");
	_p("Calcium Script Core   " + _KernelVersion);
	_p("Copyright FoxaXu " + $year_message);
	_p("Calcium Project Rebuild    .....");
	_p("type command,   use \"_exit\" to exit.");

	while (true) {
		_pn();
		_prts("Calcium Kernel  " + _KernelVersion + "   Shell Console>");
		_user_typebuffer = _getline_type();

		_api_result = _runcode_api(_user_typebuffer);
		if (_api_result == "exit") {
			_pn();
			_p("Exit Calcium Shell Console");
			return true;
		}

		continue;
	}


	return true;
}

//Put Code Here
int _HeadMainLoad() {
	//main
	if (_runmode == _runmode_null) {
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
		_ckapi_scriptload(runscript);
		return 0;
	}
	if (_runmode == _runmode_openshell) {
		CK_Shell_open();
		return 0;
	}

	return 0;
}