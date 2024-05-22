//Warning Do not running on Visual Studio 2022 Debug mode
//Create BuildShell.cfg will Crash
//Please running on Normal mode to create buildshell.cfg

//RC API
// Run Code API

//Copyright FoxaXu 2024
// Based on OpenCppLangTab

#include"../shload.h"

void _KernelVersion_LoadText(void);
//Define

const string _rc_false = "false";
const string _rc_true = "true";

//Build / Release / Prerelease   -  Release ID 
const string _RCapi_Version = "B1D1";
const string buildshell = _$GetSelfPath + "/calcium_settings.cfg";

//Rc Config var
bool _rcset_syscmd;
bool _rcset_allowsu;
bool _rcset_allowdiredit;
bool _rcset_allowtp;
bool _rcset_anticrash;
bool _rcset_logrec;
bool _rcset_directmode;

bool _rcset_shelledit,_rcset_scriptedit;

bool _rcset_aosr;

string _rcbind_pluginscript, _rcbind_pluginpath,_rcbind_thirdbind,_rcbind_autorun,_rcbind_autorunargs;
string _rcbind_logrec;
string _rcbind_langpath;
string _rcset_lang;

void _pv(string info) {
	_p(_Old_VSAPI_TransVar(info));
	return;
}

void _RcApi_vp_load(void) {
	_varspaceadd("{path}", _$GetSelfPath);
}

string _RcApi_TapiBuffer;
bool _RcLoad_TransApi(string _Rc_ID) {
	_RcApi_TapiBuffer = _load_sipcfg_noreturn(buildshell, _Rc_ID);
	//_p("tapi Buffer :  " + _Rc_ID + "  " + _RcApi_TapiBuffer);
	if (_RcApi_TapiBuffer == _rc_true) {
		return true;
	}
	if (_RcApi_TapiBuffer == _rc_false) {
		return false;
	}

	_p("--------------------------------------------------------------------");
	_p("Null Config Set");
	_p("Setting :   " + _Rc_ID + "       Data :   \"" + _RcApi_TapiBuffer + "\"");
	_p("Data is not true or false");
	_p("Trans Api cannot identify \"" + _RcApi_TapiBuffer + "\"");
	_p("TransApi Return false");
	return false;
}

string file;
bool _direct_read_script = false;
bool _RcApiLoadConfig() {
	file = buildshell;
	if (!check_file_existence(file)) {
		_soildwrite_open(file);
		_soildwrite_write(" //BuildShell SipCfg  --Use  true/false");
		_soildwrite_write("$EnableSystemCommand=false;");
		_soildwrite_write("$EnableAntiCrash=true;");
		_soildwrite_write("$EnableLogRecord=true;");
		_soildwrite_write("$AllowSuperUser=false;");
		_soildwrite_write("$AllowDirectoryEdit=false;");
		_soildwrite_write("$AllowThirdPartyPlugin=false;");
		_soildwrite_write("$AllowShellEdit=true;");
		_soildwrite_write("$AllowScriptEdit=false;");
		_soildwrite_write("$UseDirectRead=false;");
		_soildwrite_write("");
		_soildwrite_write("//ShellSettings");
		_soildwrite_write("$AutoOpenShellAfterRun=true;");
		_soildwrite_write("");
		_soildwrite_write("//Bind");
		_soildwrite_write("$AutoRun=null;");
		_soildwrite_write("$AutoRunArgs=null;");
		_soildwrite_write("");
		_soildwrite_write("//PathBind");
		_soildwrite_write("$ThirdBind={path};");
		_soildwrite_write("$DefaultPluginPath={path}/plugin;");
		_soildwrite_write("$DefaultPluginScript={path}/script;");
		_soildwrite_write("$DefaultLogRecord={path}/logs;");
		_soildwrite_write("$DefaultLanguagePath={path}/lang;");
		_soildwrite_write("");
		_soildwrite_write("//Display Settings");
		_soildwrite_write("$Language=en-us;");
		_soildwrite_close();
	}
	_rcset_syscmd = _RcLoad_TransApi("EnableSystemCommand");
	_rcset_anticrash = _RcLoad_TransApi("EnableAntiCrash");
	_rcset_logrec = _RcLoad_TransApi("EnableLogRecord");
	_rcset_allowsu = _RcLoad_TransApi("AllowSuperUser");
	_rcset_allowdiredit = _RcLoad_TransApi("AllowDirectoryEdit");
	_rcset_allowtp = _RcLoad_TransApi("AllowThirdPartyPlugin");
	_rcset_shelledit = _RcLoad_TransApi("AllowShellEdit");
	_rcset_scriptedit = _RcLoad_TransApi("AllowScriptEdit");
	_rcset_directmode = _RcLoad_TransApi("UseDirectRead");

	_rcset_aosr = _RcLoad_TransApi("AutoOpenShellAfterRun");

	//String
	_rcbind_autorun = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRun"));
	_rcbind_autorunargs = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRunArgs"));
	_rcbind_thirdbind = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "ThirdBind"));
	_rcbind_pluginpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginPath"));
	_rcbind_pluginscript = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginScript"));
	_rcbind_logrec = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultLogRecord"));
	_rcbind_langpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultLanguagePath"));

	_rcset_lang = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "Language"));

	//Create Directory
	if (!_dapi_ExistFolder_check(_rcbind_thirdbind)) {
		_dapi_mkdir(_rcbind_thirdbind);
	}
	if (!_dapi_ExistFolder_check(_rcbind_pluginpath)) {
		_dapi_mkdir(_rcbind_pluginpath);
	}
	if (!_dapi_ExistFolder_check(_rcbind_pluginscript)) {
		_dapi_mkdir(_rcbind_pluginscript);
	}
	if (!_dapi_ExistFolder_check(_rcbind_logrec)) {
		_dapi_mkdir(_rcbind_logrec);
	}
	if (!_dapi_ExistFolder_check(_rcbind_langpath)) {
		_dapi_mkdir(_rcbind_langpath);
	}

	//Auto Set
	_direct_read_script = _rcset_directmode;


	//End

	_KernelVersion_LoadText();

	return true;
}

string _$logfile;
bool _logrec_write(string INFO) {
	if (_rcset_logrec == false) {
		return false;
	}
	if (!check_file_existence(_$logfile)) {
		_fileapi_createmark(_$logfile, "//Calcium Kernel LogFile");
	}
	_fileapi_write(_$logfile,INFO);

	return true;
}

string fitback,fitbuffer;
string _Char_Filter_EndFileName(string fitchar) {
	fitchar = ReplaceChar(fitchar, "\\", "/");
	fitback = "";

	for (int fullsize = fitchar.size(); true; fullsize--) {
		fitbuffer = fitchar[fullsize];
		if (fitbuffer == "/") {
			fitback = cutendchar(fitback);
			return fitback;
		}

		fitback = fitbuffer + fitback;

	}

	return "LineError";
}