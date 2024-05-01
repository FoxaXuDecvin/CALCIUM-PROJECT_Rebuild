//Calcium Kernel Base

//Copyright FoxaXu 2024
// Based on OpenCppLangTab

#include"../shload.h"

//VCODE
// 110(Software Version).1(General).1(Release Version).1(Debug/Preview/preRelease/Release  1 - 4)

//releaseVerKnd
const string _KV_rV_Debug = "1";
const string _KV_rV_Preview = "2";
const string _KV_rV_preRelease = "3";
const string _KV_rV_Release = "4";
//rVK END


string _KV_softwareVersion = "110"; //(Software Version)

string _KV_gen = "1";//(General)

string _KV_rv = "1";//(Release Version)

string _KV_releaseVer = _KV_rV_Debug;//(Debug/Preview/preRelease/Release  1 - 4)

string _mk = ".";

string _KernelVersion = _KV_softwareVersion + _mk + _KV_gen + _mk + _KV_rv + _mk + _KV_releaseVer;

//DEFINE

//Define-Head
string _runcode_api(string command);
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA);

//HeadSpaceClean .  Default = true
bool _gf_hsc = true;

//GetFULL API
int _gf_line_maxallow = 128;
bool _gf_status;
int _gf_line = 1;
int _gf_cg = 0;
int _gf_cgmax = 1;
string _gf_FLMark = ";";
string _gf_charget;
string _gf_makebuffer,_gf_getbuffer;
string _get_fullLine(string load_script) {
	if (!check_file_existence(load_script)) {
		return "badfound";
	}
	//Clear Makebuffer
	_gf_makebuffer = "";

	//get and make
	for (;true; _gf_line++) {
		//Reset Char
		for (;true;_gf_cg ++) {
			//_p("Road Fresh    Line :   " + to_string(_gf_line));
			//Textread
			_gf_getbuffer = _fileapi_textread(load_script, _gf_line);
			//Check Status Code
			if (_gf_getbuffer == "overline") {
				_gf_status = false;
				return "badread";
			}
			if (_gf_getbuffer == "ReadFailed") {
				_gf_status = false;
				return "badopen";
			}

			if (_gf_hsc == true) {
				_gf_getbuffer = HeadSpaceCleanA(_gf_getbuffer);
			}

			if (SizeRead(_gf_getbuffer, 2) == "//") {
				_gf_cg = -1;
				_gf_cgmax = 1;
				_gf_line++;
				_gf_charget = "";
				continue;
			}
			if (_gf_getbuffer == "") {
				_gf_cg = -1;
				_gf_cgmax = 1;
				_gf_line++;
				_gf_charget = "";
				continue;
			}

			//GetProcess
			_gf_cgmax = _gf_getbuffer.size();
			//_p("   cg :   " + to_string(_gf_cg) + " cgmax :  " + to_string(_gf_cgmax));

			//OpenProcess
			while (true) {
				//Reset char get
				if (_gf_cg == _gf_cgmax) {
					//_p("Char Reset");
					_gf_cg = -1;
					_gf_cgmax = 1;
					_gf_line++;
					_gf_charget = "";
					break;
				}

				if (_gf_line > _gf_line_maxallow) {
					_gf_status = false;
					return "Over Size";
				}

				//_p("line :  " + to_string(_gf_line) + "   cg :   " + to_string(_gf_cg) + " cgmax :  " + to_string(_gf_cgmax) + "   charMake = " + _gf_makebuffer);

				_gf_charget = _gf_getbuffer[_gf_cg];
				_gf_cg++;
				//_p("charget =  " + _gf_charget);
				_gf_makebuffer = _gf_makebuffer + _gf_charget;
				//_p("_gf_makebuffer = _gf_makebuffer + _gf_charge  ===  _gf_makebuffer  = " + _gf_makebuffer + "  + " + _gf_charget + "$");
				if (_gf_charget == _gf_FLMark) {
					_gf_status = true;
					return _gf_makebuffer;
				}
				//EndProcess
			}
		}

		continue;
	}

	_gf_status = false;
	return "Kernel Exception :   _get_fullLine";
}
//END GETFULL API

string _cmd_marks = "_";
string cmdbuffer;
string _api_result;
string _ckapi_scriptload(string load_Script) {
	if (!check_file_existence(load_Script)) {
		_p("Calcium Script Run failed");
		_p("return code :  nf01    FILE_NOT_FOUND");
		_p("Error :  File Not Found");
		return "nf01";
	}

	//Character Process ...
	while (true) {
		cmdbuffer = _get_fullLine(load_Script);
		if (_gf_status == false) {
			_p("Calcium Kernel Stop Running.  Return status code :  " + cmdbuffer);
			return "ok";
		}
		if (_gf_status == false) return "ok";

		//Code Analysis

		_api_result = _runcode_api(cmdbuffer);
		if (_api_result == "exit") {
			return "ok";
		}

		//NEXT
	}

	return "ok";
}

string oldcmd;
string _rc_varid, _rc_varinfo;
string _runcode_api(string command) {
	if (_gf_hsc == true) {
		command = HeadSpaceCleanA(command);
	}
	oldcmd = command;
	command = _Old_VSAPI_TransVar(command);
	//Command Process

	if (SizeRead(command, 4) == "_prt") {
		_p(PartReadA(command,"\"", "\"",1));
		return "ok";
	}

	if (SizeRead(command, 5) == "_exit") {
		return "exit";
	}

	if (SizeRead(command, 5) == "_var ") {
		if (checkChar(command, "=")) {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "=",1));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(command, "=", ";", 1));
		}
		else {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", ";", 1));
			_rc_varinfo = "{null}";
		}
		_varspaceadd(_rc_varid, _rc_varinfo);

		return "ok";
	}
	if (SizeRead(command, 12) == "_varapi.list") {
		_p("VarSpace List :  ");
		_p(VarSpace);
		_pn();
		return "ok";
	}
	if (SizeRead(command, 6) == "_free ") {
		_rc_varid = HeadSpaceCleanA(PartReadA(oldcmd, " ", ";", 1));
		_varspacedelete(_rc_varid);
		return "ok";
	}

	_p("Unknown command or not a var.  Line " + to_string(_gf_line) + "  INFO --> " + command);
	return "ok";
}