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

string _KV_gen = "4";//(General)

string _KV_rv = "2";//(Release Version)

string _KV_releaseVer = _KV_rV_preRelease;//(Debug/Preview/preRelease/Release  1 - 4)

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
const int _gf_line_maxallow = 512;
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
string _ckapi_scriptload(string load_Script,string Sargs) {

	_global_scriptload = load_Script;
	script_args = Sargs;
	_$logfile = _rcbind_logrec + "/" + _Char_Filter_EndFileName(load_Script) + "_LogRec.log";
	if (check_file_existence(_$logfile))_fileapi_del(_$logfile);
	if (!check_file_existence(load_Script)) {
		_pv("_$lang.runfail");
		_pv("Error :  _$lang.filenotfound");
		return "nf01";
	}

	//Character Process ...
	_api_result = "scriptloadfailed";

	_logrec_write("[Start] PreCheck Script Run Environment");
	_logrec_write("[Log] Log file is Bind :  " + _$logfile);

	if (!check_file_existence(_$logfile)) {
		_pv("_$lang.logfail " + _$logfile);
	}

	while (true) {
		_logrec_write("[Notice]Start to Execute script :  " + load_Script);
		_global_scriptload = load_Script;
		_logrec_write("[Exec]Complete Read Script");
		cmdbuffer = _get_fullLine(load_Script);
		_logrec_write("[Exec]Get Full Command :  -->  " + cmdbuffer);
		if (_gf_status == false) {
			_pv("_$lang.stoprun.  Return status code :  " + cmdbuffer + "  . Args :  " + _global_scriptload + "   Line :  " + to_string(_gf_line) + " + " + to_string(_gf_cg));
			_logrec_write("[ERROR]Kernel stop Running");
			return "ok";
		}
		if (_gf_status == false) return "ok";

		//Code Analysis
		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}
		_logrec_write("-start Running -- <Line " + to_string(_gf_line) + " /File " + _global_scriptload + "> -----------------------------------------");
		last_return = _api_result = _runcode_api(cmdbuffer);
		_logrec_write("Command Execute End, Result -->  " +_api_result);
		_logrec_write("-end -----------------------------------------------------");
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

string varbufA;
string charCutA, charCutB, CharCutC, CharCutD;
string chartempA, chartempB, chartempC, chartempD;
string _rc_varid, _rc_varinfo;
int intCutA, intCutB, intCutC;
int dbA, dbB, dbC, dbD;
bool _debug_type_detected = false;
bool _var_auto_void = false;
string _runcode_api(string command) {
	if (_gf_hsc == true) {
		command = HeadSpaceCleanA(command);
	}
	string oldcmd = command;
	command = _Old_VSAPI_TransVar(command);
	_logrec_write("[INFO] _var api :   --> " + oldcmd + " | to |  " + command);
	if (oldcmd == command) {
		_var_auto_void = false;
	}
	else {
		_var_auto_void = true;
	}
	if (_debug_type_detected == true) {
		_p("Detect command :   " + command);
		_p("Detect Resource   :   " + oldcmd);
	}
	//Command Process

	if (atoi(command.c_str()) != 0) {
		return command;
	}
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
		charCutA = PartReadA(command, "\"", "\"", 1);
		_logrec_write("[INFO] Return char" + _$quo + charCutA + _$quo);
		return charCutA;
	}

	if (SizeRead(command, 4) == "_prt") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);
		
		_logrec_write("[Exec] PRINT :  " + _$quo + charCutB + _$quo);
		
		_prts(charCutB);
		return "ok.print:<" + charCutB + ">";
	}

	if (SizeRead(command, 5) == "_cout") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		_logrec_write("[Output Exec] Command :  -->  " + charCutA);
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] COUT :  " + _$quo + charCutB + _$quo);
		_p(charCutB);
		return "ok.print:<" + charCutB + ">";
	}

	if (SizeRead(command, 5) == "_exit") {
		_logrec_write("[Shutdown] Execute _Exit");
		return "runid.exit";
	}
	if (SizeRead(command, 7) == "_return") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		_logrec_write("_Exec Return Data :  " + charCutB);
		_stop_exec_script = true;
		return charCutB;
	}
	if (SizeRead(command, 7) == "_foxaxu") {
		_logrec_write("[Exec] owo  pwp wow");
		_pv("_$lang.foxaxu.t1");
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
		_logrec_write("[Exec] Create VarSpace");
		_varspaceadd(_rc_varid, _rc_varinfo);
		_logrec_write("[INFO]  varid --> " + _rc_varid + "   varinfo --> " + _rc_varinfo);

		return "ok";
	}
	if (SizeRead(command, 6) == "_free ") {
		_rc_varid = HeadSpaceCleanA(PartReadA(oldcmd, " ", ";", 1));
		_varspacedelete(_rc_varid);
		_logrec_write("VarSpace Delete  --> " + _rc_varid);

		return "ok";
	}
	if (SizeRead(command, 7) == "_system") {
		if (_rcset_syscmd == false) {
			_pv("_$lang.sys.t1  " + buildshell);
			_pv("_$lang.sys.t2");
			_pv("_$lang.sys.t3 :   _cfgedit EnableSystemCommand = true;");
			_logrec_write("[WARNING] System Command Disabled");

			return "denied";
		}
		charCutA = HeadSpaceCleanA(PartReadA(oldcmd, "\"", "\"", 1));
		charCutA = _Old_VSAPI_TransVar(charCutA);
		_str_system(charCutA);
		_logrec_write("[Exec] Run System Command   --> " + charCutA);

		return "ok";
	}
	if (SizeRead(command, 9) == "_cfgedit ") {
		_logrec_write("[KernelManager] CFGEDIT");

		if (_CK_ShellMode == false) {
			//ScriptMode
			if (_rcset_scriptedit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowScriptEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		if (_CK_ShellMode == true) {
			//ShellMode
			if (_rcset_shelledit == false) {
				_pv("_$lang.sys.t1  " + buildshell);
				_p("Please set AllowShellEdit  == true");
				_logrec_write("[KernelManager][WARNING] Access is Denied");
				return "denied";
			}
		}
		if (checkChar(command, "=")) {
			_rc_varid = HeadSpaceCleanA(PartReadA(command, " ", "=", 1));
			_rc_varinfo = HeadSpaceCleanA(PartReadA(command, "=", ";", 1));
			_write_sipcfg(buildshell,_rc_varid,_rc_varinfo);
			_logrec_write("[KernelManager] Set :  " + _rc_varid + " = " + _rc_varinfo);
			_pv("_$lang.cfgedit.r");
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
		_logrec_write("[KernelManager] RCapi Reload");
		if (!_RcApiLoadConfig()) {
			_p("Failed to Load RCapi.");
			_p("Config file is missing :  " + buildshell);
			_p("try to repair and try again.");
			_pause();
			return "false";
		}
		_pv("_$lang.reload");
		return "ok";
	}
	if (SizeRead(command, 9) == "_getrunid") {
		return _CK_Runid;
	}
	if (SizeRead(command, 6) == "_pause") {
		$_pause = _Old_VSAPI_TransVar("_$lang.pause");
		_pause();
		return"ok";
	}
	if (SizeRead(command, 10) == "_textprint") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		charCutB = _runcode_api(charCutA);

		_logrec_write("[Exec] Print Text File   " + charCutB);

		if (!check_file_existenceA(charCutB)) {
			_pv("_$lang.filenotfound   " + charCutB);
			_p("Null._textprint()");
			return "nofile";
		}

		_textapi_typetext(charCutB);
		return "ok";
	}
	if (SizeRead(command, 6) == "_sleep") {
		charCutA = _Old_VSAPI_TransVar(PartReadA(oldcmd, "(", ")", 1));
		if (charCutA == "0") {
			_pv("Error :  _sleep(0) _$lang.notNum");
			return "ok";
		}
		intCutA = atoi(charCutA.c_str());
		if (intCutA == 0) {
			_pv("Error :  _sleep(" + charCutA + ") _$lang.notNum.");
			return "ok";
		}

		_logrec_write("_Program Sleep " + charCutA);
		sleepapi(intCutA);
		return "ok";
	}
	if (SizeRead(command, 8) == "_execute") {
		string tempbase = "(" + PartReadA(oldcmd, "(", ")", 1) + ")";

		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA(tempbase, "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA(tempbase, ",", ")", 1)));

		//_p("Execute Command :   " + _rc_varid + " " + _rc_varinfo);
		if (!check_file_existence(_rc_varid)) {
			_pv("Execute Error :   _$lang.filenotfound");
			return "filenotfound";
		}
		_logrec_write("[Exec] Run Application :   " + _rc_varid +"  Argument :  " + _rc_varinfo);
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

		charCutB = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, "<", ",", 1)));
		chartempA = _runcode_api(_Old_VSAPI_TransVar(PartReadA(oldcmd, ",", ">", 1)));

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
		string _old$_args = script_args;

		//Create New Space

		_gf_cg = 0;
		_gf_cgmax = 1;
		_gf_line = 1;
		_gf_charget = "";

		//Run

		CharCutC = _ckapi_scriptload(charCutB,chartempA);

		if (_stop_exec_script == true) {
			_stop_exec_script = false;
		}

		//Recovery old GFapi Data;
		_gf_cg = _old$_gf_cg;
		_gf_cgmax = _old$_gf_cgmax;
		_gf_line = _old$_gf_line;
		_gf_charget = "";
		script_args = _old$_args;

		return CharCutC;
	}
	if (SizeRead(command, 8) == "_compare") {

		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));

		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

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

		_pv("_$lang.if.err.t1");
		_pv("_$lang.if.err.t2");
		return "NullReturn";
	}
	if (SizeRead(command, 8) == "_getline") {
		return _getline_type();
	}
	if (SizeRead(command, 8) == "_getargs") {
		return script_args;
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
	if (SizeRead(command, 12) == "_varapi.list") {
		_logrec_write("[Debug] List VarSpace");

		_p("VarSpace Size :  " + to_string(VarSpaceMax));
		_p("VarSpace List :  ");
		_p(VarSpace);
		_pn();
		return "ok";
	}
	if (SizeRead(command, 9) == "_pathlist") {
		_logrec_write("[Debug] List Path");

		_p("PluginPath =   " + _rcbind_pluginpath);
		_p("PluginScript = " + _rcbind_pluginscript);
		return "ok";
	}

	//calculator
	if (SizeRead(command, 2) == "_+") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function +");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA + dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_-") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function -");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA - dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_*") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function *");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		dbC = dbA * dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}
	if (SizeRead(command, 2) == "_/") {
		string tempbase = "(" + PartRead(oldcmd, "(", ")", true) + ")";
		_logrec_write("Calculator Function /");
		_logrec_write("full line data:  -->   " + tempbase);

		string calc_A = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, "(", ",", false)));
		_logrec_write("Get Part A :   " + calc_A);
		string calc_B = _runcode_api(_Old_VSAPI_TransVar(PartRead(tempbase, ",", ")", true)));
		_logrec_write("Get Part B :   " + calc_B);

		dbA = atoi(calc_A.c_str());
		dbB = atoi(calc_B.c_str());

		if (dbB == 0) {
			_pv("_$lang.calc.zero");
			return "0";
		}

		dbC = dbA / dbB;

		charCutA = to_string(dbC);
		_logrec_write("return result :  _" + charCutA);
		return charCutA;
	}

	//Other
	if (SizeRead(command, 8) == "_getrand") {
		_rc_varid = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", "(", ",", 1)));
		_rc_varinfo = _runcode_api(_Old_VSAPI_TransVar(PartReadA("(" + PartReadA(oldcmd, "(", ")", 1) + ")", ",", ")", 1)));

		intCutA = atoi(_rc_varid.c_str());
		intCutB = atoi(_rc_varinfo.c_str());

		intCutC = _get_random(intCutA, intCutB);

		charCutA = to_string(intCutC);
		return charCutA;
	}
	if (SizeRead(command, 7) == "_getkernel") {
		return InsideVersion;
	}

	_logrec_write("[ERROR]Unknown COMMAND");
	_pv("_$lang.nullcmd   :  <" + _global_scriptload + ">  Line " + to_string(_gf_line) + "  INFO --> " + command + "    (Resource -->  " + oldcmd +  ")");
	return "unknown.command(" + command + ")";
}