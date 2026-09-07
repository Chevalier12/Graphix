#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_test.h>

#ifdef SDL_PLATFORM_WINDOWS
#include <windows.h>
#define EXE ".exe"
#else
#define EXE ""
#endif

/*
 * FIXME: Additional tests:
 * - stdin to stderr
 */

typedef struct {
    const char *childprocess_path;
} TestProcessData;

static TestProcessData parsed_args;

static void SDLCALL setUpProcess(void **arg) {
    *arg = &parsed_args;
}

static const char *options[] = {
    "/path/to/childprocess" EXE,
    NULL
};

static char **CreateArguments(int ignore, ...) {
    va_list ap;
    size_t count = 1;
    size_t i;
    char **result;

    va_start(ap, ignore);
    for (;;) {
        const char *keyN = va_arg(ap, const char *);
        if (!keyN) {
            break;
        }
        count += 1;
    }
    va_end(ap);

    result = SDL_calloc(count, sizeof(char *));

    i = 0;
    va_start(ap, ignore);
    for (;;) {
        const char *keyN = va_arg(ap, const char *);
        if (!keyN) {
            break;
        }
        result[i++] = SDL_strdup(keyN);
    }
    va_end(ap);

    return result;
}

static void DestroyStringArray(char **list) {
    char **current;

    if (!list) {
        return;
    }
    for (current = list; *current; current++) {
        SDL_free(*current);
    }
    SDL_free(list);
}

static int SDLCALL process_testArguments(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--print-arguments",
        "--",
        "",
        "  ",
        "a b c",
        "a\tb\tc\t\v\r\n",
        "\"a b\" c",
        "'a' 'b' 'c'",
        "%d%%%s",
        "\\t\\c",
        "evil\\",
        "a\\b\"c\\",
        "\"\\^&|<>%", /* characters with a special meaning */
        NULL
    };
    SDL_Process *process = NULL;
    char *buffer;
    int exit_code;
    int i;
    size_t total_read = 0;

    process = SDL_CreateProcess(process_args, true);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcess()");
    if (!process) {
        goto failed;
    }

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    if (!buffer) {
        goto failed;
    }
    SDLTest_LogEscapedString("stdout of process: ", buffer, total_read);

    for (i = 3; process_args[i]; i++) {
        char line[64];
        SDL_snprintf(line, sizeof(line), "|%d=%s|", i - 3, process_args[i]);
        SDLTest_AssertCheck(!!SDL_strstr(buffer, line), "Check %s is in output", line);
    }
    SDL_free(buffer);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;
failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

/* Graphix #2 / SDL #16217: preserve backslash runs before a literal quote,
 * including the boundary between that argument and the following argument. */
static int SDLCALL process_testArgumentsBackslashQuote(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    static const char *const arguments[] = {
        "foo" "\"" "bar",         /* zero backslashes: control */
        "foo" "\\" "\"" "bar",   /* one backslash: control */
        "foo" "\\\\" "\"" "bar", /* two backslashes: reported regression */
        "foo" "\\\\\\" "\"" "bar",
        "foo" "\\\\\\\\" "\"" "bar",
        "foo bar\\\\",
        "foo bar\\\\\\",
        "foo bar\\\\\\\\",
        "%GRAPHIX_EXPAND%!\r\n", /* shell restrictions must not affect executables */
        "^&|<>()[]{}=;,+"
    };
    const char *process_args[] = {
        data->childprocess_path, "--print-arguments", "--", NULL, "baz", NULL
    };
    int i;

    for (i = 0; i < SDL_arraysize(arguments); i++) {
        SDL_Process *process;
        char *buffer;
        char expected[64];
        size_t total_read = 0;
        size_t expected_size;
        int exit_code = -1;

        process_args[3] = arguments[i];
        /* childprocess prints one indexed line per argument in binary mode. */
        SDL_snprintf(expected, sizeof(expected), "|0=%s|\r\n|1=baz|\r\n", arguments[i]);
        expected_size = SDL_strlen(expected);

        process = SDL_CreateProcess(process_args, true);
        SDLTest_AssertCheck(process != NULL, "Case %d: SDL_CreateProcess(): %s", i, SDL_GetError());
        if (!process) {
            return TEST_ABORTED;
        }

        buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
        SDLTest_AssertCheck(buffer != NULL, "Case %d: SDL_ReadProcess(): %s", i, SDL_GetError());
        SDLTest_AssertCheck(exit_code == 0, "Case %d: child exit code should be 0, is %d", i, exit_code);
        SDL_DestroyProcess(process);
        if (!buffer || exit_code != 0) {
            SDL_free(buffer);
            return TEST_ABORTED;
        }

        SDLTest_LogEscapedString("Expected argument output: ", expected, expected_size);
        SDLTest_LogEscapedString("Actual argument output: ", buffer, total_read);
        SDLTest_AssertCheck(total_read == expected_size && SDL_memcmp(buffer, expected, expected_size) == 0,
                            "Case %d: preserve both arguments byte-for-byte (%u expected bytes, %u actual)",
                            i, (unsigned)expected_size, (unsigned)total_read);
        SDL_free(buffer);
    }
    return TEST_COMPLETED;
}


#ifdef SDL_PLATFORM_WINDOWS
/* Graphix #2: isolated, disposable files; only the benign childprocess helper is
 * executed. No registry changes, system files, or real exploit payloads. */
typedef struct {
    bool created;
    char root[1024];
    char child[1024];
    char spaced_child[1024];
    char batch[4][1024];
    char marker[1024];
    char missing[1024];
    char ambiguous_dir[1024];
    char ambiguous_child[1024];
    char cmd[1024];
} ProcessWindowsFixture;

static void DestroyProcessWindowsFixture(ProcessWindowsFixture *fixture)
{
    int i;
    if (!fixture->created) {
        return;
    }
    SDLTest_AssertCheck(SDL_RemovePath(fixture->marker), "Remove launch marker");
    for (i = 0; i < SDL_arraysize(fixture->batch); i++) {
        SDLTest_AssertCheck(SDL_RemovePath(fixture->batch[i]), "Remove batch fixture %d", i);
    }
    SDLTest_AssertCheck(SDL_RemovePath(fixture->child), "Remove child fixture");
    SDLTest_AssertCheck(SDL_RemovePath(fixture->spaced_child), "Remove spaced child fixture");
    SDLTest_AssertCheck(SDL_RemovePath(fixture->ambiguous_child), "Remove ambiguous child fixture");
    SDLTest_AssertCheck(SDL_RemovePath(fixture->ambiguous_dir), "Remove ambiguous directory");
    SDLTest_AssertCheck(SDL_RemovePath(fixture->root), "Remove fixture directory");
}

static bool CreateProcessWindowsFixture(TestProcessData *data, ProcessWindowsFixture *fixture)
{
    char directory[64];
    char *cwd = SDL_GetCurrentDirectory();
    WCHAR system_directory[1024];
    UINT system_length;
    char *system_utf8;
    int i;
    bool result = false;

    SDL_zero(*fixture);
    if (!cwd || SDL_strlen(cwd) > 800) {
        SDLTest_AssertCheck(false, "Obtain a current directory that fits the fixture paths");
        SDL_free(cwd);
        return false;
    }
    for (i = 0; cwd[i]; i++) {
        if (cwd[i] == '/') {
            cwd[i] = '\\';
        }
    }
    SDL_snprintf(directory, sizeof(directory), "graphix-process-%lu-%016" SDL_PRIx64,
                 (unsigned long)GetCurrentProcessId(), SDL_GetTicksNS());
    SDL_snprintf(fixture->root, sizeof(fixture->root), "%s%s", cwd, directory);
    SDL_free(cwd);
    SDL_snprintf(fixture->child, sizeof(fixture->child), "%s\\probe.exe", fixture->root);
    SDL_snprintf(fixture->spaced_child, sizeof(fixture->spaced_child), "%s\\probe space.exe", fixture->root);
    SDL_snprintf(fixture->batch[0], sizeof(fixture->batch[0]), "%s\\simple.bat", fixture->root);
    SDL_snprintf(fixture->batch[1], sizeof(fixture->batch[1]), "%s\\spaced script.bat", fixture->root);
    SDL_snprintf(fixture->batch[2], sizeof(fixture->batch[2]), "%s\\mixed.CmD", fixture->root);
    SDL_snprintf(fixture->batch[3], sizeof(fixture->batch[3]), "%s\\nested.bat", fixture->root);
    SDL_snprintf(fixture->marker, sizeof(fixture->marker), "%s\\started.txt", fixture->root);
    SDL_snprintf(fixture->missing, sizeof(fixture->missing), "%s\\missing", fixture->root);
    SDL_snprintf(fixture->ambiguous_dir, sizeof(fixture->ambiguous_dir), "%s\\missing suffix", fixture->root);
    SDL_snprintf(fixture->ambiguous_child, sizeof(fixture->ambiguous_child), "%s\\probe.exe", fixture->ambiguous_dir);

    /* Exclusive creation: never reuse or remove somebody else's directory. */
    fixture->created = CreateDirectoryA(directory, NULL) != 0;
    SDLTest_AssertCheck(fixture->created, "Exclusively create fixture directory");
    if (!fixture->created) {
        return false;
    }
    result = SDL_CreateDirectory(fixture->ambiguous_dir) &&
             SDL_CopyFile(data->childprocess_path, fixture->child) &&
             SDL_CopyFile(data->childprocess_path, fixture->spaced_child) &&
             SDL_CopyFile(data->childprocess_path, fixture->ambiguous_child);
    SDLTest_AssertCheck(result, "Create benign executable fixtures: %s", SDL_GetError());
    if (!result) {
        return false;
    }
    for (i = 0; i < SDL_arraysize(fixture->batch); i++) {
        SDL_IOStream *file = SDL_IOFromFile(fixture->batch[i], "wb");
        SDLTest_AssertCheck(file != NULL, "Create batch fixture %d", i);
        if (!file) {
            return false;
        }
        if (i == 3) {
            result = SDL_IOprintf(file, "@echo off\r\n\"%s\" %%*\r\n", fixture->batch[0]) > 0;
        } else {
            result = SDL_IOprintf(file, "@echo off\r\n> \"%s\" echo started\r\n\"%s\" --print-arguments -- %%*\r\n",
                                  fixture->marker, fixture->child) > 0;
        }
        result = SDL_CloseIO(file) && result;
        SDLTest_AssertCheck(result, "Write and close batch fixture %d", i);
        if (!result) {
            return false;
        }
    }
    system_length = GetSystemDirectoryW(system_directory, SDL_arraysize(system_directory));
    SDLTest_AssertCheck(system_length > 0 && system_length < SDL_arraysize(system_directory), "Get system directory");
    if (!system_length || system_length >= SDL_arraysize(system_directory)) {
        return false;
    }
    system_utf8 = SDL_iconv_string("UTF-8", "UTF-16LE", (const char *)system_directory,
                                  (system_length + 1) * sizeof(WCHAR));
    SDLTest_AssertCheck(system_utf8 != NULL, "Convert system directory to UTF-8");
    if (!system_utf8) {
        return false;
    }
    SDL_snprintf(fixture->cmd, sizeof(fixture->cmd), "%s\\cmd.exe", system_utf8);
    SDL_free(system_utf8);
    return true;
}

static SDL_Process *CreateProcessWindowsTest(const char *const *args, SDL_Environment *env, const char *cmdline)
{
    SDL_PropertiesID props = SDL_CreateProperties();
    SDL_Process *process;
    if (!props ||
        !SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)args) ||
        !SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP) ||
        (env && !SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ENVIRONMENT_POINTER, env)) ||
        (cmdline && !SDL_SetStringProperty(props, SDL_PROP_PROCESS_CREATE_CMDLINE_STRING, cmdline))) {
        SDLTest_AssertCheck(false, "Set up process properties: %s", SDL_GetError());
        SDL_DestroyProperties(props);
        return NULL;
    }
    /* Default stdin is NULL: malformed shell commands cannot wait for input. */
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    return process;
}

static void CheckProcessWindowsOutput(const char *const *args, const char *expected, const char *cmdline)
{
    SDL_Process *process = CreateProcessWindowsTest(args, NULL, cmdline);
    char *output;
    size_t size = 0;
    size_t expected_size = SDL_strlen(expected);
    int exit_code = -1;

    SDLTest_AssertCheck(process != NULL, "Create process: %s", SDL_GetError());
    if (!process) {
        return;
    }
    output = SDL_ReadProcess(process, &size, &exit_code);
    SDLTest_AssertCheck(output != NULL, "Read process output: %s", SDL_GetError());
    SDLTest_AssertCheck(exit_code == 0, "Child exits successfully, got %d", exit_code);
    if (output) {
        SDLTest_LogEscapedString("Expected: ", expected, expected_size);
        SDLTest_LogEscapedString("Actual: ", output, size);
        SDLTest_AssertCheck(size == expected_size && SDL_memcmp(output, expected, expected_size) == 0,
                            "Preserve exact argument contents and boundaries");
    }
    SDL_free(output);
    SDL_DestroyProcess(process);
}

static void CheckProcessWindowsRejected(ProcessWindowsFixture *fixture, const char *const *args, SDL_Environment *env)
{
    SDL_Process *process;
    SDLTest_AssertCheck(SDL_RemovePath(fixture->marker), "Clear marker before rejected launch");
    SDL_ClearError();
    process = CreateProcessWindowsTest(args, env, NULL);
    SDLTest_AssertCheck(process == NULL, "Reject before launching a child");
    SDLTest_AssertCheck(SDL_strncmp(SDL_GetError(), "Windows process arguments:", 26) == 0,
                        "Report explicit argument validation error, got: %s", SDL_GetError());
    if (process) {
        char *output = SDL_ReadProcess(process, NULL, NULL);
        SDL_free(output);
        SDL_DestroyProcess(process);
    }
    SDLTest_AssertCheck(!SDL_GetPathInfo(fixture->marker, NULL), "Rejected input did not execute batch fixture");
}
#endif

static int SDLCALL process_testWindowsBatchArguments(void *arg)
{
#ifndef SDL_PLATFORM_WINDOWS
    return TEST_SKIPPED;
#else
    ProcessWindowsFixture fixture;
    static const char *const values[] = {
        "", "plain", "foo bar", "foo\tbar", "\"a b\" c",
        "foo" "\\\\" "\"" "bar", "foo bar\\\\", "^", "a&echo GRAPHIX_UNEXPECTED",
        "<>&|()[]{}^=;'+,~", "a\"&echo GRAPHIX_UNEXPECTED", "a^\"&echo GRAPHIX_UNEXPECTED"
    };
    const char *args[] = { NULL, NULL, "baz", NULL };
    char expected[256];
    int file, value;

    if (!CreateProcessWindowsFixture((TestProcessData *)arg, &fixture)) {
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    for (file = 0; file < SDL_arraysize(fixture.batch); file++) {
        args[0] = fixture.batch[file];
        for (value = 0; value < SDL_arraysize(values); value++) {
            SDLTest_Log("Batch filename case %d, argument case %d", file, value);
            args[1] = values[value];
            /* Maintainer-approved strict shell policy: quotes are rejected,
             * not encoded for a guessed number of batch expansion passes. */
            if (SDL_strchr(values[value], '"')) {
                CheckProcessWindowsRejected(&fixture, args, NULL);
                continue;
            }
            SDL_snprintf(expected, sizeof(expected), "|0=%s|\r\n|1=baz|\r\n", values[value]);
            CheckProcessWindowsOutput(args, expected, NULL);
        }
    }
    DestroyProcessWindowsFixture(&fixture);
    return TEST_COMPLETED;
#endif
}

static int SDLCALL process_testWindowsExecutableBoundary(void *arg)
{
#ifndef SDL_PLATFORM_WINDOWS
    return TEST_SKIPPED;
#else
    ProcessWindowsFixture fixture;
    const char *args[] = { NULL, "--print-arguments", "--", "control", NULL };
    const char *ambiguous_args[] = { NULL, "suffix\\probe.exe", "--print-arguments", "--", "UNEXPECTED", NULL };
    const char *invalid_args[] = { NULL, "control", NULL };
    static const char *const suffixes[] = { ".", " ", ". ", " .", "..  ", "\t", "\r", "\n" };
    char invalid_path[1100];
    int file, suffix;

    if (!CreateProcessWindowsFixture((TestProcessData *)arg, &fixture)) {
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    args[0] = fixture.spaced_child;
    CheckProcessWindowsOutput(args, "|0=control|\r\n", NULL);
    args[0] = fixture.ambiguous_child;
    CheckProcessWindowsOutput(args, "|0=control|\r\n", NULL);
    ambiguous_args[0] = fixture.missing;
    {
        SDL_Process *process = CreateProcessWindowsTest(ambiguous_args, NULL, NULL);
        SDLTest_AssertCheck(process == NULL, "Never combine missing argv[0] with argv[1] to select another executable");
        if (process) {
            char *output = SDL_ReadProcess(process, NULL, NULL);
            SDLTest_Log("Unexpected executable launched");
            SDL_free(output);
            SDL_DestroyProcess(process);
        }
    }
    for (file = 0; file < SDL_arraysize(fixture.batch) + 1; file++) {
        const char *path = file < SDL_arraysize(fixture.batch) ? fixture.batch[file] : fixture.child;
        for (suffix = 0; suffix < SDL_arraysize(suffixes); suffix++) {
            SDLTest_Log("Reject filename case %d, suffix case %d", file, suffix);
            SDL_snprintf(invalid_path, sizeof(invalid_path), "%s%s", path, suffixes[suffix]);
            invalid_args[0] = invalid_path;
            CheckProcessWindowsRejected(&fixture, invalid_args, NULL);
        }
    }
    DestroyProcessWindowsFixture(&fixture);
    return TEST_COMPLETED;
#endif
}

static int SDLCALL process_testWindowsShellRejections(void *arg)
{
#ifndef SDL_PLATFORM_WINDOWS
    return TEST_SKIPPED;
#else
    ProcessWindowsFixture fixture;
    static const char *const values[] = {
        "%GRAPHIX_EXPAND%", "^%GRAPHIX_EXPAND^%",
        "%CMDCMDLINE:~-1%&echo GRAPHIX_UNEXPECTED", "!GRAPHIX_EXPAND!",
        "foo\rbar", "foo\nbar", "\r", "\n", "\"", "a\"&echo GRAPHIX_UNEXPECTED"
    };
    const char *batch_args[] = { NULL, NULL, "baz", NULL };
    const char *cmd_args[] = { NULL, "/d", "/s", "/c", NULL, NULL, "baz", NULL };
    const char *shells[3];
    SDL_Environment *env;
    int shell, value;

    if (!CreateProcessWindowsFixture((TestProcessData *)arg, &fixture)) {
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    env = SDL_CreateEnvironment(true);
    if (!env ||
        !SDL_SetEnvironmentVariable(env, "GRAPHIX_EXPAND", "\"&echo GRAPHIX_UNEXPECTED", true) ||
        !SDL_SetEnvironmentVariable(env, "GRAPHIX_EXPAND^", "\"&echo GRAPHIX_UNEXPECTED", true)) {
        SDLTest_AssertCheck(false, "Create isolated expansion environment");
        SDL_DestroyEnvironment(env);
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    batch_args[0] = fixture.batch[0];
    for (value = 0; value < SDL_arraysize(values); value++) {
        SDLTest_Log("Reject batch argument case %d", value);
        batch_args[1] = values[value];
        CheckProcessWindowsRejected(&fixture, batch_args, env);
    }
    shells[0] = "cmd";
    shells[1] = "CMD.EXE";
    shells[2] = fixture.cmd;
    cmd_args[4] = fixture.batch[0];
    for (shell = 0; shell < SDL_arraysize(shells); shell++) {
        cmd_args[0] = shells[shell];
        for (value = 0; value < SDL_arraysize(values); value++) {
            SDLTest_Log("Reject cmd spelling %d, argument case %d", shell, value);
            cmd_args[5] = values[value];
            CheckProcessWindowsRejected(&fixture, cmd_args, env);
        }
    }
    SDL_DestroyEnvironment(env);
    DestroyProcessWindowsFixture(&fixture);
    return TEST_COMPLETED;
#endif
}

static int SDLCALL process_testWindowsCmdArguments(void *arg)
{
#ifndef SDL_PLATFORM_WINDOWS
    return TEST_SKIPPED;
#else
    ProcessWindowsFixture fixture;
    static const char *const values[] = {
        "", "foo bar", "foo\tbar", "foo" "\\\\" "\"" "bar",
        "a&echo GRAPHIX_UNEXPECTED", "a\"&echo GRAPHIX_UNEXPECTED", "foo bar\\\\", "^", "/c", "/k"
    };
    const char *args[] = { NULL, "/c", NULL, "--print-arguments", "--", NULL, "baz", NULL };
    const char *shells[3];
    char expected[256];
    char raw_command[1400];
    const char *invalid_args[] = { "cmd.exe", "/c", "%REJECTED%!", NULL };
    static const char *const invalid_options[] = { "/c echo", "/d/c", "/unknown", "/t:GG" };
    int shell, value;

    if (!CreateProcessWindowsFixture((TestProcessData *)arg, &fixture)) {
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    shells[0] = "cmd";
    shells[1] = "CMD.EXE";
    shells[2] = fixture.cmd;
    args[2] = fixture.spaced_child;
    for (shell = 0; shell < SDL_arraysize(shells); shell++) {
        args[0] = shells[shell];
        for (value = 0; value < SDL_arraysize(values); value++) {
            SDLTest_Log("Literal cmd spelling %d, argument case %d", shell, value);
            args[5] = values[value];
            if (SDL_strchr(values[value], '"')) {
                CheckProcessWindowsRejected(&fixture, args, NULL);
                continue;
            }
            SDL_snprintf(expected, sizeof(expected), "|0=%s|\r\n|1=baz|\r\n", values[value]);
            CheckProcessWindowsOutput(args, expected, NULL);
        }
        {
            const char *option_args[] = {
                shells[shell], "/D", "/S", "/Q", "/A", "/E:ON", "/F:OFF", "/V:ON", "/T:0A", "/C",
                fixture.spaced_child, "--print-arguments", "--", "a&echo GRAPHIX_UNEXPECTED", NULL
            };
            const char *rejected_args[] = { shells[shell], NULL, fixture.batch[0], NULL };
            const char *missing_command[] = { shells[shell], "/c", NULL };
            const char *empty_command[] = { shells[shell], "/k", "", NULL };
            int option;

            CheckProcessWindowsOutput(option_args, "|0=a&echo GRAPHIX_UNEXPECTED|\r\n", NULL);
            for (option = 0; option < SDL_arraysize(invalid_options); option++) {
                rejected_args[1] = invalid_options[option];
                CheckProcessWindowsRejected(&fixture, rejected_args, NULL);
            }
            CheckProcessWindowsRejected(&fixture, missing_command, NULL);
            CheckProcessWindowsRejected(&fixture, empty_command, NULL);
        }
    }
    /* The explicitly raw escape hatch still owns shell syntax and takes
     * precedence over an argument list that the strict path would reject. */
    SDL_snprintf(raw_command, sizeof(raw_command), "\"%s\" /d /v:off /s /c \"echo RAW_FIRST&echo RAW_SECOND\"", fixture.cmd);
    CheckProcessWindowsOutput(invalid_args, "RAW_FIRST\r\nRAW_SECOND\r\n", raw_command);
    DestroyProcessWindowsFixture(&fixture);
    return TEST_COMPLETED;
#endif
}


static int SDLCALL process_testexitCode(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    int i;
    int exit_codes[] = {
        0, 13, 31, 127, 255
    };

    for (i = 0; i < SDL_arraysize(exit_codes); i++) {
        bool wait_result;
        SDL_Process *process = NULL;
        char **process_args = NULL;
        char number_buffer[8];
        int exit_code;

        SDL_snprintf(number_buffer, sizeof(number_buffer), "%d", exit_codes[i]);

        process_args = CreateArguments(0, data->childprocess_path, "--exit-code", number_buffer, NULL);

        process = SDL_CreateProcess((const char * const *)process_args, false);
        SDLTest_AssertCheck(process != NULL, "SDL_CreateProcess()");
        if (!process) {
            goto failed;
        }

        exit_code = 0xdeadbeef;
        SDLTest_AssertPass("About to wait on process (first time)");
        wait_result = SDL_WaitProcess(process, true, &exit_code);
        SDLTest_AssertCheck(wait_result == true, "SDL_WaitProcess(): Process should have closed immediately");
        SDLTest_AssertCheck(exit_code == exit_codes[i], "SDL_WaitProcess(): Exit code should be %d, is %d", exit_codes[i], exit_code);

        exit_code = 0xdeadbeef;
        SDLTest_AssertPass("About to wait on process (second time)");
        wait_result = SDL_WaitProcess(process, true, &exit_code);
        SDLTest_AssertCheck(wait_result == true, "SDL_WaitProcess(): Process should have closed immediately");
        SDLTest_AssertCheck(exit_code == exit_codes[i], "SDL_WaitProcess(): Exit code should be %d, is %d", exit_codes[i], exit_code);

        SDLTest_AssertPass("About to destroy process");
        SDL_DestroyProcess(process);
        DestroyStringArray(process_args);
        continue;
failed:
        SDL_DestroyProcess(process);
        DestroyStringArray(process_args);
        return TEST_ABORTED;
    }
    return TEST_COMPLETED;
#if 0
failed:
    SDL_DestroyProcess(process);
    DestroyStringArray(process_args);
    return TEST_ABORTED;
#endif
}

static int SDLCALL process_testInheritedEnv(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--print-environment",
        NULL,
    };
    SDL_PropertiesID props;
    SDL_Process *process = NULL;
    Sint64 pid;
    int exit_code;
    char random_env1[64];
    char random_env2[64];
    static const char *const TEST_ENV_KEY1 = "testprocess_inherited_var";
    static const char *const TEST_ENV_KEY2 = "testprocess_other_var";
    char *test_env_val1 = NULL;
    char *test_env_val2 = NULL;
    char *buffer = NULL;

    test_env_val1 = SDLTest_RandomAsciiStringOfSize(32);
    SDL_snprintf(random_env1, sizeof(random_env1), "%s=%s", TEST_ENV_KEY1, test_env_val1);
    SDLTest_AssertPass("Setting parent environment variable %s=%s", TEST_ENV_KEY1, test_env_val1);
    SDL_SetEnvironmentVariable(SDL_GetEnvironment(), TEST_ENV_KEY1, test_env_val1, true);

    SDL_UnsetEnvironmentVariable(SDL_GetEnvironment(), TEST_ENV_KEY2);

    props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    test_env_val2 = SDLTest_RandomAsciiStringOfSize(32);
    SDL_snprintf(random_env2, sizeof(random_env2), "%s=%s", TEST_ENV_KEY2, test_env_val2);
    SDLTest_AssertPass("Setting parent environment variable %s=%s", TEST_ENV_KEY2, test_env_val2);
    SDL_SetEnvironmentVariable(SDL_GetEnvironment(),TEST_ENV_KEY2, test_env_val2, true);
    SDLTest_AssertCheck(SDL_strcmp(test_env_val1, test_env_val2) != 0, "Sanity checking the 2 random environment variables are not identical");

    props = SDL_GetProcessProperties(process);
    SDLTest_AssertCheck(props != 0, "SDL_GetProcessProperties()");

    pid = SDL_GetNumberProperty(props, SDL_PROP_PROCESS_PID_NUMBER, 0);
    SDLTest_AssertCheck(pid != 0, "Checking process ID, expected non-zero, got %" SDL_PRIs64, pid);

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, NULL, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);

    SDLTest_AssertCheck(SDL_strstr(buffer, random_env1) != NULL, "Environment of child should contain \"%s\"", test_env_val1);
    SDLTest_AssertCheck(SDL_strstr(buffer, random_env2) == NULL, "Environment of child should not contain \"%s\"", test_env_val2);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    SDL_free(test_env_val1);
    SDL_free(test_env_val2);
    SDL_free(buffer);
    return TEST_COMPLETED;
failed:
    SDL_free(test_env_val1);
    SDL_free(test_env_val2);
    SDL_DestroyProcess(process);
    SDL_free(buffer);
    return TEST_ABORTED;
}

static int SDLCALL process_testNewEnv(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--print-environment",
        NULL,
    };
    SDL_Environment *process_env;
    SDL_PropertiesID props;
    SDL_Process *process = NULL;
    Sint64 pid;
    int exit_code;
    char random_env1[64];
    char random_env2[64];
    static const char *const TEST_ENV_KEY1 = "testprocess_inherited_var";
    static const char *const TEST_ENV_KEY2 = "testprocess_other_var";
    char *test_env_val1 = NULL;
    char *test_env_val2 = NULL;
    char *buffer = NULL;
    size_t total_read = 0;

    test_env_val1 = SDLTest_RandomAsciiStringOfSize(32);
    SDL_snprintf(random_env1, sizeof(random_env1), "%s=%s", TEST_ENV_KEY1, test_env_val1);
    SDLTest_AssertPass("Unsetting parent environment variable %s", TEST_ENV_KEY1);
    SDL_UnsetEnvironmentVariable(SDL_GetEnvironment(), TEST_ENV_KEY1);

    process_env = SDL_CreateEnvironment(true);
    SDL_SetEnvironmentVariable(process_env, "PATH", SDL_GetEnvironmentVariable(SDL_GetEnvironment(), "PATH"), true);
    SDL_SetEnvironmentVariable(process_env, "LD_LIBRARY_PATH", SDL_GetEnvironmentVariable(SDL_GetEnvironment(), "LD_LIBRARY_PATH"), true);
    SDL_SetEnvironmentVariable(process_env, "DYLD_LIBRARY_PATH", SDL_GetEnvironmentVariable(SDL_GetEnvironment(), "DYLD_LIBRARY_PATH"), true);
    SDL_SetEnvironmentVariable(process_env, TEST_ENV_KEY1, test_env_val1, true);

    test_env_val2 = SDLTest_RandomAsciiStringOfSize(32);
    SDL_snprintf(random_env2, sizeof(random_env2), "%s=%s", TEST_ENV_KEY2, test_env_val1);
    SDLTest_AssertPass("Setting parent environment variable %s=%s", TEST_ENV_KEY2, test_env_val2);
    SDL_SetEnvironmentVariable(SDL_GetEnvironment(), TEST_ENV_KEY2, test_env_val2, true);
    SDLTest_AssertCheck(SDL_strcmp(test_env_val1, test_env_val2) != 0, "Sanity checking the 2 random environment variables are not identical");

    props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ENVIRONMENT_POINTER, process_env);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    props = SDL_GetProcessProperties(process);
    SDLTest_AssertCheck(props != 0, "SDL_GetProcessProperties()");

    pid = SDL_GetNumberProperty(props, SDL_PROP_PROCESS_PID_NUMBER, 0);
    SDLTest_AssertCheck(pid != 0, "Checking process ID, expected non-zero, got %" SDL_PRIs64, pid);

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    SDLTest_LogEscapedString("Text read from subprocess: ", buffer, total_read);

    SDLTest_AssertCheck(SDL_strstr(buffer, random_env1) != NULL, "Environment of child should contain \"%s\"", random_env1);
    SDLTest_AssertCheck(SDL_strstr(buffer, random_env2) == NULL, "Environment of child should not contain \"%s\"", random_env1);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    SDL_DestroyEnvironment(process_env);
    SDL_free(test_env_val1);
    SDL_free(test_env_val2);
    SDL_free(buffer);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    SDL_DestroyEnvironment(process_env);
    SDL_free(test_env_val1);
    SDL_free(test_env_val2);
    SDL_free(buffer);
    return TEST_ABORTED;
}

static int SDLCALL process_testKill(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--stdin",
        NULL,
    };
    SDL_Process *process = NULL;
    SDL_PropertiesID props;
    Sint64 pid;
    int result;
    int exit_code;

    SDLTest_AssertPass("About to call SDL_CreateProcess(true)");
    process = SDL_CreateProcess(process_args, true);
    if (!process) {
        goto failed;
    }

    props = SDL_GetProcessProperties(process);
    SDLTest_AssertCheck(props != 0, "SDL_GetProcessProperties()");

    pid = SDL_GetNumberProperty(props, SDL_PROP_PROCESS_PID_NUMBER, 0);
    SDLTest_AssertCheck(pid != 0, "Checking process ID, expected non-zero, got %" SDL_PRIs64, pid);

    exit_code = 0xdeadbeef;
    SDLTest_AssertPass("About to call SDL_WaitProcess(false)");
    result = SDL_WaitProcess(process, false, &exit_code);
    SDLTest_AssertCheck(result == false, "Process should not have exited yet");

    /* Wait for the child process to finish initializing */
    SDL_Delay(500);

    SDLTest_AssertPass("About to call SDL_KillProcess(true)");
    result = SDL_KillProcess(process, true);
    SDLTest_AssertCheck(result == true, "Process should have exited");

    exit_code = 0;
    SDLTest_AssertPass("About to call SDL_WaitProcess(true)");
    result = SDL_WaitProcess(process, true, &exit_code);
    SDLTest_AssertCheck(result == true, "Process should have exited");
    SDLTest_AssertCheck(exit_code != 0, "Exit code should be non-zero, is %d", exit_code);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static int process_testStdinToStdout(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--stdin-to-stdout",
        NULL,
    };
    SDL_PropertiesID props;
    SDL_Process *process = NULL;
    Sint64 pid;
    SDL_IOStream *process_stdin = NULL;
    SDL_IOStream *process_stdout = NULL;
    SDL_IOStream *process_stderr = NULL;
    size_t text_in_size = 1 * 1024 * 1024;
    char *text_in = NULL;
    size_t total_written;
    size_t total_read;
    bool wait_result;
    int exit_code;
    SDL_IOStream *stdout_stream = NULL;
    char *stdout_stream_buf;
    int iteration_count = 0;

    text_in = SDLTest_RandomAsciiStringOfSize((int)text_in_size);
    /* Make sure text_in does not contain EOF */
    for (;;) {
        char *e = SDL_strstr(text_in, "EOF");
        if (!e) {
            break;
        }
        e[0] = 'N';
    }
    text_in[text_in_size - 3] = 'E';
    text_in[text_in_size - 2] = 'O';
    text_in[text_in_size - 1] = 'F';

    stdout_stream = SDL_IOFromDynamicMem();

    props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    props = SDL_GetProcessProperties(process);
    SDLTest_AssertCheck(props != 0, "SDL_GetProcessProperties()");

    pid = SDL_GetNumberProperty(props, SDL_PROP_PROCESS_PID_NUMBER, 0);
    SDLTest_AssertCheck(pid != 0, "Checking process ID, expected non-zero, got %" SDL_PRIs64, pid);

    process_stdin = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(process_stdin != NULL, "SDL_GetPointerProperty(SDL_PROP_PROCESS_STDIN_POINTER) returns a valid IO stream");
    process_stdout = SDL_GetProcessOutput(process);
    SDLTest_AssertCheck(process_stdout != NULL, "SDL_GetPointerProperty(SDL_PROP_PROCESS_STDOUT_POINTER) returns a valid IO stream");
    process_stderr = (SDL_IOStream *)SDL_GetPointerProperty(props, SDL_PROP_PROCESS_STDERR_POINTER, NULL);
    SDLTest_AssertCheck(process_stderr == NULL, "SDL_GetPointerProperty(SDL_PROP_PROCESS_STDERR_POINTER) returns NULL");
    if (!process_stdin || !process_stdout) {
        goto failed;
    }

    total_written = 0;
    total_read = 0;
    for (;;) {
        int log_this_iteration = (iteration_count % 32) == 32;
        char local_buffer[16 * 4094];
        size_t amount_read;
        SDL_IOStatus io_status;
        if (total_written != text_in_size) {
            size_t amount_written;
            if (log_this_iteration) {
                SDLTest_AssertPass("About to SDL_WriteIO (%dth time)", iteration_count);
            }
            amount_written = SDL_WriteIO(process_stdin, text_in + total_written, text_in_size - total_written);
            if (log_this_iteration) {
                SDLTest_Log("SDL_WriteIO() -> %u (%dth time)", (unsigned)amount_written, iteration_count);
            }
            if (amount_written == 0) {
                io_status = SDL_GetIOStatus(process_stdin);
                if (io_status != SDL_IO_STATUS_NOT_READY) {
                    SDLTest_Log("SDL_GetIOStatus(process_stdin) returns %d, breaking.", io_status);
                    break;
                }
            }
            total_written += amount_written;
            SDL_FlushIO(process_stdin);
        }

        /* FIXME: this needs a rate limit */
        if (log_this_iteration) {
            SDLTest_AssertPass("About to SDL_ReadIO (%dth time)", iteration_count);
        }
        amount_read = SDL_ReadIO(process_stdout, local_buffer, sizeof(local_buffer));
        if (log_this_iteration) {
            SDLTest_Log("SDL_ReadIO() -> %u (%dth time)", (unsigned)amount_read, iteration_count);
        }
        if (amount_read == 0) {
            io_status = SDL_GetIOStatus(process_stdout);
            if (io_status != SDL_IO_STATUS_NOT_READY) {
                SDLTest_Log("SDL_GetIOStatus(process_stdout) returned %d, breaking.", io_status);
                break;
            }
        } else {
            total_read += amount_read;
            SDL_WriteIO(stdout_stream, local_buffer, amount_read);
            stdout_stream_buf = SDL_GetPointerProperty(SDL_GetIOProperties(stdout_stream), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, NULL);
            /* Graphix: the dynamic stream contains raw bytes, not a terminated string. */
            if (SDL_strnstr(stdout_stream_buf, "EOF", total_read)) {
                SDLTest_Log("Found EOF in stdout");
                break;
            }
        }
        SDL_Delay(10);
    }
    SDLTest_Log("Wrote %" SDL_PRIu64 " bytes to process.stdin", (Uint64)total_written);
    SDLTest_Log("Read %" SDL_PRIu64 " bytes from process.stdout",(Uint64)total_read);

    stdout_stream_buf = SDL_GetPointerProperty(SDL_GetIOProperties(stdout_stream), SDL_PROP_IOSTREAM_DYNAMIC_MEMORY_POINTER, NULL);
    SDLTest_CompareMemory(stdout_stream_buf, total_written, text_in, text_in_size);

    exit_code = 0xdeadbeef;
    wait_result = SDL_WaitProcess(process, false, &exit_code);
    SDLTest_AssertCheck(wait_result == false, "Process should not have closed yet");

    SDLTest_AssertPass("About to close stdin");
    /* Closing stdin of `subprocessstdin --stdin-to-stdout` should close the process */
    SDL_CloseIO(process_stdin);

    process_stdin = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(process_stdin == NULL, "SDL_GetPointerProperty(SDL_PROP_PROCESS_STDIN_POINTER) is cleared after close");

    SDLTest_AssertPass("About to wait on process");
    exit_code = 0xdeadbeef;
    wait_result = SDL_WaitProcess(process, true, &exit_code);
    SDLTest_AssertCheck(wait_result == true, "Process should have closed when closing stdin");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    if (!wait_result) {
        bool killed;
        SDL_Log("About to kill process");
        killed = SDL_KillProcess(process, true);
        SDLTest_AssertCheck(killed, "SDL_KillProcess succeeded");
    }
    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    SDL_CloseIO(stdout_stream);
    SDL_free(text_in);
    return TEST_COMPLETED;
failed:

    SDL_DestroyProcess(process);
    SDL_CloseIO(stdout_stream);
    SDL_free(text_in);
    return TEST_ABORTED;
}

static int process_testStdinToStderr(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--stdin-to-stderr",
        NULL,
    };
    SDL_Process *process = NULL;
    SDL_IOStream *process_stdin = NULL;
    SDL_IOStream *process_stdout = NULL;
    SDL_IOStream *process_stderr = NULL;
    const char *text_in = "Tests whether we can write to stdin and read from stderr\r\n{'succes': true, 'message': 'Success!'}\r\nYippie ka yee\r\nEOF";
    size_t result;
    int exit_code;
    SDL_PropertiesID props;
    char buffer[256];
    size_t amount_read;

    props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_NULL);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_NUMBER, SDL_PROCESS_STDIO_APP);
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    SDLTest_AssertPass("About to write to process");
    process_stdin = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(process_stdin != NULL, "SDL_GetProcessInput()");
    result = SDL_WriteIO(process_stdin, text_in, SDL_strlen(text_in));
    SDLTest_AssertCheck(result == SDL_strlen(text_in), "SDL_WriteIO() wrote %d, expected %d", (int)result, (int)SDL_strlen(text_in));
    SDL_CloseIO(process_stdin);

    process_stdout = SDL_GetProcessOutput(process);
    SDLTest_AssertCheck(process_stdout == NULL, "Process has no stdout");

    process_stderr = SDL_GetPointerProperty(SDL_GetProcessProperties(process), SDL_PROP_PROCESS_STDERR_POINTER, NULL);
    SDLTest_AssertCheck(process_stderr != NULL, "Process has stderr");

    exit_code = 0xdeadbeef;
    result = SDL_WaitProcess(process, true, &exit_code);
    SDLTest_AssertCheck(result == true, "Process should have finished");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);

    amount_read = SDL_ReadIO(process_stderr, buffer, sizeof(buffer));
    SDLTest_CompareMemory(buffer, amount_read, text_in, SDL_strlen(text_in));

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static int process_testSimpleStdinToStdout(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--stdin-to-stdout",
        NULL,
    };
    SDL_Process *process = NULL;
    SDL_IOStream *input = NULL;
    const char *text_in = "Tests whether we can write to stdin and read from stdout\r\n{'succes': true, 'message': 'Success!'}\r\nYippie ka yee\r\nEOF";
    char *buffer;
    size_t result;
    int exit_code;
    size_t total_read = 0;

    process = SDL_CreateProcess(process_args, true);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcess()");
    if (!process) {
        goto failed;
    }

    SDLTest_AssertPass("About to write to process");
    input = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(input != NULL, "SDL_GetProcessInput()");
    result = SDL_WriteIO(input, text_in, SDL_strlen(text_in));
    SDLTest_AssertCheck(result == SDL_strlen(text_in), "SDL_WriteIO() wrote %d, expected %d", (int)result, (int)SDL_strlen(text_in));
    SDL_CloseIO(input);

    input = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(input == NULL, "SDL_GetProcessInput() after close");

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    if (!buffer) {
        goto failed;
    }

    SDLTest_LogEscapedString("Expected text read from subprocess: %s", text_in, SDL_strlen(text_in));
    SDLTest_LogEscapedString("Actual text read from subprocess: %s", buffer, total_read);
    SDLTest_AssertCheck(total_read == SDL_strlen(text_in), "Expected to read %u bytes, actually read %u bytes", (unsigned)SDL_strlen(text_in), (unsigned)total_read);
    SDLTest_AssertCheck(SDL_strcmp(buffer, text_in) == 0, "Subprocess stdout should match text written to stdin");
    SDL_free(buffer);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static int process_testMultiprocessStdinToStdout(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--stdin-to-stdout",
        "--log-stdin",
        NULL,
        NULL,
    };
    SDL_Process *process1 = NULL;
    SDL_Process *process2 = NULL;
    SDL_PropertiesID props;
    SDL_IOStream *input = NULL;
    const char *text_in = "Tests whether we can write to stdin and read from stdout\r\n{'succes': true, 'message': 'Success!'}\r\nYippie ka yee\r\nEOF";
    char *buffer;
    size_t result;
    int exit_code;
    size_t total_read = 0;
    bool finished;

    process_args[3] = "child1-stdin.txt";
    process1 = SDL_CreateProcess(process_args, true);
    SDLTest_AssertCheck(process1 != NULL, "SDL_CreateProcess()");
    if (!process1) {
        goto failed;
    }

    props = SDL_CreateProperties();
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_REDIRECT);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_POINTER, SDL_GetPointerProperty(SDL_GetProcessProperties(process1), SDL_PROP_PROCESS_STDOUT_POINTER, NULL));
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    SDLTest_AssertPass("About to call SDL_CreateProcessWithProperties");
    process_args[3] = "child2-stdin.txt";
    process2 = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process2 != NULL, "SDL_CreateProcess()");
    if (!process2) {
        goto failed;
    }

    SDLTest_AssertPass("About to write to process");
    input = SDL_GetProcessInput(process1);
    SDLTest_AssertCheck(input != NULL, "SDL_GetProcessInput()");
    result = SDL_WriteIO(input, text_in, SDL_strlen(text_in));
    SDLTest_AssertCheck(result == SDL_strlen(text_in), "SDL_WriteIO() wrote %d, expected %d", (int)result, (int)SDL_strlen(text_in));
    SDL_CloseIO(input);

    exit_code = 0xdeadbeef;
    finished = SDL_WaitProcess(process1, true, &exit_code);
    SDLTest_AssertCheck(finished == true, "process 1 should have finished");
    SDLTest_AssertCheck(exit_code == 0, "Exit code of process 1 should be 0, is %d", exit_code);

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process2, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code of process 2 should be 0, is %d", exit_code);
    if (!buffer) {
        goto failed;
    }

    SDLTest_LogEscapedString("Expected text read from subprocess: ", text_in, SDL_strlen(text_in));
    SDLTest_LogEscapedString("Actual text read from subprocess: ", buffer, total_read);
    SDLTest_AssertCheck(total_read == SDL_strlen(text_in), "Expected to read %u bytes, actually read %u bytes", (unsigned)SDL_strlen(text_in), (unsigned)total_read);
    SDLTest_AssertCheck(SDL_strcmp(buffer, text_in) == 0, "Subprocess stdout should match text written to stdin");
    SDL_free(buffer);
    SDLTest_AssertPass("About to destroy processes");
    SDL_DestroyProcess(process1);
    SDL_DestroyProcess(process2);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process1);
    SDL_DestroyProcess(process2);
    return TEST_ABORTED;
}

static int process_testWriteToFinishedProcess(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        NULL,
    };
    SDL_Process *process = NULL;
    bool result;
    int exit_code;
    SDL_IOStream *process_stdin;
    const char *text_in = "text_in";

    SDLTest_AssertPass("About to call SDL_CreateProcess");
    process = SDL_CreateProcess(process_args, true);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcess()");
    if (!process) {
        goto failed;
    }

    exit_code = 0xdeadbeef;
    SDLTest_AssertPass("About to call SDL_WaitProcess");
    result = SDL_WaitProcess(process, true, &exit_code);
    SDLTest_AssertCheck(result, "SDL_WaitProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);

    process_stdin = SDL_GetProcessInput(process);
    SDLTest_AssertCheck(process_stdin != NULL, "SDL_GetProcessInput returns non-Null SDL_IOStream");
    SDLTest_AssertPass("About to call SDL_WriteIO on dead child process");
    SDL_WriteIO(process_stdin, text_in, SDL_strlen(text_in));

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static int process_testNonExistingExecutable(void *arg)
{
    static const int STEM_LENGTH = 16;
    char **process_args;
    char *random_stem;
    char *random_path;
    SDL_Process *process = NULL;
    bool result;
    int exit_code = 0;

    random_stem = SDLTest_RandomAsciiStringOfSize(STEM_LENGTH);
    random_path = SDL_malloc(STEM_LENGTH + SDL_strlen(EXE) + 1);
    SDL_snprintf(random_path, STEM_LENGTH + SDL_strlen(EXE) + 1, "%s%s", random_stem, EXE);
    SDL_free(random_stem);
    SDLTest_AssertCheck(!SDL_GetPathInfo(random_path, NULL), "%s does not exist", random_path);

    process_args = CreateArguments(0, random_path, NULL);
    SDL_free(random_path);

    SDLTest_AssertPass("About to call SDL_CreateProcess");
    process = SDL_CreateProcess((const char * const *)process_args, false);
    if (process) {
        SDLTest_AssertPass("SDL_CreateProcess() returned a process, waiting for exec failure");
        result = SDL_WaitProcess(process, true, &exit_code);
        SDLTest_AssertCheck(result, "SDL_WaitProcess()");
        SDLTest_AssertCheck(exit_code != 0, "Exit code should be non-zero, is %d", exit_code);
        SDL_DestroyProcess(process);
    } else {
        SDLTest_AssertPass("SDL_CreateProcess() failed synchronously (%s)", SDL_GetError());
    }

    DestroyStringArray(process_args);
    return TEST_COMPLETED;
}

static int process_testBatBadButVulnerability(void *arg)
{
#ifndef SDL_PLATFORM_WINDOWS
    return TEST_SKIPPED;
#else
    ProcessWindowsFixture fixture;
    char *inject_arg = NULL;
    const char *args[] = { NULL, NULL, NULL };

    if (!CreateProcessWindowsFixture((TestProcessData *)arg, &fixture)) {
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    /* The original payload is now rejected synchronously under Graphix's
     * approved quote policy, rather than testing a particular quoted spelling
     * of %1 after executing a batch file. The marker proves no batch ran. */
    if (SDL_asprintf(&inject_arg, "\"&%s --version --print-arguments --stdout OWNEDSTDOUT\"", fixture.child) < 0) {
        SDLTest_AssertCheck(false, "Allocate original BatBadBut payload");
        DestroyProcessWindowsFixture(&fixture);
        return TEST_ABORTED;
    }
    args[0] = fixture.batch[0];
    args[1] = "control";
    CheckProcessWindowsOutput(args, "|0=control|\r\n", NULL);
    args[1] = inject_arg;
    CheckProcessWindowsRejected(&fixture, args, NULL);
    SDL_free(inject_arg);
    DestroyProcessWindowsFixture(&fixture);
    return TEST_COMPLETED;
#endif
}

static int process_testFileRedirection(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    SDL_PropertiesID props = 0;
    const char * process_args[] = {
        data->childprocess_path,
        "--stdin-to-stdout",
        "--stdin-to-stderr",
        NULL,
    };
    const char TEXT_REF[] = "This is input for the child process";
    static const char *PATH_STDIN = "test_redirection_stdin.txt";
    static const char *PATH_STDOUT = "test_redirection_stdout.txt";
    static const char *PATH_STDERR = "test_redirection_stderr.txt";
    char *text_out = NULL;
    size_t len_text_out;
    int exitcode;
    bool result;
    SDL_Process *process = NULL;
    SDL_IOStream *stream;
    SDL_IOStream *input_stream = NULL;
    SDL_IOStream *output_stream = NULL;
    SDL_IOStream *error_stream = NULL;

    stream = SDL_IOFromFile(PATH_STDIN, "w");
    SDLTest_AssertCheck(stream != NULL, "SDL_IOFromFile(\"%s\", \"w\")", PATH_STDIN);
    if (!stream) {
        goto cleanup;
    }
    SDL_WriteIO(stream, TEXT_REF, sizeof(TEXT_REF));
    SDL_CloseIO(stream);

    input_stream = SDL_IOFromFile(PATH_STDIN, "r");
    SDLTest_AssertCheck(input_stream != NULL, "SDL_IOFromFile(\"%s\", \"r\")", PATH_STDIN);
    if (!input_stream) {
        goto cleanup;
    }

    output_stream = SDL_IOFromFile(PATH_STDOUT, "w");
    SDLTest_AssertCheck(output_stream != NULL, "SDL_IOFromFile(\"%s\", \"w\")", PATH_STDOUT);
    if (!output_stream) {
        goto cleanup;
    }

    error_stream = SDL_IOFromFile(PATH_STDERR, "w");
    SDLTest_AssertCheck(error_stream != NULL, "SDL_IOFromFile(\"%s\", \"w\")", PATH_STDERR);
    if (!error_stream) {
        goto cleanup;
    }

    props =  SDL_CreateProperties();
    SDLTest_AssertCheck(props != 0, "SDL_CreateProperties()");
    if (!props) {
        goto cleanup;
    }
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_REDIRECT);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_POINTER, (void *)input_stream);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_REDIRECT);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_POINTER, (void *)output_stream);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_NUMBER, SDL_PROCESS_STDIO_REDIRECT);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_POINTER, (void *)error_stream);
    process = SDL_CreateProcessWithProperties(props);
    SDL_DestroyProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties (%s)", SDL_GetError());
    if (!process) {
        goto cleanup;
    }

    exitcode = 0xdeadbeef;
    text_out = SDL_ReadProcess(process, &len_text_out, &exitcode);
    SDLTest_AssertCheck(text_out == NULL, "SDL_ReadProcess should not be able to close a redirected process (%s)", SDL_GetError());
    SDLTest_AssertCheck(len_text_out == 0, "length written by SDL_ReadProcess should be 0");
    SDL_free(text_out);
    text_out = NULL;

    exitcode = 0xdeadbeef;
    result = SDL_WaitProcess(process, true, &exitcode);
    SDLTest_AssertCheck(result, "process must have exited");
    SDLTest_AssertCheck(exitcode == 0, "process exited with exitcode 0, was %d", exitcode);

    SDL_CloseIO(input_stream);
    input_stream = NULL;
    SDL_CloseIO(output_stream);
    output_stream = NULL;
    SDL_CloseIO(error_stream);
    error_stream = NULL;

    text_out = SDL_LoadFile(PATH_STDOUT, &len_text_out);
    SDLTest_AssertCheck(text_out != NULL, "SDL_LoadFile(\"%s\") succeeded (%s)", PATH_STDOUT, SDL_GetError());
    SDLTest_AssertPass("Comparing stdout with reference");
    SDLTest_CompareMemory(text_out, len_text_out, TEXT_REF, sizeof(TEXT_REF));
    SDL_free(text_out);

    text_out = SDL_LoadFile(PATH_STDERR, &len_text_out);
    SDLTest_AssertCheck(text_out != NULL, "SDL_LoadFile(\"%s\") succeeded (%s)", PATH_STDERR, SDL_GetError());
    SDLTest_AssertPass("Comparing stderr with reference");
    SDLTest_CompareMemory(text_out, len_text_out, TEXT_REF, sizeof(TEXT_REF));
    SDL_free(text_out);

cleanup:
    SDL_CloseIO(input_stream);
    SDL_CloseIO(output_stream);
    SDL_CloseIO(error_stream);
    SDL_DestroyProcess(process);
    return TEST_COMPLETED;
}

static int process_testWindowsCmdline(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--print-arguments",
        "--",
        "",
        "  ",
        "a b c",
        "a\tb\tc\t",
        "\"a b\" c",
        "'a' 'b' 'c'",
        "%d%%%s",
        "\\t\\c",
        "evil\\",
        "a\\b\"c\\",
        "\"\\^&|<>%", /* characters with a special meaning */
        NULL
    };
    /* this will have the same result as process_args, but escaped in a different way */
    const char *process_cmdline_template =
        "%s "
        "--print-arguments "
        "-- "
        "\"\" "
        "\"  \" "
        "a\" \"b\" \"c\t" /* using tab as delimiter */
        "\"a\tb\tc\t\" "
        "\"\"\"\"a b\"\"\" c\" "
        "\"'a' 'b' 'c'\" "
        "%%d%%%%%%s " /* will be passed to sprintf */
        "\\t\\c "
        "evil\\ "
        "a\\b\"\\\"\"c\\ "
        "\\\"\\^&|<>%%";
    char process_cmdline[65535];
    SDL_PropertiesID props;
    SDL_Process *process = NULL;
    char *buffer;
    int exit_code;
    int i;
    size_t total_read = 0;

#ifndef SDL_PLATFORM_WINDOWS
    SDLTest_AssertPass("SDL_PROP_PROCESS_CREATE_CMDLINE_STRING only works on Windows");
    return TEST_SKIPPED;
#endif

    props = SDL_CreateProperties();
    SDLTest_AssertCheck(props != 0, "SDL_CreateProperties()");
    if (!props) {
        goto failed;
    }
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetBooleanProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_TO_STDOUT_BOOLEAN, true);

    process = SDL_CreateProcessWithProperties(props);
    SDLTest_AssertCheck(process == NULL, "SDL_CreateProcessWithProperties() should fail");

    SDL_snprintf(process_cmdline, SDL_arraysize(process_cmdline), process_cmdline_template, data->childprocess_path);
    SDL_SetStringProperty(props, SDL_PROP_PROCESS_CREATE_CMDLINE_STRING, process_cmdline);

    process = SDL_CreateProcessWithProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    if (!buffer) {
        goto failed;
    }
    SDLTest_LogEscapedString("stdout of process: ", buffer, total_read);

    for (i = 3; process_args[i]; i++) {
        char line[64];
        SDL_snprintf(line, sizeof(line), "|%d=%s|", i - 3, process_args[i]);
        SDLTest_AssertCheck(!!SDL_strstr(buffer, line), "Check %s is in output", line);
    }
    SDL_free(buffer);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);

    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static int process_testWindowsCmdlinePrecedence(void *arg)
{
    TestProcessData *data = (TestProcessData *)arg;
    const char *process_args[] = {
        data->childprocess_path,
        "--print-arguments",
        "--",
        "argument 1",
        NULL
    };
    const char *process_cmdline_template = "%s --print-arguments -- \"argument 2\"";
    char process_cmdline[65535];
    SDL_PropertiesID props;
    SDL_Process *process = NULL;
    char *buffer;
    int exit_code;
    size_t total_read = 0;

#ifndef SDL_PLATFORM_WINDOWS
    SDLTest_AssertPass("SDL_PROP_PROCESS_CREATE_CMDLINE_STRING only works on Windows");
    return TEST_SKIPPED;
#endif

    props = SDL_CreateProperties();
    SDLTest_AssertCheck(props != 0, "SDL_CreateProperties()");
    if (!props) {
        goto failed;
    }

    SDL_snprintf(process_cmdline, SDL_arraysize(process_cmdline), process_cmdline_template, data->childprocess_path);
    SDL_SetPointerProperty(props, SDL_PROP_PROCESS_CREATE_ARGS_POINTER, (void *)process_args);
    SDL_SetStringProperty(props, SDL_PROP_PROCESS_CREATE_CMDLINE_STRING, (const char *)process_cmdline);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDIN_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetNumberProperty(props, SDL_PROP_PROCESS_CREATE_STDOUT_NUMBER, SDL_PROCESS_STDIO_APP);
    SDL_SetBooleanProperty(props, SDL_PROP_PROCESS_CREATE_STDERR_TO_STDOUT_BOOLEAN, true);

    process = SDL_CreateProcessWithProperties(props);
    SDLTest_AssertCheck(process != NULL, "SDL_CreateProcessWithProperties()");
    if (!process) {
        goto failed;
    }

    exit_code = 0xdeadbeef;
    buffer = (char *)SDL_ReadProcess(process, &total_read, &exit_code);
    SDLTest_AssertCheck(buffer != NULL, "SDL_ReadProcess()");
    SDLTest_AssertCheck(exit_code == 0, "Exit code should be 0, is %d", exit_code);
    if (!buffer) {
        goto failed;
    }
    SDLTest_LogEscapedString("stdout of process: ", buffer, total_read);
    SDLTest_AssertCheck(!!SDL_strstr(buffer, "|0=argument 2|"), "Check |0=argument 2| is printed");
    SDL_free(buffer);

    SDLTest_AssertPass("About to destroy process");
    SDL_DestroyProcess(process);

    return TEST_COMPLETED;

failed:
    SDL_DestroyProcess(process);
    return TEST_ABORTED;
}

static const SDLTest_TestCaseReference processTestArguments = {
    process_testArguments, "process_testArguments", "Test passing arguments to child process", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestArgumentsBackslashQuote = {
    process_testArgumentsBackslashQuote, "process_testArgumentsBackslashQuote", "Test backslashes before a quote and preservation of the following argument", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsBatchArguments = {
    process_testWindowsBatchArguments, "process_testWindowsBatchArguments", "Test literal batch arguments and spaced batch filenames", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsExecutableBoundary = {
    process_testWindowsExecutableBoundary, "process_testWindowsExecutableBoundary", "Test executable boundaries and rejected trailing path characters", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsShellRejections = {
    process_testWindowsShellRejections, "process_testWindowsShellRejections", "Test synchronous rejection of unsafe shell arguments", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsCmdArguments = {
    process_testWindowsCmdArguments, "process_testWindowsCmdArguments", "Test literal cmd arguments and explicit raw command-line precedence", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestExitCode = {
    process_testexitCode, "process_testExitCode", "Test exit codes", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestInheritedEnv = {
    process_testInheritedEnv, "process_testInheritedEnv", "Test inheriting environment from parent process", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestNewEnv = {
    process_testNewEnv, "process_testNewEnv", "Test creating new environment for child process", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestKill = {
    process_testKill, "process_testKill", "Test Killing a child process", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestStdinToStdout = {
    process_testStdinToStdout, "process_testStdinToStdout", "Test writing to stdin and reading from stdout", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestStdinToStderr = {
    process_testStdinToStderr, "process_testStdinToStderr", "Test writing to stdin and reading from stderr", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestSimpleStdinToStdout = {
    process_testSimpleStdinToStdout, "process_testSimpleStdinToStdout", "Test writing to stdin and reading from stdout using the simplified API", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestMultiprocessStdinToStdout = {
    process_testMultiprocessStdinToStdout, "process_testMultiprocessStdinToStdout", "Test writing to stdin and reading from stdout using the simplified API", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWriteToFinishedProcess = {
    process_testWriteToFinishedProcess, "process_testWriteToFinishedProcess", "Test writing to stdin of terminated process", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestNonExistingExecutable = {
    process_testNonExistingExecutable, "process_testNonExistingExecutable", "Test running a non-existing executable", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestBatBadButVulnerability = {
    process_testBatBadButVulnerability, "process_testBatBadButVulnerability", "Test BatBadBut vulnerability: command injection through cmd.exe", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestFileRedirection = {
    process_testFileRedirection, "process_testFileRedirection", "Test redirection from/to files", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsCmdline = {
    process_testWindowsCmdline, "process_testWindowsCmdline", "Test passing cmdline directly to CreateProcess", TEST_ENABLED
};

static const SDLTest_TestCaseReference processTestWindowsCmdlinePrecedence = {
    process_testWindowsCmdlinePrecedence, "process_testWindowsCmdlinePrecedence", "Test SDL_PROP_PROCESS_CREATE_CMDLINE_STRING precedence over SDL_PROP_PROCESS_CREATE_ARGS_POINTER", TEST_ENABLED
};

static const SDLTest_TestCaseReference *processTests[] = {
    &processTestArguments,
    &processTestArgumentsBackslashQuote,
    &processTestWindowsBatchArguments,
    &processTestWindowsExecutableBoundary,
    &processTestWindowsShellRejections,
    &processTestWindowsCmdArguments,
    &processTestExitCode,
    &processTestInheritedEnv,
    &processTestNewEnv,
    &processTestKill,
    &processTestStdinToStdout,
    &processTestStdinToStderr,
    &processTestSimpleStdinToStdout,
    &processTestMultiprocessStdinToStdout,
    &processTestWriteToFinishedProcess,
    &processTestNonExistingExecutable,
    &processTestBatBadButVulnerability,
    &processTestFileRedirection,
    &processTestWindowsCmdline,
    &processTestWindowsCmdlinePrecedence,
    NULL
};

static SDLTest_TestSuiteReference processTestSuite = {
    "Process",
    setUpProcess,
    processTests,
    NULL
};

static SDLTest_TestSuiteReference *testSuites[] = {
    &processTestSuite,
    NULL
};

int main(int argc, char *argv[])
{
    int i;
    int result;
    SDLTest_CommonState *state;
    SDLTest_TestSuiteRunner *runner;

    /* Initialize test framework */
    state = SDLTest_CommonCreateState(argv, 0);
    if (!state) {
        return 1;
    }

    runner = SDLTest_CreateTestSuiteRunner(state, testSuites);

    /* Parse commandline */
    for (i = 1; i < argc;) {
        int consumed;

        consumed = SDLTest_CommonArg(state, i);
        if (!consumed) {
            if (!parsed_args.childprocess_path) {
                parsed_args.childprocess_path = argv[i];
                consumed = 1;
            }
        }
        if (consumed <= 0) {
            SDLTest_CommonLogUsage(state, argv[0], options);
            return 1;
        }

        i += consumed;
    }

    if (!parsed_args.childprocess_path) {
        SDLTest_CommonLogUsage(state, argv[0], options);
        return 1;
    }

    result = SDLTest_ExecuteTestSuiteRunner(runner);

    SDL_Quit();
    SDLTest_DestroyTestSuiteRunner(runner);
    SDLTest_CommonDestroyState(state);
    return result;
}
