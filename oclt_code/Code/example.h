#pragma once

#include"../shload.h"
#include"../Code/CalciumKernel.h"

bool PreLaunchLoad(void) {
	//Put Preload code here
	//

	__settings_displaylaunchscreen = false;
	_windows_active_65001 = true;

	//End
	return true;
}

void TypeHelpMenu() {
	_p("----------------------------------------------------------");
	_p("OCLT Version   " + $version_title + "  Base version : " + $version_code_str);
	_p("OS Kernel :    " + _Run_SysKernel);
	_p("----------------------------------------------------------");
	_p("Kernel Version :    " + _KernelVersion + "  " + _KV_rV_Text);
	_p("RCapi Version :     " + _RCapi_Version);
	_p("Copyright FoxaXu " + $year_message);
	_p("Calcium Script    .....");
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
		_runmode = _runmode_runscript;
		return;
	}

	if (args$api == "-optimi") {
		_setnextargs_runscript = true;
		_runmode = _runmode_optimi;
		return;
	}

	if (args$api == "-pack") {
		_setnextargs_runscript = true;
		_runmode = _runmode_cstpmake;
		return;
	}

	if (args$api == "-unpack") {
		_setnextargs_runscript = true;
		_runmode = _runmode_cstpunpack;
		return;
	}

	if (args$api == "-to") {
		_setnextargs_addo = true;
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

	if (args$api == "-direct") {
		_direct_read_script = true;
	}

	if (args$api == "-nolang") {
		_skipcheck_language = true;
	}

	//auto set args
	if (_setnextargs_runscript == true) {
		runscript = args$api;
		_setnextargs_runscript = false;
	}

	if (_setnextargs_addargs == true) {
		script_args = args$api;
		_setnextargs_addargs = false;
	}

	if (_setnextargs_addo == true) {
		o_info = args$api;
		_setnextargs_addo = false;
	}

	return;
}

string _user_typebuffer;
bool CK_Shell_open(void) {
	if (_rcset_shell_log == true) {
		_rcset_logrec = true;
	}
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
			if (_shell_lock) {
				_pn();
				_p("  -Stop_exec_Script is true  :   return data = " + _api_result);
				_stop_exec_script = false;
			}
			else {
				_pn();
				_p("  -Shell Closed :   return data = " + _api_result);
				return 0;
			}
		}

		continue;
	}


	return true;
}

int AntiCrash_Return_Code;
string ckapi_result;
string langpackfile;
string AC_FAILCODE = "{Null}";
//Put Code Here
int _HeadMainLoad() {
	if (_anticrash_services == false) {
		_p("Calcium Script " + _KernelVersion + "...   Startup");
	}
	_RcApi_vp_load();
	if (!_RcApiLoadConfig()) {
		_p("Failed to Load RCapi.");
		_p("Config file is missing :  " + buildshell);
		_p("try to repair and try again.");
		_pause();
		return -1;
	}
	if (_skipcheck_language == false) {
		if (!LanguageLoad()) {
			langpackfile = _$GetSelfPath + "/" + "temp_languagepack.pack";
			_p("Install Language Pack ?");
			_prts("type y/n >");

			if (_getline_type() != "n") {
				if (!_api_request_download("lang.txt", langpackfile)) {
					_p("Install Failed");
				}
				else {
					_system_autoRun(_$GetSelfFull, "-nolang -unpack \"" + langpackfile + "\" -to \"" + _$GetSelfPath + "/Lang\"");
					_p("Complete Install Language");
					_fileapi_del(langpackfile);
				}
			}
			LanguageLoad();
		}
	}

	_gf_cg = 0;
	_gf_cgmax = 1;
	_gf_line = 1;
	_gf_charget = "";

	if (_rcset_anticrash == true) {
		if (_anticrash_services == false) {
			Crash_Reload_service:
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
				AC_FAILCODE = "SYSTEM_KERNEL_CONFLICT";
			}
			if (AntiCrash_Return_Code == 34304) {
				AC_FAILCODE = "SYSTEM_KERNEL_CONFLICT";
			}
			if (AntiCrash_Return_Code == -1073740791) {
				AC_FAILCODE = "MEMORY_ACCESS_CRASH";
			}

			cleanConsole();
			_pn();
			_pv("_$lang.crash.title");
			_pn();
			_pv("     _$lang.crash.t1");
			_pv("       _$lang.crash.t2");
			_pv("       _$lang.crash.t3");
			_pv("       _$lang.crash.errcode" + AC_FAILCODE);
			_pv("       _$lang.crash.kcode :  " + to_string(AntiCrash_Return_Code));
			_pv("     _$lang.runargs :  " + native_argument);
			_pn();
			_pv("  _$lang.presskey");
			_pv("  _$lang.crash.report");
			_pn();
			_pn();
			_pause();
			if (_rcset_crash_reload) {
				cleanConsole();
				goto Crash_Reload_service;
			}
			else {
				return 0;
			}
		}
	}
	else {
		//_p("Anti Crash Services is " + to_string(_rcset_anticrash));
	}

	if (_rcbind_autorun != "null") {
		_runmode = _runmode_runscript;
		runscript = _rcbind_autorun;
		script_args = _rcbind_autorunargs;

		ckapi_result = _ckapi_scriptload(runscript, script_args);
		if (ckapi_result == "runid.entershell") {
			_runmode = _runmode_openshell;
		}
		else {
			return 0;
		}
	}

	if (_debugMode == true) {
		_p("Runmode ID " + _runmode);
		_p("runscript :  " + runscript);
		_p("Argument :  " + script_args);
		_p("o info :  " + o_info);
		_pause();
		return 0;
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
	if (_runmode == _runmode_optimi) {
		readbufferA = runscript + "_optimi.ca";
		_p("Optimi Mode");
		if (runscript == "{null}") {
			_p("Command :  <program.exe> -optimi <file>");
			return 0;
		}
		_p("Optimi Script :  " + runscript);
		_p("Output Script :  " + readbufferA);
		if (!check_file_existence(runscript)) {
			_p("File Not Found :  " + runscript);
			_p("Command :  <program.exe> -optimi <file>");
			return 0;
		}
		_soildwrite_open(readbufferA);
		_soildwrite_write("_$directmode;");
		_soildwrite_write("_$nolog;");
		while(true) {
			charCutA = _get_fullLine(runscript, ";");
			if (_gf_status == false) break;
			_soildwrite_write(charCutA);
		}
		_soildwrite_close();

		_p("Optimi Complete");
		return 0;
	}
	if (_runmode == _runmode_cstpmake) {
		_cstp_maker(runscript, o_info);

		return 0;
	}
	if (_runmode == _runmode_cstpunpack) {
		_cstp_unpack(o_info,runscript);

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
		ckapi_result = _ckapi_scriptload(runscript, script_args);
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