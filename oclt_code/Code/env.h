//Environment Variable
//Env.H

#include"../SourceHeader/include.h"

//Here
string runscript = "{null}";
string script_args = "{null}";

bool _setnextargs_runscript = false;
bool _setnextargs_addargs = false;

bool _debugMode = false;


//RUNMODE STRING

const string _runmode_null = "0000";
const string _runmode_runscript = "r1md";
const string _runmode_typehelp = "r2hp";
const string _runmode_autoexit = "r0cl";
const string _runmode_openshell = "r3se";
const string _runmode_listversion = "r4ve";
const string _runmode_optimi = "r5op";

string _runmode = _runmode_null;

bool _anticrash_services = false;

string InsideVersion = "1000";

string last_return;

//Here
