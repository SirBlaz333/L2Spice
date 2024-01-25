#include "consoleapplication.h"
#include <iostream>
#include <vector>

ConsoleApplication::ConsoleApplication(int argc, char **argv)
    : argc(argc)
    , argv(argv)
{}

ConsoleApplication::~ConsoleApplication() {}

std::string get_option(const std::vector<std::string> &args,
                       const std::string &option_name,
                       const std::string &option_fullname)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name || *it == option_fullname) {
            if (it + 1 != end) {
                return *(it + 1);
            }
        }
    }
    return "";
}

bool has_option(const std::vector<std::string> &args,
                const std::string &option_name,
                const std::string &option_fullname)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == option_name || *it == option_fullname) {
            return true;
        }
    }
    return false;
}

int ConsoleApplication::exec()
{
    const std::vector<std::string> args(argv + 1, argv + argc);
    if (argc > 10) {
        throw std::runtime_error("Too many input parameters!");
    }
    if (has_option(args, "-h", "--help")) {
        std::cout << "HELP!!!" << std::endl;
        return 0;
    }
    bool hasInput = has_option(args, "-i", "--input");
    bool hasOutput = has_option(args, "-o", "--output");
    if (!hasInput || !hasOutput) {
        throw std::runtime_error("Input and output files must be provided!");
    }
    QString inputFileName = QString::fromStdString(get_option(args, "-i", "--input"));
    QString outputFileName = QString::fromStdString(get_option(args, "-o", "--output"));
    QString input = fileManager.loadFile(inputFileName);
    bool subcircuitStatus = has_option(args, "-s", "--subcircuit");
    QString subcircuitName = QString::fromStdString(get_option(args, "-s", "--subcircuit"));
    bool fileOutput = has_option(args, "-wf", "--without-file");
    bool consoleOutput = has_option(args, "-wc", "--without-console");
    int converterVersion = has_option(args, "-j", "--jsim") ? 1 : 0;
    ConversionParams conversionParams(subcircuitStatus,
                                      subcircuitName,
                                      fileOutput,
                                      consoleOutput,
                                      converterVersion);
    ConversionData state = appController.convertToSpice(input, conversionParams);
    fileManager.save(outputFileName, state.getSpiceNetlist());
    std::cout << "Converted successfully!";
    return 0;
}
