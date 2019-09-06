#include <MutilaDebug.h>
#include "CommandHandler.h"
#include "Settings.h"
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
        _stream->println(F("# Commands:"));
        _stream->println(F("# help       - this cruft"));
        _stream->println(F("# settings   - print current settings"));
        _stream->println(F("# reset      - reset default settings"));
        _stream->println(F("# input [ms] - set input update interval in milliseconds"));
    } else if (cmd == "settings") {
		printSettings();
    } else if (cmd == "reset") {
		resetSettings();
    } else if (cmd == "input") {
        _stream->print(F("# Setting input update to: '"));
		String arg(_buf + i);
        _stream->print(arg);
		bool ok = InputDisplayPeriodMs.set(arg.toInt());
		if (!ok) {
			_stream->print(F("# ERROR: invalid argument to input command: '"));
			_stream->print(arg);
			_stream->println('\'');
		} else {
			InputDisplayPeriodMs.save();
			_stream->println("# OK");
		}
    } else {
        _stream->print(F("# ERROR: invalid command: '"));
        _stream->print(_buf);
        _stream->println(F("', try 'help'"));
    }
}

CommandHandlerClass CommandHandler;

