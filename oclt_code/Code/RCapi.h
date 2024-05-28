//RC API
// Run Config API

//Copyright FoxaXu 2024
// Based on OpenCppLangTab

#include"../shload.h"
#include"../Code/ThirdPartyCode.h"

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

bool _rcset_shell_log;

bool _rcset_crash_reload;

string _rcbind_pluginscript, _rcbind_pluginpath,_rcbind_thirdbind,_rcbind_autorun,_rcbind_autorunargs;
string _rcbind_logrec;
string _rcbind_langpath;
string _rcset_lang;
string _rcset_seclang;
string _rcbind_serverapi;
string _rc_active_key;

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

string url_cache;
bool _api_request_download(string Address,string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	_p("api server :  " + _rcbind_serverapi);
	_p("request some files...   please wait");
	_p("url :  " + url_cache);
	if (!_urldown_api_nocache(url_cache, Save)){
		_p("URL Request Failed");
		return false;
	}
	return true;
}

bool _api_request_clear(string Address, string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	if (!_urldown_api_nocache(url_cache, Save)) {
		return false;
	}
	return true;
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
		_soildwrite_write("$EnableCrashReload=true;");
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
		_soildwrite_write("$EnableShellLog=true;");
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
		_soildwrite_write("$SecondLanguage=en-us;");
		_soildwrite_write("");
		_soildwrite_write("//Server");
		_soildwrite_write("$RootAPIServer=https://calciumservices.foxaxu.com/api;");
		_soildwrite_write("$KernelActive={NotActive};");
		_soildwrite_write("");
		_soildwrite_close();
	}
	_rcset_syscmd = _RcLoad_TransApi("EnableSystemCommand");
	_rcset_anticrash = _RcLoad_TransApi("EnableAntiCrash");
	_rcset_crash_reload = _RcLoad_TransApi("EnableCrashReload");
	_rcset_logrec = _RcLoad_TransApi("EnableLogRecord");
	_rcset_allowsu = _RcLoad_TransApi("AllowSuperUser");
	_rcset_allowdiredit = _RcLoad_TransApi("AllowDirectoryEdit");
	_rcset_allowtp = _RcLoad_TransApi("AllowThirdPartyPlugin");
	_rcset_shelledit = _RcLoad_TransApi("AllowShellEdit");
	_rcset_scriptedit = _RcLoad_TransApi("AllowScriptEdit");
	_rcset_directmode = _RcLoad_TransApi("UseDirectRead");

	_rcset_aosr = _RcLoad_TransApi("AutoOpenShellAfterRun");
	_rcset_shell_log = _RcLoad_TransApi("EnableShellLog");

	//String
	_rcbind_autorun = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRun"));
	_rcbind_autorunargs = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "AutoRunArgs"));
	_rcbind_thirdbind = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "ThirdBind"));
	_rcbind_pluginpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginPath"));
	_rcbind_pluginscript = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultPluginScript"));
	_rcbind_logrec = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultLogRecord"));
	_rcbind_langpath = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "DefaultLanguagePath"));

	_rcset_lang = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "Language"));
	_rcset_seclang = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "SecondLanguage"));
	_rcbind_serverapi = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "RootAPIServer"));
	_rc_active_key= _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "KernelActive"));

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


string cachecstp;
string _cstp_file_write = "a.cstp";
bool _$cstp_writeapi(string file) {
	if (!check_file_existence(file)) {
		_pv("Cstp _$lang.loadfail :  _$lang.filenotfound");
		return false;
	}
	_soildwrite_write("$sign_file_output(" + file + ");");

	for (int readptr = 1; true; readptr++) {
		cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			_p("End LoadScript. Total :  " + to_string(readptr));
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_write("$sign_file_close;");
	return true;
}

string getfile;
bool _cstp_maker(string make_file_header,string file) {
	_cstp_file_write = file;
	_p("Execute to " + _cstp_file_write);
	if (check_file_existence(_cstp_file_write)) {
		_fileapi_del(_cstp_file_write);
	}
	_soildwrite_open(_cstp_file_write);
	if (!check_file_existence(make_file_header)) {
		_pv("Cstp Make failed :   _$lang.filenotfound");
		return false;
	}
	_soildwrite_write("calcium_script_text_package");
	_soildwrite_write("//Text Package");
	for (int readptr = 1; true; readptr++) {
		getfile = cachecstp = LineReader(make_file_header, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
		_p("Add File :   " + cachecstp);
		if (_$cstp_writeapi(cachecstp)) {
			_pv("Cstp File :  " + getfile);
		}
		else {
			_pv("Failed :  " + getfile);
		}
		continue;
	}
	_pv("cstp make _$lang.complete");

	return true;
}

int readptr = 1;
bool _$cstp_unpackapi(string file,string resourcefile,int startline,string extract_dir) {
	readptr++;
	_p("Extract File :  " + file);
	if (check_file_existence(extract_dir + "/" + file)) {
		_fileapi_del(extract_dir + "/" + file);
	}
	creatpath(file);
	_soildwrite_open(extract_dir + "/" + file);
	for (; true; readptr++) {
		cachecstp = LineReader(resourcefile, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			return false;
		}
		if (SizeRead(cachecstp, 16) == "$sign_file_close") {
			break;
		}
		_soildwrite_write(cachecstp);
	}
	_soildwrite_close();
	if (!check_file_existence(extract_dir + "/" + file)) {
		_p("failed to write file " + file);
		return false;
	}
	else {
		return true;
	}

	return false;
}

bool _cstp_unpack(string unpack_path, string file) {
	_p("Extract Package " + file);
	if (!check_file_existence(file)) {
		_pv("Cstp Unpack failed :   _$lang.filenotfound " + file);
		return false;
	}
	for (; true; readptr++) {
		getfile = cachecstp = LineReader(file, readptr);
		if (cachecstp == "overline") {
			break;
		}
		if (cachecstp == "ReadFailed") {
			break;
		}
		if (SizeRead(cachecstp,17) == "$sign_file_output") {
			getfile = PartReadA(cachecstp, "(", ")", 1);
			if (!_$cstp_unpackapi(getfile,file, readptr,unpack_path)) {
				_pv("Failed :  " + getfile);
			}
		}
		continue;
	}
	_pv("cstp unpack _$lang.complete");
	return true;
}

string dircache;
bool _packsetup(string packid) {
	dircache = _$GetSelfPath + "/Setup_" + packid;
	if (!_api_request_download(packid,dircache)) {
		_pv("_packsetup _$lang.fail :  " + packid);
		return false;
	}

	_cstp_unpack(_rcbind_pluginscript, dircache);
	_p("complete ...");

	return true;
}

string active_id;
string at_cache;
bool _active_calcium(string Key_Register) {
	if (_KV_relver$int > 5) {
		//No Verify
		return true;
	}
	if (SizeRead(Key_Register, 10) != "USER-SIGN-") {
		return false;
	}
	active_id = PartReadA(Key_Register, "(", ")", 1);

	if (!_api_request_clear("activeRequest/" + active_id, "ActiveSign.tmp")) {
		_p("Cannot Verify your Active Code is Valid");
		return false;
	}

	at_cache = _fileapi_textread("ActiveSign.tmp", 1);
	_fileapi_del("ActiveSign.tmp");

	if (Key_Register == at_cache) {
		return true;
	}

	_p("Invalid Activity Key");
	return false;
}


bool _active_request(string key_reg) {
	_kernel_active = _active_calcium(key_reg);
	if (_kernel_active == true) {
		if (key_reg != "{NotActive}") {
			_write_sipcfg(buildshell, "KernelActive", key_reg);
		}
	}

	return _kernel_active;
}