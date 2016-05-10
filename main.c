#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <GL/gl.h>
#include <emscripten/emscripten.h>
#include <emscripten/html5.h>
#include <emscripten/threading.h>

static void* thread(void* data)
{
	EmscriptenWebGLContextAttributes attributes;
	emscripten_webgl_init_context_attributes(&attributes);
	int context = emscripten_webgl_create_context(0, &attributes);
	emscripten_webgl_make_context_current(context);

	int i = 0;

	for(;;)
	{
		i = (i + 1) % 256;

		glClearColor(i / 255.0f, i / 255.0f, i / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		emscripten_webgl_commit_context(context);

		usleep((useconds_t)(1000000.0f / 60.0f));
	}

	return 0;
}

int main()
{
	emscripten_transfer_canvas();

	pthread_t handle;
	pthread_create(&handle, 0, thread, 0);

	emscripten_exit_with_live_runtime();
	return 0;
}
