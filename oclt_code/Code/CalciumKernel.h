//Calcium Kernel Base

//Copyright FoxaXu 2024
// Based on OpenCppLangTab

#include"../shload.h"
#include"../Code/RCapi.h"

//VCODE
// 110(Software Version).1(General).1(Release Version).1(Debug/Preview/preRelease/Release  1 - 4)

//releaseVerKnd
const string _KV_rV_Debug = "1";
const string _KV_rV_Preview = "2";
const string _KV_rV_preRelease = "3";
const string _KV_rV_Release = "4";
const string _KV_rV_Stable = "5";

//Other Version
const string _KV_rV_Custom = "6";
const string _KV_rV_Embed = "7";
const string _KV_rV_Demo = "8";

//Main Char
string _kv_text_debug = "Debug";
string _kv_text_preview = "Preview";
string _kv_text_prerelease = "Prerelease";
string _kv_text_release = "Release";
string _kv_text_stable = "stable";

//OV
string _kv_text_custom = "Custom";
string _kv_text_embed = "Embed";
string _kv_text_demo = "Demo";
//rVK END

//RunID
string _KV_rV_Text;
string _CK_Runid = _get_random_s(100000, 999999);

string _KV_softwareVersion = "110"; //(Software Version)

string _KV_gen = "2";//(General)

string _KV_rv = "1";//(Release Version)

string _KV_releaseVer = _KV_rV_Preview;//(Debug/Preview/preRelease/Release  1 - 4)

string _mk = ".";

string _KernelVersion = _KV_softwareVersion + _mk + _KV_gen + _mk + _KV_rv + _mk + _KV_releaseVer;

//DEFINE

void _KernelVersion_LoadText(void) {
	_KV_rV_Text = "{Unknown KrV ;  " + _KV_releaseVer + " }";

	if (_KV_releaseVer == _KV_rV_Debug) {
		_KV_rV_Text = _kv_text_debug;
	}
	if (_KV_releaseVer == _KV_rV_Preview) {
		_KV_rV_Text = _kv_text_preview;
	}
	if (_KV_releaseVer == _KV_rV_preRelease) {
		_KV_rV_Text = _kv_text_prerelease;
	}
	if (_KV_releaseVer == _KV_rV_Release) {
		_KV_rV_Text = _kv_text_release;
	}
	if (_KV_releaseVer == _KV_rV_Stable) {
		_KV_rV_Text = _kv_text_stable;
	}

	//Other
	if (_KV_releaseVer == _KV_rV_Custom) {
		_KV_rV_Text = _kv_text_custom;
	}
	if (_KV_releaseVer == _KV_rV_Embed) {
		_KV_rV_Text = _kv_text_embed;
	}
	if (_KV_releaseVer == _KV_rV_Demo) {
		_KV_rV_Text = _kv_text_demo;
	}

	return;
}

//Define-Head
string _runcode_api(string command);
string PartReadA(string Info, string StartMark, string EndMark, int RPartSizeA);

//HeadSpaceClean .  Default = true
bool _gf_hsc = true;

//GetFULL API
const int _gf_line_maxallow = 128;
bool _gf_status;
int _gf_cg = 0;
int _gf_cgmax = 1;
int _gf_line = 1;
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

bool _CK_ShellMode = false;
string _cmd_marks = "_";
string cmdbuffer;
string _api_result;
string _global_scriptload;
bool _stop_exec_script = false;
string _ckapi_scriptload(string load_Script) {
	_global_scriptload = load_Script;
	if (!check_file_existence(load_Script)) {
		_p("Calcium Script Run failed");
		_p("return code :  nf01    FILE_NOT_FOUND");
		_p("Error :  File Not Found");
		return "nf01";
	}

	//Character Process ...
	_api_result = "scriptloadfailed";
	while (true) {
		_global_scriptload = load_Script;
		cmdbuffer = _get_fullLine(load_Script);
		if (_gf_status == false) {
			_p("Calcium Kernel Stop Running.  Return status code :  " + cmdbuffer);
			return "ok";
		}
		if (_gf_status == false) return "ok";

		//Code Analysis
		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}
		last_return = _api_result = _runcode_api(cmdbuffer);
		if (_api_result == "runid.exit") {
			return "ok";
		}
		if (_api_result == "runid.entershell") {
			return "runid.entershell";
		}

		if (_stop_exec_script == true) {
			return _api_result;
		}

		//NEXT
	}

	return _api_result;
}

string oldcmd;
string charCutA, charCutB, CharCutC, CharCutD;
string _rc_varid, _rc_varinfo;
int intCutA, intCutB, intCutC;
bool _debug_type_detected = false;
string _runcode_api(string command) {
	if (_gf_hsc == true) {
		command = HeadSpaceCleanA(command);
	}
	oldcmd = command;
	command = _Old_VSAPI_TransVar(command);
	if (_debug_type_detected == true) {
		_p("Detect command :   " + command);
		_p("Detect Resource   :   " + oldcmd);
	}
	//Command Process

	if (command == "") {
		if (_debug_type_detected == true) {
			_p("command is empty");
		}
		return"empty";
	}
	if (SizeRead(command,1) == ":") {
		if (_debug_type_detected == true) {
			_p("command is goto mark");
		}
		return"empty";
	}
	if (command == ";") {
		if (_debug_type_detected == true) {
			_p("command is empty with ;(EndMark)");
		}
		return"empty";
	}
	if (command == "1") {
		return "true";
	}
	if (command == "0") {
		return "false";
	}
	if (command == "true") {
		return "true";
	}
	if (command == "false") {
		return "false";
	}

	if (SizeRead(command, 1) == "\"") {
		if (charTotal(command, "\"") != 2) {
			return("Null.format(Quotation Mark not full) for -->  " + command);
		}
		return PartReadA(command, "\"", "\"", 1);
	}

	if (SizeRead(command, 4) == "_prt") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		_prts(charCutB);
		return "ok.print:<" + charCutB + ">";
	}

	if (SizeRead(command, 5) == "_cout") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		_p(charCutB);
		return "ok.print:<" + charCutB + ">";
	}

	if (SizeRead(command, 5) == "_exit") {
		return "runid.exit";
	}
	if (SizeRead(command, 7) == "_return") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		_stop_exec_script = true;
		return charCutB;
	}
	if (SizeRead(command, 7) == "_foxaxu") {
		_p("Thanks your support");
		_p("https://www.foxaxu.com/fwlink?linkid=calcium_kernel_surprise");
		return "ok";
	}
	if (SizeRead(command, 5) == "_var ") {
		if (checkChar(command, "=")) {
			//Detecd illegal char = 

			if (charTotal(command, "=") == 2) {
				_p("Detect illegal Character :   =");
				_p("Varspace :  Access is Denied");
				return "false";
			}

			_rc_varid = HeadSpaceCleanA(PartReadA(oldcmd, " ", "=",1));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(oldcmd, "=", ";", 1));
			_rc_varinfo = _runcode_api(_rc_varinfo);

			if (checkChar(_rc_varinfo, "=")) {
				_p("Detect illegal Character :   =");
				_p("Varspace :  Access is Denied");
				return "false";
			}

		}
		else {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", ";", 1));
			_rc_varinfo = "{null}";
		}
		_varspaceadd(_rc_varid, _rc_varinfo);

		return "ok";
	}
	if (SizeRead(command, 12) == "_varapi.list") {
		_p("VarSpace Size :  " + to_string(VarSpaceMax));
		_p("VarSpace List :  ");
		_p(VarSpace);
		_pn();
		return "ok";
	}
	if (SizeRead(command, 9) == "_pathlist") {
		_p("PluginPath =   " + _rcbind_pluginpath);
		_p("PluginScript = " + _rcbind_pluginscript);
		return "ok";
	}
	if (SizeRead(command, 6) == "_free ") {
		_rc_varid = HeadSpaceCleanA(PartReadA(oldcmd, " ", ";", 1));
		_varspacedelete(_rc_varid);
		return "ok";
	}
	if (SizeRead(command, 7) == "_system") {
		if (_rcset_syscmd == false) {
			_p("System Command is disabled on  " + buildshell);
			_p("Your administrator won't allow you to run this command");
			_p("Please use command :   _cfgedit EnableSystemCommand = true;");
			return "denied";
		}
		charCutA = HeadSpaceCleanA(PartReadA(oldcmd, "\"", "\"", 1));
		charCutA = _Old_VSAPI_TransVar(charCutA);
		_str_system(charCutA);
		return "ok";
	}
	if (SizeRead(command, 9) == "_cfgedit ") {
		if (_CK_ShellMode == false) {
			//ScriptMode
			if (_rcset_scriptedit == false) {
				_p("Your administrator won't allow you to run this command");
				_p("Please set AllowScriptEdit  == true");
				return "denied";
			}
		}
		if (_CK_ShellMode == true) {
			//ShellMode
			if (_rcset_shelledit == false) {
				_p("Your administrator won't allow you to run this command");
				_p("Please set AllowShellEdit  == true");
				return "denied";
			}
		}
		if (checkChar(command, "=")) {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "=", 1));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(command, "=", ";", 1));
			_write_sipcfg(buildshell,_rc_varid,_rc_varinfo);
			_p("Your settings is has been modified. use \"_reload\" to Reload all configs");
			return "ok";
		}
		else {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", ";", 1));
			_p("Config " + _rc_varid + " == " + _load_sipcfg(buildshell, _rc_varid));
			return "ok";
		}
		return "falseproblem";
	}
	if (SizeRead(command, 7) == "_reload") {
		if (!_RcApiLoadConfig()) {
			_p("Failed to Load RCapi.");
			_p("Config file is missing :  " + buildshell);
			_p("try to repair and try again.");
			_pause();
			return "false";
		}
		_p("_Rcapi Config is reload");
		return "ok";
	}
	if (SizeRead(command, 9) == "_getrunid") {
		return _CK_Runid;
	}
	if (SizeRead(command, 6) == "_pause") {
		_pause();
		return"ok";
	}
	if (SizeRead(command, 10) == "_textprint") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		if (!check_file_existenceA(charCutB)) {
			_p("file not found   " + charCutB);
			_p("Null._textprint()");
			return "nofile";
		}

		_textapi_typetext(charCutB);
		return "ok";
	}
	if (SizeRead(command, 6) == "_sleep") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		if (charCutA == "0") {
			_p("Error :  _sleep(0) is a Null Time");
			return "ok";
		}
		intCutA = atoi(charCutA.c_str());
		if (intCutA == 0) {
			_p("Error :  _sleep(" + charCutA + ") is not a Digital.");
			return "ok";
		}

		sleepapi(intCutA);
		return "ok";
	}
	if (SizeRead(command, 8) == "_execute") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";

		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		//_p("Execute Command :   " + _rc_varid + " " + _rc_varinfo);
		if (!check_file_existence(_rc_varid)) {
			_p("Execute Error :   FileNotFound");
			_p("Please check yor type");
			return "filenotfound";
		}
		intCutA = _system_autoRun(_rc_varid, _rc_varinfo);

		return to_string(intCutA);
	}
	if (SizeRead(command, 6) == "_goto ") {
		if (_CK_ShellMode == true) {
			_p("Calcium Kernel is running on Shell Mode");
			_p("Please use this command on script");
			return "false";
		}
		charCutA = PartReadA(oldcmd, " ", ";", 1);
		intCutA = FindCharLine(1, _global_scriptload, charCutA);
		if (intCutA == _gf_line) {
			intCutB = _gf_line;

			intCutB++;

			intCutA = FindCharLine(intCutB, _global_scriptload, charCutA);
		}
		if (intCutA == -4) {
			_p("_goto Command Error");
			_p("Cannot Find Head :   ---> " + charCutA);
			_p("Execution termination");
			return "runid.exit";
		}

		if (_debug_type_detected == true) {
			_p("Find char mark in " + to_string(intCutA));
		}

		intCutA++;

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = intCutA;
		_gf_charget = "";

		return "runid.line_reset";
	}
	if (SizeRead(command, 6) == "_clear") {
		cleanConsole();
		return "ok";
	}
	if (SizeRead(command, 12) == "_kernelcrash") {
		string abcapi = NULL;
		_p(abcapi);
	}
	if (SizeRead(command, 10) == "_runscript") {

		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ">", 1));
		charCutB = _runcode_api(charCutA);

		if (!check_file_existenceA(charCutB)) {
			charCutB = _rcbind_pluginscript + "/" + charCutB;
			if (!check_file_existenceA(charCutB)) {
				_p("_runscript Error:  File not Exist");
				_p(charCutB);
				return "filenotfound";
			}
		}

		//Backup old GFapi data;

		int _old$_gf_cg = _gf_cg;
		int _old$_gf_cgmax = _gf_cgmax;
		int _old$_gf_line = _gf_line;

		//Create New Space

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_gf_charget = "";

		//Run

		CharCutC = _ckapi_scriptload(charCutB);

		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}

		//Recovery old GFapi Data;
		_gf_cg = _old$_gf_cg;
		_gf_cgmax = _old$_gf_cgmax;
		_gf_line = _old$_gf_line;
		_gf_charget = "";

		return CharCutC;
	}
	if (SizeRead(command, 8) == "_compare") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";

		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));

		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		//_p("1 = " + _rc_varid);
		//_p("2 = " + _rc_varinfo);

		if (_rc_varid == _rc_varinfo) {
			return "true";
		}
		else {
			return "false";
		}

		return "FAIL";
	}
	if (SizeRead(command, 3) == "_if") {

		//_p("LaoDeng");
		CharCutD = "(" + PartRead(oldcmd, "(", "|", true);

		charCutA = _Old_VSAPI_TransVar(PartRead(CharCutD, "(", ")",true));

		//_p("Ready to XinDeng");

		charCutB = _runcode_api(charCutA);

		//_p("XinDeng");

		if (charCutB == "true") {
			CharCutC = _Old_VSAPI_TransVar(PartRead(command, "|", "$FROMEND$",true));

			CharCutD = _runcode_api(CharCutC);

			return CharCutD;
		}
		if (charCutB == "false") {
			return "notrue";
		}

		_p(" $$ _if command Error");
		_p(" $$ Command return a null result not a true or false");
		return "NullReturn";
	}
	if (SizeRead(command, 8) == "_getline") {
		return _getline_type();
	}

	//Debug
	if (SizeRead(command, 12) == "_detect.mode") {
		if (_debug_type_detected == true) {
			_p("Detect Mode is Disabled");
			_debug_type_detected = false;
			return "ok";
		}
		if (_debug_type_detected == false) {
			_p("Detect Mode is Enabled");
			_debug_type_detected = true;
			return "ok";
		}

		return " BadEffect";
	}
	if (SizeRead(command, 13) == "_get.lastcode") {
		_p("Last Return is :   <" + last_return + ">");
		return "ok";
	}
	if (SizeRead(command, 11) == "_entershell") {
		return"runid.entershell";
	}
	if (SizeRead(command, 7) == "_getrow") {
		return to_string(_gf_line);
	}

	//calculator
	if (SizeRead(command, 7) == "_calc.+") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = intCutA + intCutB;

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_calc.-") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = intCutA - intCutB;

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_calc.*") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = intCutA * intCutB;

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_calc./") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		if (_rc_varinfo == "0") {
			_p("Calcium calculator Warning");
			_p("command :    _calc./    ");
			_p("The divisor cannot be 0");
			return "0";
		}

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = intCutA / intCutB;

		charCutA = to_string(intCutC);
		return charCutA;
	}

	//Other
	if (SizeRead(command, 8) == "_getrand") {
		charCutA = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(charCutA, ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = _get_random(intCutA, intCutB);

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_getkernel") {
		return InsideVersion;
	}

	_p(" $$$ Unknown command or not a var. File :  <" + _global_scriptload + ">  Line " + to_string(_gf_line) + "  INFO --> " + command + "    (Resource -->  " + oldcmd +  ")");
	return "unknown.command()";
}