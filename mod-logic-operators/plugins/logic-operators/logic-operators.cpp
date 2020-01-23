#include "logic-operators.hpp"
#include <iostream>

START_NAMESPACE_DISTRHO

#include <iostream>

// -----------------------------------------------------------------------

LogicOperators::LogicOperators()
    : Plugin(paramCount, 1, 0) // 1 program, 0 states
{
    loadProgram(0);

    sampleRate = (float)getSampleRate();

    logicOperators = new Operator*[NUM_OPERATORS];

    logicOperators[0] = new AND_Operator();
    logicOperators[1] = new NAND_Operator();
    logicOperators[2] = new INV_Operator();
    logicOperators[3] = new OR_Operator();
    logicOperators[4] = new NOR_Operator();
    logicOperators[5] = new XOR_Operator();
    logicOperators[6] = new XNOR_Operator();

    selectOperator = 0.0;
    paramHigh = 5.0;
    paramLow = 0.0;
    paramEqualOrHigher = 1.0;

    logicOut = 0.0;

    reset();
}

LogicOperators::~LogicOperators()
{
}

// -----------------------------------------------------------------------
// Init

void LogicOperators::initParameter(uint32_t index, Parameter& parameter)
{
    switch (index)
    {
    case paramSelectOperator:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Logic Operator";
        parameter.symbol     = "LogicOperator";
        parameter.unit       = "";
        parameter.ranges.def = 0.0f;
        parameter.ranges.min = 0.0f;
        parameter.ranges.max = 6.f;
        break;
    case paramSetHigh:
        parameter.hints      = kParameterIsAutomable;
        parameter.name       = "Logic High";
        parameter.symbol     = "LogicHigh";
        parameter.unit       = "";
        parameter.ranges.def = 1.0f;
        parameter.ranges.min = 0.f;
        parameter.ranges.max = 1.f;
        break;
    }
}

void LogicOperators::initProgramName(uint32_t index, String& programName)
{
    if (index != 0)
        return;

    programName = "Default";
}

// -----------------------------------------------------------------------
// Internal data

float LogicOperators::getParameterValue(uint32_t index) const
{
    switch (index)
    {
    case paramSelectOperator:
        return selectOperator;
    case paramSetHigh:
        return paramHigh;
    }
}

void LogicOperators::setParameterValue(uint32_t index, float value)
{
    switch (index)
    {
    case paramSelectOperator:
        selectOperator = value;
        break;
    case paramSetHigh:
        paramHigh = value;
        break;
    }
}

void LogicOperators::loadProgram(uint32_t index)
{
}

void LogicOperators::reset()
{
}

// -----------------------------------------------------------------------
// Process

void LogicOperators::activate()
{
}

void LogicOperators::deactivate()
{
}



void LogicOperators::run(const float** inputs, float** outputs, uint32_t frames)
{
    const float* input1 = inputs[0];
    const float* input2 = inputs[1];
    float* output = outputs[0];

    for (uint32_t f = 0; f < frames; ++f)
    {
        float a = input1[f];
        float b = input2[f];

        a = (a >= paramHigh) ? 5.0 : 0.0;
        b = (b >= paramHigh) ? 5.0 : 0.0;

        logicOut = logicOperators[(int)selectOperator]->process(a, b);

        output[f] = logicOut;
    }
}



// -----------------------------------------------------------------------

Plugin* createPlugin()
{
    return new LogicOperators();
}

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO
