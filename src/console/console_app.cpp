#include "console_app.h"
#include "src/console/flag.h"
#include "src/utils/global_variables.h"
#include <iostream>
#include <vector>

Q_GLOBAL_STATIC(Flag, HELP_FLAG, Flag("-h", "--help"));
Q_GLOBAL_STATIC(Flag, INPUT_FLAG, Flag("-i", "--input"));
Q_GLOBAL_STATIC(Flag, OUTPUT_FLAG, Flag("-o", "--output"));
Q_GLOBAL_STATIC(Flag, SUBCIRCUIT_FLAG, Flag("-s", "--subcircuit"));
Q_GLOBAL_STATIC(Flag, WITHOUT_FILE_FLAG, Flag("-wf", "--without-file"));
Q_GLOBAL_STATIC(Flag, WITHOUT_CONSOLE_FLAG, Flag("-wc", "--without-console"));
Q_GLOBAL_STATIC(Flag, JSIM_FLAG, Flag("-j", "--jsim"));

ConsoleApplication::ConsoleApplication(int argc, char **argv)
    : argc(argc)
    , argv(argv)
{}

ConsoleApplication::~ConsoleApplication() {}

std::string get_option(const std::vector<std::string> &args, const Flag *flag)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == flag->getFlag() || *it == flag->getAlias()) {
            if (it + 1 != end) {
                return *(it + 1);
            }
        }
    }
    return "";
}

bool has_option(const std::vector<std::string> &args, const Flag *flag)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == flag->getFlag() || *it == flag->getAlias()) {
            return true;
        }
    }
    return false;
}

int ConsoleApplication::exec()
{
    const std::vector<std::string> args(argv + 1, argv + argc);
    if (argc > 16) {
        throw std::runtime_error("Too many input parameters!");
    }
    if (has_option(args, HELP_FLAG)) {
        std::cout << "HELP!!!" << std::endl;
        return 0;
    }
    bool hasInput = has_option(args, INPUT_FLAG);
    bool hasOutput = has_option(args, OUTPUT_FLAG);
    if (!hasInput || !hasOutput) {
        throw std::runtime_error("Input and output files must be provided!");
    }
    QString inputFileName = QString::fromStdString(get_option(args, INPUT_FLAG));
    QString outputFileName = QString::fromStdString(get_option(args, OUTPUT_FLAG));
    QString input = fileManager.loadFile(inputFileName);
    bool subcircuitStatus = has_option(args, SUBCIRCUIT_FLAG);
    QString subcircuitName = QString::fromStdString(get_option(args, SUBCIRCUIT_FLAG));
    bool fileOutput = !has_option(args, WITHOUT_FILE_FLAG);
    bool consoleOutput = !has_option(args, WITHOUT_CONSOLE_FLAG);
    int converterVersion = has_option(args, JSIM_FLAG) ? SIMULATOR_VERSION_JSIM
                                                       : SIMULATOR_VERSION_JOSIM;
    ConversionParams conversionParams(subcircuitStatus,
                                      subcircuitName,
                                      fileOutput,
                                      consoleOutput,
                                      converterVersion);
    QString spiceNetlist = appHeader.getHeader(conversionParams, inputFileName) +
                           appController.convertToSpice(input, conversionParams);
    fileManager.save(outputFileName, spiceNetlist);
    std::cout << "Converted successfully!";
    return 0;
}
