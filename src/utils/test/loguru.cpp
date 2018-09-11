// compile with -std=c++11 -lstdc++ -lpthread -ldl

/*
	Before including <loguru.hpp> you may optionally want to define the following to 1:

	LOGURU_DEBUG_LOGGING (default 1 #if !NDEBUG, else 0):
		Enables debug versions of logging statements.

	LOGURU_DEBUG_CHECKS (default 1 #if !NDEBUG, else 0):
		Enables debug versions of checks.

	LOGURU_REDEFINE_ASSERT (default 0):
		Redefine "assert" call Loguru version (!NDEBUG only).

	LOGURU_WITH_STREAMS (default 0):
		Add support for _S versions for all LOG and CHECK functions:
			LOG_S(INFO) << "My vec3: " << x.cross(y);
			CHECK_EQ_S(a, b) << "I expected a and b to be the same!";
		This is off by default to keep down compilation times.

	LOGURU_REPLACE_GLOG (default 0):
		Make Loguru mimic GLOG as close as possible,
		including #defining LOG, CHECK, VLOG_IS_ON etc.
		LOGURU_REPLACE_GLOG implies LOGURU_WITH_STREAMS.

	LOGURU_UNSAFE_SIGNAL_HANDLER (default 1):
		Make Loguru try to do unsafe but useful things,
		like printing a stack trace, when catching signals.
		This may lead to bad things like deadlocks in certain situations.

	LOGURU_USE_FMTLIB (default 0):
		Use fmtlib formatting. See https://github.com/fmtlib/fmt
		This will make loguru.hpp depend on <fmt/format.h>
		You will need to link against `fmtlib` or use the `FMT_HEADER_ONLY` preprocessor definition.
		Feature by kolis (https://github.com/emilk/loguru/pull/22)

	LOGURU_WITH_FILEABS (default 0):
		When LOGURU_WITH_FILEABS is defined, a check of file change will be performed on every call to file_log.
		If the file is moved, or inode changes, file is reopened using the same FileMode as is done by add_file.
		Such a scheme is useful if you have a daemon program that moves the log file every 24 hours and expects new file to be created.
		Feature by scinart (https://github.com/emilk/loguru/pull/23).

	LOGURU_STACKTRACES (default 1 on supported platforms):
		Print stack traces on abort.

	LOGURU_RTTI (try to detect automatically by default):
		Set to 0 if your platform does not support runtime type information (-fno-rtti).
*/

// include
#define LOGURU_IMPLEMENTATION 1
#include "loguru.hpp"


int main(int argc, char *argv[])
{
    // Loguru version
    printf("Loguru version: %d.%d.%d\n", LOGURU_VERSION_MAJOR, LOGURU_VERSION_MINOR, LOGURU_VERSION_PATCH);

    /* Everything with a verbosity equal or greater than g_stderr_verbosity will be
	written to stderr. You can set this in code or via the -v argument.
	Set to logurur::Verbosity_OFF to write nothing to stderr.
	Default is 0, i.e. only log ERROR, WARNING and INFO are written to stderr.
	*/
	loguru::g_stderr_verbosity = 1;  	

	/*  Should be called from the main thread.
		You don't *need* to call this, but if you do you get:
			* Signal handlers installed
			* Program arguments logged
			* Working dir logged
			* Optional -v verbosity flag parsed
			* Main thread name set to "main thread"
			* Explanation of the preamble (date, threanmae etc) logged

		loguru::init() will look for arguments meant for loguru and remove them.
		Arguments meant for loguru are:
			-v n   Set loguru::g_stderr_verbosity level. Examples:
				-v 3        Show verbosity level 3 and lower.
				-v 0        Only show INFO, WARNING, ERROR, FATAL (default).
				-v INFO     Only show INFO, WARNING, ERROR, FATAL (default).
				-v WARNING  Only show WARNING, ERROR, FATAL.
				-v ERROR    Only show ERROR, FATAL.
				-v FATAL    Only show FATAL.
				-v OFF      Turn off logging to stderr.

		Tip: You can set g_stderr_verbosity before calling loguru::init.
		That way you can set the default but have the user override it with the -v flag.
		Note that -v does not affect file logging (see loguru::add_file).

		You can use something else instead of "-v" via verbosity_flag.
		You can also set verbosity_flag to nullptr.
	*/
    loguru::init(argc, argv);

	/*  Will log to a file at the given path.
		Any logging message with a verbosity lower or equal to
		the given verbosity will be included.
		The function will create all directories in 'path' if needed.
		If path starts with a ~, it will be replaced with loguru::home_dir()
		To stop the file logging, just call loguru::remove_callback(path) with the same path.
	*/
	loguru::add_file("everything.log", loguru::Append, loguru::Verbosity_MAX);
	loguru::add_file("latest_readable.log", loguru::Truncate, loguru::Verbosity_INFO);

    /* Given a prefix of e.g. "~/loguru/" this might return
	   "/home/your_username/loguru/app_name/20151017_161503.123.log"

	   where "app_name" is a sanitized version of argv[0].
	*/
	char log_path[PATH_MAX];
	loguru::suggest_log_path("~/loguru/", log_path, sizeof(log_path));
	loguru::add_file(log_path, loguru::FileMode::Truncate, loguru::Verbosity_MAX);

	// All Logging macros can be found in loguru.hpp
	LOG_SCOPE_F(INFO, "Will indent all log messages within this scope.");
	LOG_F(INFO, "I'm hungry for some %.3f!", 3.14159);
	LOG_F(2, "Will only show if verbosity is 2 or higher");
    const char *filename = "loguru.hpp";
	auto fp = fopen(filename, "r");
	CHECK_F(fp != nullptr, "Failed to open file '%s'", filename);
	CHECK_GT_F(2, 0); // Will print the value of `length` on failure.
	CHECK_EQ_F(2, 2, "You can also supply a custom message, like to print something: %d", 2 + 3);

	// // Each function also comes with a version prefixed with D for Debug:
	// DCHECK_F(expensive_check(x)); // Only checked #if LOGURU_DEBUG_CHECKS
	// DLOG_F("Only written in debug-builds");

	// Turn off writing to stderr:
	loguru::g_stderr_verbosity = loguru::Verbosity_OFF;

	// Turn off writing err/warn in red:
	loguru::g_colorlogtostderr = false;

	// Throw exceptions instead of aborting on CHECK fails:
	loguru::set_fatal_handler([](const loguru::Message& message){
		throw std::runtime_error(std::string(message.prefix) + message.message);
	});

    return 0;
}