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


string _ckapi_scriptload(string load_Script) {
	if (!check_file_existence(load_Script)) {
		_p("Calcium Script Run failed");
		_p("return code :  nf01    FILE_NOT_FOUND");
		_p("Error :  File Not Found");
		return "nf01";
	}

	//Character Process ...
}