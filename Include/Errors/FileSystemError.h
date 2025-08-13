#pragma once

#include <sstream>

#include "Errors/ErrorType.h"

namespace Errors {

/// Helpful wrapper around filesystem errors
/// The idea is to call runtime_error constructor using stream outputted from stringstream which contains error message
class FileSystemError : public std::runtime_error {
	std::string init(const std::string& path, TYPE type) {
		std::stringstream stream;

		if(type == TYPE::FAILED_TO_FIND) {
			stream << "Failed to find " << path << " file. Please check whether the file exists.";
		}

		return stream.str();
	}

public:
	FileSystemError(const std::string path, TYPE type) : std::runtime_error(init(path,type)) {}
};

};
