/*
 *	MetaCall Library by Parra Studios
 *	Copyright (C) 2016 - 2017 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
 *
 *	A library for providing a foreign function interface calls.
 *
 */

#include <gmock/gmock.h>

#include <metacall/metacall.h>
#include <metacall/metacall_value.h>
#include <metacall/metacall_loaders.h>

void * c_function(void * args[])
{
	printf("%s\n", (char*)args[0]);

	return metacall_value_create_int(1);
}

class metacall_reinitialize_test : public testing::Test
{
public:
};

TEST_F(metacall_reinitialize_test, DefaultConstructor)
{
	metacall_print_info();

	metacall_log_stdio_type log_stdio = { stdout };

	const size_t initialize_count = 10;

	ASSERT_EQ((int)0, (int)metacall_log(METACALL_LOG_STDIO, (void *)&log_stdio));

	for (size_t iterator = 0; iterator < initialize_count; ++iterator)
	{
		ASSERT_EQ((int) 0, (int) metacall_initialize());

		/* Mock */
		#if defined(OPTION_BUILD_LOADERS_MOCK)
		{
			const char * mock_scripts[] =
			{
				"empty.mock"
			};

			EXPECT_EQ((int) 0, (int) metacall_load_from_file("mock", mock_scripts, sizeof(mock_scripts) / sizeof(mock_scripts[0]), NULL));
		}
		#endif /* OPTION_BUILD_LOADERS_MOCK */

		EXPECT_EQ((int) 0, (int) metacall_destroy());
	}
}
