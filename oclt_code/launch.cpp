//Launch
// Main Cpp

//NET Loader

#include"Code/example.h"

//EDIT ON ANY_H



//Other Main
#include"Code/launchscreen.h"
//For Windows API
//Use #pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" )


using namespace std;

void printmsgoclt() {
    cleanConsole();
    _pn();
    _p("OpenCppLangTab Version :  " + $version_code_str + "  (" + $codename + ")");
    _p("OCLT Timestamp :   " + $buildtime);
    _p("Operating system :   " + _Run_SysKernel);
    _p("Run Command Argument :  " + native_argument);
    _p("File Path :  " + _$GetSelfFull);
    _pn();
    _p("Copyright FoxaXu ");
    _p($year_message);
    _p("All rights reserved.");
    _pause();
    return;

}

int main(int argc, char* argv[]) {
    
    if (__settings_displaylaunchscreen) {
        _LaunchScreen();
        sleepapi(__settings_displaylaunchscreen_time);
        cleanConsole();
    }
    else {

    }


    for (int readargc = 1, fileswitch = 0; readargc != argc; readargc++) {

        _argslonger++;

        readbuffer = argv[readargc];
        native_argument = native_argument + " " + _$quo + readbuffer + _$quo;
        if (readbuffer == "--oclt-version") {
            printmsgoclt();
            return 0;
        }

        if (readbuffer == "--license") {
            _soildwrite_open("license-oclt.txt");
            _soildwrite_write("Build By OpenCLT");
            _soildwrite_write($version_title + "   " + to_string($version_code));
            _soildwrite_write("OpenCLT " + $version_msg);
            _soildwrite_write("Code Name :   " + $codename);
            _soildwrite_write("    Copyright FoxaXu " + $year_message);
            _soildwrite_write(" Github :  " + $github_website);
            _soildwrite_close();

            _soildwrite_open("auther-oclt.txt");
            _soildwrite_write("Creator :  " + Program_Creater);
            _soildwrite_write("OpenCLT " + $version_msg);
            _soildwrite_write("Code Name :   " + $codename);
            _soildwrite_close();
            return 0;
        }

        argsApi(readbuffer);
    }

    if (argsSetExit == true) {
        return 0;
    }

    int return_code = _HeadMainLoad();

    return return_code;
}
