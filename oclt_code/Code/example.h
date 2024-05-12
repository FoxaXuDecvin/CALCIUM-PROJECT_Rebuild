#pragma once

#include"../shload.h"
#include"../Code/CalciumKernel.h"

void TypeHelpMenu() {
	_p("----------------------------------------------------------");
	_p("Based on OCLT  " + $version_title + "  Base version :   " + $version_code_str);
	_p("OCLT CodeName :   " + $codename + "  " + $version_msg);
	_p("OS Kernel :    " + _Run_SysKernel);
	_p("----------------------------------------------------------");
	_p("Calcium Script Core   " + _KernelVersion + "  " + _KV_rV_Text);
	_p("RCapi :   " + _RCapi_Version);
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

	if (args$api == "-version") {
		_runmode = _runmode_listversion;
		return;
	}

	if (args$api == "-anticrash_ok") {
		_anticrash_services = true;
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
	_global_scriptload = "{ShellMode}";
	_CK_ShellMode = true;
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
		_user_typebuffer = _getline_type() + ";";

		last_return = _api_result = _runcode_api(_user_typebuffer);
		if (_api_result == "runid.exit") {
			_pn();
			_p("Exit Calcium Shell Console");
			return true;
		}

		if (_api_result == "runid.entershell") {
			_p("The current environment is in Shell Mode");
		}

		if (_stop_exec_script == true) {
			_pn();
			_p("  -Shell Closed :   return data = " + _api_result);
			return 0;
		}

		continue;
	}


	return true;
}

int AntiCrash_Return_Code;
string ckapi_result;
//Put Code Here
int _HeadMainLoad() {
	_RcApi_vp_load();
	if (!_RcApiLoadConfig()) {
		_p("Failed to Load RCapi.");
		_p("Config file is missing :  " + buildshell);
		_p("try to repair and try again.");
		_pause();
		return -1;
	}

	if (_rcset_anticrash == true) {
		if (_anticrash_services == false) {
			AntiCrash_Return_Code = _system_autoRun(_$GetSelfFull, native_argument + " -anticrash_ok");
			if (AntiCrash_Return_Code == 0) {
				return 0;
			}
			cleanConsole();
			_p("oh.  oops.");
			_pn();
			_p("   :(  Calcium Kernel crashed");
			_pn();
			_p("     We are unable to analyze the cause of the error");
			_p("     If this issue affects your use");
			_p("     Report it to us on https://www.foxaxu.com/contact");
			_p("     Kernel return status code :  " + to_string(AntiCrash_Return_Code));
			_pn();
			_p("  Press Enter to Close this report");
			_p("  Please include the repro method with the report");
			_pn();
			_pn();
			_pause();
			return 0;
		}
	}
	else {
		//_p("Anti Crash Services is " + to_string(_rcset_anticrash));
	}

	//main
	if (_runmode == _runmode_null) {
		TypeHelpMenu();
		_pause();
		if (_rcset_aosr == true) {
			_runmode = _runmode_openshell;
		}
		else {
			return 0;
		}
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
		ckapi_result = _ckapi_scriptload(runscript);
		if (ckapi_result == "runid.entershell") {
			_runmode = _runmode_openshell;
		}
		else {
			return 0;
		}
		
	}
	if (_runmode == _runmode_openshell) {
		CK_Shell_open();
		return 0;
	}
	if (_runmode == _runmode_listversion) {
		_pn();
		_p("Calcium Project   " + _KernelVersion + "(" + _KV_rV_Text + ")");
		_p("RCapi Version :   " + _RCapi_Version);
		_p("Inside Version :   " + InsideVersion);
		_pn();
		_p("OpenCppLangTab Version :  " + $version_code_str + "  (" + $codename + ")");
		_p("OCLT Timestamp :   " + $buildtime);
		_p("Operating system :   " + _Run_SysKernel);
		_p("Run Command Argument :  " + native_argument);
		_p("File Path :  " + _$GetSelfFull);
		_p("Local Config :   " + buildshell);
		_pn();
		_p("Copyright FoxaXu");
		_p($year_message);
		_p("All rights reserved.");
		_pause();
		return 0;
	}

	return 0;
}