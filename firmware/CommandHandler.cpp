#include <MutilaDebug.h>
#include "CommandHandler.h"
#include "Settings.h"
#include "RecordIndicator.h"
#include "Config.h"

void CommandHandlerClass::runCmd()
{
    uint8_t i;
    String cmd;
    for (i = 0; i < _maxLen && _buf[i] != ' ' && _buf[i] != '\0'; i++) {
        cmd += _buf[i];
    }
    while (_buf[i] == ' ') { ++i; }
    
	// cmd is the first word of the command
    if (cmd == "help") {
        _stream->println(F("\n# Commands:"));
        _stream->println(F("# help       - this cruft"));
        _stream->println(F("# settings   - print current settings"));
        _stream->println(F("# reset      - reset default settings"));
        _stream->println(F("# input [ms] - set input update interval in milliseconds"));
        _stream->println(F("# rec [mode] - set the mode of the recording indicator (on, off, [quick|slow]flash)"));
    } else if (cmd == "settings") {
		printSettings();
    } else if (cmd == "reset") {
		resetSettings();
    } else if (cmd == "input") {
		String arg(_buf + i);
		bool ok = InputDisplayPeriodMs.set(arg.toInt());
		if (!ok) {
			_stream->print(F("# ERROR: invalid argument to input command: '"));
			_stream->print(arg);
			_stream->println('\'');
		} else {
			InputDisplayPeriodMs.save();
			_stream->println("# OK");
		}
    } else if (cmd == "rec") {
		String arg(_buf + i);
		if (arg == "on") {
			RecordIndicator.setMode(Heartbeat::On);
		} else if (arg == "off") {
			RecordIndicator.setMode(Heartbeat::Off);
		} else if (arg == "flash") {
			RecordIndicator.setMode(Heartbeat::Normal);
		} else if (arg == "slowflash") {
			RecordIndicator.setCustomMode(750, 500);
		} else if (arg == "quickflash") {
			RecordIndicator.setCustomMode(50, 50);
		} else {
			_stream->print(F("# ERROR: invalid argument to rec command: '"));
			_stream->print(arg);
			_stream->println('\'');
		}
    } else {
        _stream->print(F("# ERROR: invalid command: '"));
        _stream->print(_buf);
        _stream->println(F("', try 'help'"));
    }
}

CommandHandlerClass CommandHandler;

