#pragma once

#include"../shload.h"
#include"../Code/CalciumKernel.h"

void TypeHelpMenu() {
	_p("----------------------------------------------------------");
	_p("OCLT Version   " + $version_title + "  Base version : " + $version_code_str);
	_p("OS Kernel :    " + _Run_SysKernel);
	_p("----------------------------------------------------------");
	_p("Kernel Version :    " + _KernelVersion + "  " + _KV_rV_Text);
	_p("RCapi Version :     " + _RCapi_Version);
	_p("Copyright FoxaXu " + $year_message);
	_p("Calcium Project Rebuild    .....");
	_p("Github : https://github.com/FoxaXuDecvin/Calcium-Project");
	_p("Language   " + _rcset_lang);
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

	if (args$api == "-args") {
		_setnextargs_addargs = true;
		return;
	}

	//auto set args
	if (_setnextargs_runscript == true) {
		runscript = args$api;
		_setnextargs_runscript = false;
		_runmode = _runmode_runscript;
	}

	if (_setnextargs_addargs == true) {
		script_args = args$api;
		_setnextargs_addargs = false;
	}

	return;
}

string _user_typebuffer;
bool CK_Shell_open(void) {
	_$logfile = _rcbind_logrec + "/ShellLog.log";
	if (check_file_existence(_$logfile))_fileapi_del(_$logfile);
	_global_scriptload = "{ShellMode}";
	_CK_ShellMode = true;
	_logrec_write("[Notice]Calcium Kernel is Running on Shell Mode :  ");
	_pn();
	_pn();
	_p("----------------------------------------------------------");
	_p("Calcium Shell Console");
	_p("----------------------------------------------------------");
	_pv("_$lang.language :  _$lang.about .....  " + _rcset_lang);
	_p("type command,   use \"_exit\" to exit.");

	while (true) {
		_pn();
		_prts("Calcium Kernel  " + _KernelVersion + "   Shell Console>");
		_user_typebuffer = _getline_type() + ";";

		_logrec_write("[Exec]Get Full Command :  -->  " + _user_typebuffer);

		_logrec_write("-start Running -------------------------------------------");
		last_return = _api_result = _runcode_api(_user_typebuffer);
		_logrec_write("Command Execute End, Result -->  " + _api_result);
		_logrec_write("-end -----------------------------------------------------");
		
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

string langfile;
bool LanguageLoad() {
	langfile = _rcbind_langpath + "/" + _rcset_lang;
	if (!check_file_existence(langfile)) {
		return false;
	}
	_logrec_write("Loading  Language :   " + langfile);
	_ckapi_scriptload(langfile,"langmode");
	return true;
}

int AntiCrash_Return_Code;
string ckapi_result;
string AC_FAILCODE = "{Null}";
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
	if (!LanguageLoad()) {
		_p("Failed to Load Language File.");
		_p("Try to reset config. or fix this file :  " + langfile);
		_pn();
		_pause();
		return -1;
	}

	if (_rcset_anticrash == true) {
		if (_anticrash_services == false) {
			AntiCrash_Return_Code = _system_autoRun(_$GetSelfFull, native_argument + " \"-anticrash_ok\"");
			if (AntiCrash_Return_Code == 0) {
				return 0;
			}
			if (AntiCrash_Return_Code == 1) {
				AC_FAILCODE = "SYSTEM_NULL_COMMAND";
			}
			if (AntiCrash_Return_Code == -1001) {
				AC_FAILCODE = "SYSTEM_API_EXCEPTION";
			}
			if (AntiCrash_Return_Code == -1073741819) {
				AC_FAILCODE = "WIN_KERNEL_CONFLICT";
			}
			if (AntiCrash_Return_Code == 34304) {
				AC_FAILCODE = "LINUX_KERNEL_CONFLICT";
			}

			cleanConsole();
			_pn();
			_pv("_$lang.crash.title");
			_pn();
			_pv("     _$lang.crash.t1");
			_pv("     _$lang.crash.t2");
			_pv("     _$lang.crash.t3");
			_pv("     _$lang.crash.errcode" + AC_FAILCODE);
			_pv("      _$lang.crash.kcode :  " + to_string(AntiCrash_Return_Code));
			_pv("     Run Args :  " + native_argument);
			_pn();
			_pv("  _$lang.presskey");
			_pv("  _$lang.crash.report");
			_pn();
			_pn();
			_pause();
			return 0;
		}
	}
	else {
		//_p("Anti Crash Services is " + to_string(_rcset_anticrash));
	}

	if (_rcbind_autorun != "null") {
		_runmode = _runmode_runscript;
		runscript = _rcbind_autorun;
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
		ckapi_result = _ckapi_scriptload(runscript,script_args);
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