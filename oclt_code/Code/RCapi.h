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
const string _RCapi_Version = "C701";
const string buildshell = _$GetSelfPath + "/calcium_settings.cfg";

//Rc Config var
bool _rcset_syscmd;
bool _rcset_allowsu;
bool _rcset_allowdiredit;
bool _rcset_allowtp;
bool _rcset_anticrash;
bool _rcset_logrec;
bool _rcset_directmode;
bool _rcset_trustcheck;

bool _rcset_shelledit,_rcset_scriptedit;

bool _rcset_enforceUTF8;

bool _rcset_aosr;

bool _rcset_shell_log;

bool _rcset_crash_reload;

string _rcbind_pluginscript, _rcbind_pluginpath,_rcbind_thirdbind,_rcbind_autorun,_rcbind_autorunargs;
string _rcbind_logrec;
string _rcbind_langpath;
string _rcset_lang;
string _rcset_seclang;
string _rcbind_serverapi;
string _rc_activate_key;
string _rc_exec_address;

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

bool _api_request_clear_cache(string Address, string Save) {
	url_cache = _rcbind_serverapi + "/" + Address;
	if (!_urldown_api(url_cache, Save)) {
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
		_soildwrite_write("$TrustedServerCheck=true;");
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
		_soildwrite_write("//Windows Only");
		_soildwrite_write("$EnforceUTF-8=true;");
		_soildwrite_write("");
		_soildwrite_write("//Server");
		_soildwrite_write("$RootAPIServer=https://calciumservices.foxaxu.com/api;");
		_soildwrite_write("$Kernelactivate={Notactivate};");
		_soildwrite_write("$ExecuteFile=" + _$GetSelfFull + ";");
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
	_rcset_trustcheck = _RcLoad_TransApi("TrustedServerCheck");

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
	//Lang 
	_rcset_enforceUTF8 = _RcLoad_TransApi("EnforceUTF-8");

	_rcbind_serverapi = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "RootAPIServer"));
	_rc_activate_key= _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "Kernelactivate"));
	_rc_exec_address = _Old_VSAPI_TransVar(_load_sipcfg_noreturn(file, "ExecuteFile"));

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
string LogWriteCache;
bool _logrec_write(string INFO) {
	if (_rcset_logrec == false) {
		return false;
	}
	if (!check_file_existence(_$logfile)) {
		_fileapi_createmark(_$logfile, "//Calcium Kernel LogFile");
		_fileapi_write(_$logfile, "//Log Record on :  " + __GetFullTime());
	}

	LogWriteCache = "[" + __GetFullClock() + "]" + INFO;
	_fileapi_write(_$logfile,LogWriteCache);

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
string filiter_mfh;
string cache_filepath;
string _cstp_file_write = "a.cstp";
bool _$cstp_writeapi(string file) {
	if (!check_file_existence(file)) {
		_pv("Cstp _$lang.loadfail :  _$lang.filenotfound");
		return false;
	}
	cache_filepath = ReplaceChar(file, filiter_mfh, "");
	_soildwrite_write("$sign_file_output(" + cache_filepath + ");");

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
	CreateFileMap_txt("makedirmap.txt", make_file_header);
	_cstp_file_write = file;
	filiter_mfh = make_file_header;
	make_file_header = "makedirmap.txt";
	_p("Execute Pack Directory " + _cstp_file_write);
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
	_fileapi_del("makedirmap.txt");
	_fileapi_del("empty.txt");
	return true;
}

int readptr = 1;
bool _$cstp_unpackapi(string file,string resourcefile,int startline,string extract_dir) {
	_dapi_create_full_path(extract_dir + "/" + file);
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
	dircache = _$GetSelfPath + "/Setup_" + _get_random_s(1,10000);
	if (!_api_request_download(packid,dircache)) {
		if (!_api_request_clear_cache(packid, dircache)) {
			_pv("_packsetup _$lang.fail :  " + packid);
			return false;
		}
	}

	_cstp_unpack(_rcbind_pluginscript, dircache);
	_p("complete ...");

	_fileapi_del(dircache);

	return true;
}

string activate_id;
string at_cache;
bool _TrustedServer;
bool _activate_calcium(string Key_Register) {
	if (_rcset_trustcheck == true) {
		if (!_urldown_api_nocache("https://calciumservices.foxaxu.com/trusted/TrustedServer.txt", "TrustedList.txt")) {
			_TrustedServer = false;
		}
		else {
			if (FindCharLine(1, "TrustedList.txt", _rcbind_serverapi) == -4) {
				_TrustedServer = false;
			}
			else {
				_TrustedServer = true;
			}
			_fileapi_del("TrustedList.txt");
		}
	}
	else {
		_TrustedServer = false;
	}
	
	if (_KV_relver$int > 4) {
		//No Verify
		if (_rc_exec_address != _$GetSelfFull) {
			_write_sipcfg(buildshell, "ExecuteFile", _$GetSelfFull);
			_rc_exec_address = _Old_VSAPI_TransVar(_load_sipcfg(buildshell, "ExecuteFile"));
		}
		return true;
	}
	if (SizeRead(Key_Register, 10) != "USER-SIGN-") {
		return false;
	}
	activate_id = PartReadA(Key_Register, "(", ")", 1);

	if (_TrustedServer == false) {
		_p("You are trying to activate Calcium using an untrusted server.");
		_p("Please use a trusted server. you can read this list https://calciumservices.foxaxu.com/trusted/TrustedServer.txt");
		return false;
	}

	if (!_api_request_clear("activateRequest/" + activate_id, "activateSign.tmp")) {
		_p("Your activation code is invalid");
		return false;
	}

	at_cache = _fileapi_textread("activateSign.tmp", 1);
	_fileapi_del("activateSign.tmp");

	if (Key_Register == at_cache) {
		return true;
	}

	_p("You entered an activation code that is not the current product");
	return false;
}

bool _activate_request(string key_reg) {
	_kernel_activate = _activate_calcium(key_reg);
	if (_kernel_activate == true) {
		if (key_reg != "{Notactivate}") {
			_write_sipcfg(buildshell, "Kernelactivate", key_reg);
		}
	}

	return _kernel_activate;
}

void _var_typetext(string file) {
	if (_existfile(file)) {
		int maxdocsize = getdocmax(file);

		maxdocsize++;

		for (int startRoll = 1; maxdocsize != startRoll; startRoll++) {
			_p(_Old_VSAPI_TransVar(_fileapi_textread(file, startRoll)));
		}
		return;
	}
	else {
		_sh_throw_error("FileAPI.TypeText :  File Not Exist");
		return;
	}
}

void _Create_Analysis_File(string savefile) {
	_soildwrite_open(savefile);
	_soildwrite_write("::Calcium Analysis File");
	_soildwrite_write("::Copyright FoxaXu " + $year_message);
	_soildwrite_write("::Kernel Message");
	_soildwrite_write("-Execute File Path :   " + _$GetSelfFull);
	_soildwrite_write("-System :  " + _Run_SysKernel);
	_soildwrite_write("-Calcium Activate Status :  " + to_string(_kernel_activate));
	_soildwrite_write("-Language :  " + _rcset_lang + "    Second Language :  " + _rcset_seclang);
	_soildwrite_write("-Version :  " + _KernelVersion);
	_soildwrite_write("-Created Time :  " + __GetFullTime());
	_soildwrite_write("");
	_soildwrite_write("");
	_soildwrite_write("");
	_soildwrite_write("----Project ID----");
	_soildwrite_write("-CID  :    " + _CTitle);
	_soildwrite_write("-VerText :     " + _KV_rV_Text);
	_soildwrite_write("-InsideVersion :     " + InsideVersion);
	_soildwrite_write("----OpenCppLangTab----");
	_soildwrite_write("-OCLT ID :  " + $version_title);
	_soildwrite_write("-OCLT Release :  " + $version_msg);
	_soildwrite_write("-OCLT CodeName :   " + $codename);
	_soildwrite_write("-OCLT RID :    " + $version_code_str);
	_soildwrite_write("-OCLT BuildTime :  " + $buildtime);
	_soildwrite_write("+ Debug ++++++++++++++++++++++++++++++++");
	_soildwrite_write("");
	_soildwrite_write("---- VarSpace Map-----");
	_soildwrite_write(VarSpace);
	_soildwrite_write("----End varspace ----");
	_soildwrite_write("");
	_soildwrite_write("----Execute Address----");
	_soildwrite_write("Script File :  " + _global_scriptload + " Line :  " + to_string(_gf_line) + "  breakpoint :  " + to_string(_gf_cg));
	_soildwrite_write("---- End address----");
	_soildwrite_write("");
	_soildwrite_write("---- Log File ----");
	_soildwrite_write(_$logfile);
	_soildwrite_write("---- End Logfile ----");
}