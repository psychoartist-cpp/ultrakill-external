#include "AudioProvider.h"

bool PlayAsyncSound(const wchar_t* path)
{
	return PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
}
