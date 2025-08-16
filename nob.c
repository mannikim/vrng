// SPDX-License-Identifier: GPL-3.0-or-later
// copyright 2025 mannikim mannikim[at]proton[dot]me
// this file is part of vrng.h
// see the bottom of the `vrng.h` file for the license text

// c program for building & running tests

// this program uses nob, a build tool dual-licensed under the MIT license and
// the UNLICENSE
// nob is copyright 2024 Alexey Kutepov
// see `nob.h` for license and copyright information

#define BUILD_DIR "bin/"
#define TEST_DIR "test/"

#define nob_cc_flags(cmd) \
	nob_cmd_append( \
		cmd, "-Wall", "-Wextra", "-Wpedantic", "-Werror", "-std=c99")

#define vrng_flags(cmd) nob_cmd_append(cmd, "-O3", "-c")
#define test_flags(cmd) \
	nob_cmd_append(cmd, "-O0", "-g", "-fsanitize=address", "-I.")

#define NOB_IMPLEMENTATION
#define PATH_MAX 12
#include "nob.h"

static const char *test_names[] = {
	"init", 
	"u32", 
	"u64", 
	"weightu32", 
	"weightu64"};

static bool
build_and_run_test(Nob_Cmd *cmd, const char *test_name)
{
	size_t mark = nob_temp_save();

	const char *bin_path =
		nob_temp_sprintf("%s%s", BUILD_DIR TEST_DIR, test_name);
	const char *src_path = nob_temp_sprintf("%s%s.c", TEST_DIR, test_name);

	nob_cc(cmd);
	nob_cc_flags(cmd);
	test_flags(cmd);
	nob_cc_output(cmd, bin_path);
	nob_cc_inputs(cmd, src_path, BUILD_DIR "vrng.o");

	if (!nob_cmd_run_sync_and_reset(cmd))
		return false;

	if (!nob_set_current_dir(TEST_DIR))
		return false;
	nob_cmd_append(
		cmd,
		nob_temp_sprintf("../" BUILD_DIR TEST_DIR "%s", test_name));
	if (!nob_cmd_run_sync_and_reset(cmd))
		return false;
	if (!nob_set_current_dir("../"))
		return false;

	nob_log(NOB_INFO, "--- %s finished ---", bin_path);

	nob_temp_rewind(mark);
	return true;
}

int
main(int argc, char **argv)
{
	NOB_GO_REBUILD_URSELF(argc, argv);

	const char *program_name = nob_shift(argv, argc);
	const char *command_name = "test";
	if (argc > 0)
		command_name = nob_shift(argv, argc);

	if (!nob_mkdir_if_not_exists(BUILD_DIR))
		return 1;

	if (!nob_mkdir_if_not_exists(BUILD_DIR TEST_DIR))
		return 1;

	if (strcmp(command_name, "test") == 0)
	{
		Nob_Cmd cmd = {0};

		nob_cc(&cmd);
		nob_cc_flags(&cmd);
		vrng_flags(&cmd);
		nob_cc_output(&cmd, BUILD_DIR "vrng.o");
		nob_cc_inputs(&cmd, "vrng.c");

		if (!nob_cmd_run_sync_and_reset(&cmd))
			return false;

		if (argc <= 0)
		{
			for (size_t i = 0; i < NOB_ARRAY_LEN(test_names); ++i)
			{
				if (!build_and_run_test(&cmd, test_names[i]))
					return 1;
			}
			return 0;
		}

		while (argc > 0)
		{
			const char *test_name = nob_shift(argv, argc);
			if (!build_and_run_test(&cmd, test_name))
				return 1;
		}

		return 0;
	}

	// UNREACHABLE

	return 1;
}
