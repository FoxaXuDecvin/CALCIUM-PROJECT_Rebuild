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
const string buildshell = _$GetSelfPath + "/Buildshell.cfg";

//Rc Config var
bool _rcset_syscmd;
bool _rcset_allowsu;
bool _rcset_allowdiredit;
bool _rcset_allowtp;

bool _rcset_shelledit,_rcset_scriptedit;

bool _rcset_aosr;

string _rcbind_pluginscript, _rcbind_pluginpath,_rcbind_thirdbind;

void _RcApi_vp_load(void) {
	_varspaceadd("{path}", _$GetSelfPath);
}

string _RcApi_TapiBuffer;
bool _RcLoad_TransApi(string _Rc_ID) {
	_RcApi_TapiBuffer = _load_sipcfg(buildshell, _Rc_ID);
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
bool _RcApiLoadConfig() {
	file = buildshell;
	if (!check_file_existence(file)) {
		return false;
	}
	_rcset_syscmd = _RcLoad_TransApi("EnableSystemCommand");
	_rcset_allowsu = _RcLoad_TransApi("AllowSuperUser");
	_rcset_allowdiredit = _RcLoad_TransApi("AllowDirectoryEdit");
	_rcset_allowtp = _RcLoad_TransApi("AllowThirdPartyPlugin");
	_rcset_shelledit = _RcLoad_TransApi("AllowShellEdit");
	_rcset_scriptedit = _RcLoad_TransApi("AllowScriptEdit");

	_rcset_aosr = _RcLoad_TransApi("AutoOpenShellAfterRun");

	_rcbind_thirdbind = _Old_VSAPI_TransVar(_load_sipcfg(file, "ThirdBind"));
	_rcbind_pluginpath = _Old_VSAPI_TransVar(_load_sipcfg(file, "DefaultPluginPath"));
	_rcbind_pluginscript = _Old_VSAPI_TransVar(_load_sipcfg(file, "DefaultPluginScript"));

	if (!_dapi_ExistFolder_check(_rcbind_thirdbind)) {
		_dapi_mkdir(_rcbind_thirdbind);
	}
	if (!_dapi_ExistFolder_check(_rcbind_pluginpath)) {
		_dapi_mkdir(_rcbind_pluginpath);
	}
	if (!_dapi_ExistFolder_check(_rcbind_pluginscript)) {
		_dapi_mkdir(_rcbind_pluginscript);
	}

	_KernelVersion_LoadText();

	return true;
}