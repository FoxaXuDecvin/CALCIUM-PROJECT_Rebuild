//Environment Variable
//Env.H

#include"../SourceHeader/include.h"

//Here
string runscript = "{null}";
string script_args = "{null}";
string o_info = "{null}";

bool _setnextargs_runscript = false;
bool _setnextargs_addargs = false;
bool _setnextargs_addo = false;

bool _debugMode = false;


//RUNMODE STRING

const string _runmode_null = "0000";
const string _runmode_runscript = "r1md";
const string _runmode_typehelp = "r2hp";
const string _runmode_autoexit = "r0cl";
const string _runmode_openshell = "r3se";
const string _runmode_listversion = "r4ve";
const string _runmode_optimi = "r5op";
const string _runmode_cstpmake = "r661";
const string _runmode_cstpunpack = "r662";

const string _str_true = "true";
const string _str_false = "false";

string _runmode = _runmode_null;

bool _anticrash_services = false;

string InsideVersion = "C201";

string last_return;

//Here
bool _kernel_activate = false;
int _KV_relver$int;
bool _language_mode = false;

string kernelcmdVid;
string kernelenvVid;
string kernelSecureVid;
string gethookVid;
string isGetVid;
string sysexecVid;
string ThirdExecVid;

//RCapi

string _CTitle;
string _KV_rV_Text;
string _global_scriptload;
int _gf_cg = 0;
int _gf_cgmax = 1;
int _gf_line = 1;

string nt_sipcfg_open;