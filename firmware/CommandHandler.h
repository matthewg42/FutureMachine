#pragma once

#include <Arduino.h>
#include <CommandInterface.h>

class CommandHandlerClass : public CommandInterface 
{
public:
    void runCmd();

};

extern CommandHandlerClass CommandHandler;

