/*
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any
 * means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <https://unlicense.org>
 */

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <opus/opusenc.h>

#define FILENAME	"sound-file.opus"
#define SAMPLE_RATE	48000
#define CHANNELS	2
#define FAMILY		0
#define DURATION	5.0

int
main(void)
{
	OggOpusComments *comments = ope_comments_create();
	assert(comments);

	int result;
	OggOpusEnc *encoder = ope_encoder_create_file(
		FILENAME, comments, SAMPLE_RATE, CHANNELS, FAMILY, &result);
	assert(result >= 0);

	size_t numSamples = (size_t)(DURATION * SAMPLE_RATE);

	int16_t *pcm = malloc(CHANNELS * numSamples * sizeof *pcm);
	assert(pcm);

	for (size_t i = 0; i < numSamples; i++)
		for (size_t c = 0; c < CHANNELS; c++)
			pcm[CHANNELS * i + c] = ((2*rand()) & 0xFFFF) - 0x8000;

	result = ope_encoder_write(encoder, pcm, numSamples);
	assert(result >= 0);

	free(pcm);

	result = ope_encoder_drain(encoder);
	assert(result >= 0);

	ope_encoder_destroy(encoder);
	ope_comments_destroy(comments);
	return 0;
}
