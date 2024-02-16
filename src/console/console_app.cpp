#include "console_app.h"
#include "src/console/flag.h"
#include "src/utils/global_variables.h"
#include <iostream>
#include <qfileinfo.h>
#include <src/utils/text_utils.h>
#include <vector>

const Flag HELP_FLAG = Flag("-h", "--help");
const Flag VERSION_FLAG = Flag("-v", "--version");
const Flag INPUT_FLAG = Flag("-i", "--input");
const Flag OUTPUT_FLAG = Flag("-o", "--output");
const Flag SUBCIRCUIT_FLAG = Flag("-s", "--subcircuit");
const Flag WITHOUT_FILE_FLAG = Flag("-wf", "--without-file");
const Flag WITHOUT_CONSOLE_FLAG = Flag("-wc", "--without-console");
const Flag JSIM_FLAG = Flag("-j", "--jsim");

ConsoleApplication::ConsoleApplication(int argc, char **argv)
    : argc(argc)
    , argv(argv)
{}

std::string get_option(const std::vector<std::string> &args, const Flag flag)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == flag.getFlag() || *it == flag.getAlias()) {
            if (it + 1 != end) {
                return *(it + 1);
            }
        }
    }
    return "";
}

bool has_option(const std::vector<std::string> &args, const Flag flag)
{
    for (auto it = args.begin(), end = args.end(); it != end; ++it) {
        if (*it == flag.getFlag() || *it == flag.getAlias()) {
            return true;
        }
    }
    return false;
}

ConversionParams getConversionParams(std::vector<std::string> args) {
    bool subcircuitStatus = has_option(args, SUBCIRCUIT_FLAG);
    QString subcircuitName = QString::fromStdString(get_option(args, SUBCIRCUIT_FLAG));
    bool fileOutput = !has_option(args, WITHOUT_FILE_FLAG);
    bool consoleOutput = !has_option(args, WITHOUT_CONSOLE_FLAG);
    int converterVersion = has_option(args, JSIM_FLAG) ? GlobalVariables::SIMULATOR_VERSION_JSIM
                                                       : GlobalVariables::SIMULATOR_VERSION_JOSIM;
    return ConversionParams(subcircuitStatus,
                            subcircuitName,
                            fileOutput,
                            consoleOutput,
                            converterVersion);
}

int ConsoleApplication::exec()
{
    const std::vector<std::string> args(argv + 1, argv + argc);
    if (argc > 16) {
        throw std::runtime_error("Too many input parameters!");
    }
    if (has_option(args, HELP_FLAG)) {
        QString help = FileManager::loadFile("settings/help.txt");
        std::cout << help.toStdString() << std::endl;
        return 0;
    }
    if (has_option(args, VERSION_FLAG)) {
        std::cout << GlobalVariables::VERSION << std::endl;
        return 0;
    }
    bool hasInput = has_option(args, INPUT_FLAG);
    bool hasOutput = has_option(args, OUTPUT_FLAG);
    if (!hasInput || !hasOutput) {
        throw std::runtime_error("Input and output files must be provided!");
    }

    QString inputFileName = QString::fromStdString(get_option(args, INPUT_FLAG));
    QString outputFileName = QString::fromStdString(get_option(args, OUTPUT_FLAG));
    QString result;
    if (QFileInfo(inputFileName).suffix() == "lp") {
        QString input = FileManager::loadFile(inputFileName);
        ConversionParams conversionParams = getConversionParams(args);
        result = appController.convertToSpice(input, conversionParams);
    }
    if (QFileInfo(inputFileName).suffix() == "cir" && QFileInfo(outputFileName).suffix() == "lp") {
        QString newSpice = FileManager::loadFile(inputFileName);
        QString oldLibre = FileManager::loadFile(outputFileName);
        result = appController.updateLibre(oldLibre, newSpice);
    }
    result = TextUtils::convertHtmlToPlain(result);
    bool fileIsSaved = FileManager::save(outputFileName, result);
    if (!fileIsSaved) {
        std::cout << "Cannot save the output file";
        return 1;
    }
    std::cout << "Converted successfully!";
    return 0;
}
